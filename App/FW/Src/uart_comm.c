#include "uart_comm.h"

uart_comm_t* uart_comm_create(uart_t* huart, uint16_t dmabuf_len, uint16_t cmdbuf_len)
{
    uart_comm_t* comm = (uart_comm_t*)malloc(sizeof(uart_comm_t));
    if (!comm)
        return NULL;

    comm->instance = huart;
    comm->dmabuf_len = dmabuf_len;
    comm->cmdbuf_len = cmdbuf_len;
    comm->rxdma_pos_wr = 0;
    comm->rxdma_pos_rd = 0;
    comm->rxdma_cmd_head = 0;
    comm->rxdma_cmd_len = 0;
    comm->error = UART_COMM_NO_ERR;

    comm->txdma_buf = (uint8_t*)malloc(comm->dmabuf_len);
    comm->rxdma_buf = (uint8_t*)malloc(comm->dmabuf_len);
    comm->rxcmd_buf = (uint8_t*)malloc(comm->cmdbuf_len);

    if (!comm->txdma_buf || !comm->rxdma_buf || !comm->rxcmd_buf)
    {
        free(comm->txdma_buf);
        free(comm->rxdma_buf);
        free(comm->rxcmd_buf);
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
        free(comm->rxcmd_buf);
        free(comm);
    }
}

void uart_comm_print_info(const uart_comm_t* comm)
{
    if (comm)
    {
        printf("\n");
    }
}

void uart_comm_start(uart_comm_t* comm)
{
    UART_RXDMA_START(comm);
}

void uart_comm_stop(uart_comm_t* comm)
{
    UART_RXDMA_STOP(comm);
}

void uart_comm_write(uart_comm_t* comm, const uint8_t* txcmd, uint16_t txcmd_len)
{
    while (UART2PC_HANDLE.gState != HAL_UART_STATE_READY)
    {
        // WAITING FOR AVAILABLE
        __NOP();
    }
    
    memcpy(comm->txdma_buf, txcmd, txcmd_len);
    while (HAL_UART_Transmit_DMA(&UART2PC_HANDLE, comm->txdma_buf, txcmd_len) != HAL_OK)
    {
        // ERROR
        __NOP();
    }
}

void uart_rxdma_parse()
{
    // NDTR     876543218
    // wr       012345670
    rxdma_pos_wr = (RXDMA_BUFSIZE - __HAL_DMA_GET_COUNTER(UART2PC_HANDLE.hdmarx));

    // start from read cursor
    uint16_t pos_start = rxdma_pos_rd;
    // end to write cursor (maybe across bound)
    uint16_t pos_end = rxdma_pos_rd <= rxdma_pos_wr ? rxdma_pos_wr : RXDMA_BUFSIZE + rxdma_pos_wr;
    for (uint16_t i = 0; i < pos_end - pos_start; i++)
    {
        // goto frame end
        if ((rxdma_buf[CIRCUIR_ARRAY_INDEX((pos_start + i), (RXDMA_BUFSIZE))]) == '\n')
        {
            rxcmd_src_head = pos_start;
            rxcmd_src_len = i + 1;
            rxdma_pos_rd = CIRCUIR_ARRAY_INDEX(pos_start + i + 1, RXDMA_BUFSIZE);
            break;
        }
    }
}

uint16_t uart_rxdma_read(uint8_t* rxcmd_buf, uint16_t len)
{
    uint16_t rxlen = 0;
    if (!rxcmd_src_len != 0)
    {
        uart_rxdma_parse();
    }
    if ((rxcmd_src_len != 0) && (rxcmd_src_len <= len))
    {
        MEMCPY_FROM_RINGBUF(rxcmd_buf, rxdma_buf, RXDMA_BUFSIZE, rxcmd_src_head, rxcmd_src_len);
        rxlen = rxcmd_src_len;
        rxcmd_src_head = 0;
        rxcmd_src_len = 0;
    }
    return rxlen;
}
