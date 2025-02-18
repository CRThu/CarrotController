#include "uart_comm.h"

uart_comm_t* uart_comm_create(uart_t* huart, uint16_t dmabuf_len)
{
    uart_comm_t* comm = (uart_comm_t*)malloc(sizeof(uart_comm_t));
    if (!comm)
        return NULL;

    comm->instance = huart;
    comm->dmabuf_len = dmabuf_len;
    comm->rxdma_pos_wr = 0;
    comm->rxdma_pos_rd = 0;
    comm->rxdma_pos_parse = 0;
    comm->txdma_cmd_head = 0;
    comm->txdma_cmd_len = 0;
    comm->error = UART_COMM_NO_ERR;

    comm->txdma_buf = (uint8_t*)malloc(comm->dmabuf_len);
    comm->rxdma_buf = (uint8_t*)malloc(comm->dmabuf_len);

    if (!comm->txdma_buf || !comm->rxdma_buf)
    {
        free(comm->txdma_buf);
        free(comm->rxdma_buf);
        free(comm);
        return NULL;
    }
    return comm;
}

void uart_comm_destory(uart_comm_t* comm)
{
    if (comm)
    {
        free(comm->txdma_buf);
        free(comm->rxdma_buf);
        free(comm);
    }
}

void uart_comm_print_info(const uart_comm_t* comm)
{
    if (comm)
    {
        PRINTF("\n");
    }
}

void uart_comm_start(uart_comm_t* comm)
{
    UART_RXDMA_START(comm);
}

void uart_comm_stop(uart_comm_t* comm)
{
    UART_STOP(comm);
}

void uart_comm_write(uart_comm_t* comm, const uint8_t* txcmd, uint16_t size)
{
    // todo txlist
    while (UART_IS_TX_BUSY(comm))
    {
        // WAITING FOR AVAILABLE
        __NOP();
    }

    memcpy(comm->txdma_buf, txcmd, size);
    comm->txdma_cmd_head = 0;
    comm->txdma_cmd_len = size;

    while (!UART_TXDMA_START(comm))
    {
        // ERROR
        __NOP();
    }
}

uint16_t uart_comm_read(uart_comm_t* comm, uint8_t* buf, uint16_t size)
{
    // UPDATE RXDMA_POS_WR
    // if BUFLEN=8
    // NDTR     87654321876
    // wr       01234567012
    comm->rxdma_pos_wr = UART_GET_RXDMA_POS(comm);

    for (uint16_t i = 0; i < LEN_RINGBUF(comm->dmabuf_len, comm->rxdma_pos_wr, comm->rxdma_pos_parse); i++)
    {
        // ptr++
        comm->rxdma_pos_parse = IDX_RINGBUF(comm->rxdma_pos_parse + 1, comm->dmabuf_len);

        if ((comm->rxdma_buf[IDX_RINGBUF(comm->rxdma_pos_parse, comm->dmabuf_len)]) == '\n')
        {
            // parse packet end symbol '\n'
            uint16_t cmd_len = LEN_RINGBUF(comm->dmabuf_len, comm->rxdma_pos_parse, comm->rxdma_pos_rd);

            if (cmd_len > size)
                return UART_COMM_READ_BUF_OVF;

            MEMCPY_RINGBUF(buf, comm->rxdma_buf, comm->dmabuf_len, comm->rxdma_pos_rd, cmd_len);

            comm->rxdma_pos_rd = comm->rxdma_pos_parse;
            return cmd_len;
        }
    }

    return 0;
}
