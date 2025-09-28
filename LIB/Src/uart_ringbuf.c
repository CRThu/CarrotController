#include "uart_ringbuf.h"

uart_ringbuf_t* uart_ringbuf_create(uart_t* huart, uint16_t dmabuf_len)
{
    uart_ringbuf_t* rb = (uart_ringbuf_t*)malloc(sizeof(uart_ringbuf_t));
    if (!rb)
        return NULL;

    rb->instance = huart;
    rb->dmabuf_len = dmabuf_len;
    rb->rxdma_pos_wr = 0;
    rb->rxdma_pos_rd = 0;
    rb->rxdma_pos_parse = 0;
    rb->txdma_cmd_head = 0;
    rb->txdma_cmd_len = 0;
    rb->error = UART_RINGBUF_NO_ERR;

    rb->txdma_buf = (uint8_t*)malloc(rb->dmabuf_len);
    rb->rxdma_buf = (uint8_t*)malloc(rb->dmabuf_len);

    if (!rb->txdma_buf || !rb->rxdma_buf)
    {
        free(rb->txdma_buf);
        free(rb->rxdma_buf);
        free(rb);
        return NULL;
    }
    return rb;
}

void uart_ringbuf_destory(uart_ringbuf_t* rb)
{
    if (rb)
    {
        free(rb->txdma_buf);
        free(rb->rxdma_buf);
        free(rb);
    }
}

void uart_ringbuf_print_info(const uart_ringbuf_t* rb)
{
    if (rb)
    {
        PRINTF("\n");
    }
}

void uart_ringbuf_start(uart_ringbuf_t* rb)
{
    UART_RXDMA_START(rb);
}

void uart_ringbuf_stop(uart_ringbuf_t* rb)
{
    UART_STOP(rb);
}

void uart_ringbuf_write(uart_ringbuf_t* rb, const uint8_t* txcmd, uint16_t size)
{
    // todo txlist
    while (UART_IS_TX_BUSY((uart_ringbuf_t*)rb))
    {
        // WAITING FOR AVAILABLE
        __NOP();
    }

    memcpy(((uart_ringbuf_t*)rb)->txdma_buf, txcmd, size);
    ((uart_ringbuf_t*)rb)->txdma_cmd_head = 0;
    ((uart_ringbuf_t*)rb)->txdma_cmd_len = size;

    while (!UART_TXDMA_START(((uart_ringbuf_t*)rb)))
    {
        // ERROR
        __NOP();
    }
}

uint16_t uart_ringbuf_read(uart_ringbuf_t* rb, uint8_t* buf, uint16_t size)
{
    // UPDATE RXDMA_POS_WR
    // if BUFLEN=8
    // NDTR     87654321876
    // wr       01234567012
    rb->rxdma_pos_wr = UART_GET_RXDMA_POS(rb);
    if(!UART_RXDMA_CIR_CHECK(rb))
        return UART_RINGBUF_IS_NOT_CIRCULAR;

    while (rb->rxdma_pos_parse != rb->rxdma_pos_wr)
    {
        // printf("[INFO]: rd=%3d, wr=%3d, parse=%3d.\r\n", rb->rxdma_pos_rd, rb->rxdma_pos_wr, rb->rxdma_pos_parse);
        if ((rb->rxdma_buf[rb->rxdma_pos_parse]) == '\n')
        {
            // ptr++
            rb->rxdma_pos_parse = IDX_RINGBUF(rb->rxdma_pos_parse + 1, rb->dmabuf_len);

            // parse packet end symbol '\n'
            uint16_t cmd_len = LEN_RINGBUF(rb->dmabuf_len, rb->rxdma_pos_parse, rb->rxdma_pos_rd);

            if (cmd_len > size)
            {
                rb->rxdma_pos_rd = rb->rxdma_pos_parse;
                return UART_RINGBUF_READ_BUF_OVF;
            }

            MEMCPY_RINGBUF(buf, rb->rxdma_buf, rb->dmabuf_len, rb->rxdma_pos_rd, cmd_len);

            rb->rxdma_pos_rd = rb->rxdma_pos_parse;
            return cmd_len;
        }
        else
        {
            // ptr++
            rb->rxdma_pos_parse = IDX_RINGBUF(rb->rxdma_pos_parse + 1, rb->dmabuf_len);
        }
    }

    // printf("[INFO]: no complete\\n command.\r\n");
    return 0;
}
