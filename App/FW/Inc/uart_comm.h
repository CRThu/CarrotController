/****************************
 * UART COMM
 * CARROT HU
 * 2024.08.12
 *****************************/
#pragma once
#ifndef _UART_COMM_H_
#define _UART_COMM_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define UART_COMM_VERSION "2.1.0"
    #include <stdint.h>
    #include <string.h>
    #include "main.h"
    #include "usart.h"

    /*
        USAGE:
        SETUP UARTx:
        ENABLE UARTx GLOBAL INTERRUPT
        SETUP DMA:
        TXDMA:              HIGH PRIORITY, MEM2PER, MEM(SRC) ADDR INCR
        RXDMA: CIRCULAR,    HIGH PRIORITY, PER2MEM, MEM(DEST) ADDR INCR
        SETUP TIMx:
        ENABLE TIMx GLOBAL INTERRUPT
        PSC = 25000-1       (fCLK=250MHz, fTIM=10KHz)
        ARR = 10-1          (fTIM=10KHz, fINT=1KHz)
        SETUP NVIC:
        NVIC Interrupt Table    Preemption Priority
        RXDMA/TXDMA             1
        UARTx GLOBAL INT        2
        TIMx GLOBAL INT         14

        INITIAL:

     */

    #define UART2PC_HANDLE      huart4
    #define RXDMA_BUFSIZE       2048
    #define TXDMA_BUFSIZE       2048

    #define UART_COMM_NO_ERR    0

    #define RXDMA_POS_END       (RXDMA_BUFSIZE - 1)



    #define CIRCUIR_ARRAY_INDEX(idx, size)  ((idx) < (size) ? (idx) : ((idx) - (size)))
    #define MEMCPY_FROM_RINGBUF(dst, src, src_size, src_head, len)                          \
        do {                                                                                \
            size_t first_chunk_size = (src_size) - (src_head);                              \
            if((len) <= (first_chunk_size)) {                                               \
                memcpy((dst), &(src)[(src_head)], (len));                                   \
            } else {                                                                        \
                memcpy((dst), &(src)[(src_head)], (first_chunk_size));                      \
                memcpy((dst) + (first_chunk_size), &(src)[0], (len) - (first_chunk_size));  \
            }                                                                               \
        } while (0)                                                                         \

     // STM32
    typedef UART_HandleTypeDef uart_t;
    #define UART_RXDMA_START(uart_comm) (HAL_UART_Receive_DMA( &((uart_comm)->instance), (uart_comm)->rxdma_buf, (uart_comm)->dmabuf_len ))
    #define UART_RXDMA_STOP(uart_comm) (void)

    typedef uint8_t uart_comm_error_t;
    typedef struct uart_comm_t {
        uart_t* instance;                       // uart perh instance
        uint8_t* rxdma_buf;                     // uart rxdma buffer
        uint8_t* txdma_buf;                     // uart txdma buffer
        uint8_t* rxcmd_buf;                     // uart rxcmd buffer
        uint16_t dmabuf_len, cmdbuf_len;        // buffer length
        uint16_t rxdma_pos_wr, rxdma_pos_rd;    // rxdma buffer read and write cursor
        uint16_t rxdma_cmd_head, rxdma_cmd_len; // rxdma buffer cmd head and length
        uart_comm_error_t error;
    } uart_comm_t;


    uart_comm_t* uart_comm_create(uart_t* huart, uint16_t dmabuf_len, uint16_t cmdbuf_len);
    void uart_comm_destory(uart_comm_t* comm);
    void uart_comm_print_info(const uart_comm_t* comm);
    void uart_comm_start();
    
    void uart_rxdma_parse();
    uint16_t uart_rxdma_read(uint8_t* rxcmd_buf, uint16_t len);
    void uart_txdma_write(uint8_t* txcmd_buf, uint16_t len);



    #ifdef __cplusplus
}
#endif

#endif // _UART_COMM_H_
