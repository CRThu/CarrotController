/****************************
 * UART RINGBUF
 * CARROT HU
 * 2025.09.28
 *****************************/
#pragma once
#ifndef _UART_RINGBUF_H_
#define _UART_RINGBUF_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define UART_RINGBUF_VERSION "2.3.0"

    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "stm32h5xx_hal.h"

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
        uart_ringbuf_t* rb = uart_ringbuf_create(handle, 2048);

        START SERVICE:
        uart_ringbuf_start(rb);

        LOOP TEST:
        uint8_t recv_bytes[256];
        uint16_t recv_len = 0;

        recv_len = uart_ringbuf_read(rb, recv_bytes, sizeof(recv_bytes));
        if (recv_len != 0)
        {
            uart_ringbuf_write(rb, recv_bytes, recv_len);
        }
     */

    #define UART_RINGBUF_NO_ERR             (0)
    #define UART_RINGBUF_READ_BUF_OVF       (-1)
    #define UART_RINGBUF_IS_NOT_CIRCULAR    (-2)

     // PRINTF IMPL
    #define PRINTF                  printf

    // RINGBUF IMPL
    #define IDX_RINGBUF(__IDX__, __SIZE__)                          ((__IDX__) < (__SIZE__) ? (__IDX__) : ((__IDX__) - (__SIZE__)))
    #define LEN_RINGBUF(__SIZE__, __END_PTR__, __START_PTR__)       ((__START_PTR__) <= (__END_PTR__) ? (__END_PTR__) - (__START_PTR__) : (__END_PTR__) + (__SIZE__) - (__START_PTR__))
    #define MEMCPY_RINGBUF(__DST__, __SRC__, __SRC_SIZE__, __SRC_HEAD__, __LEN__)                               \
        do {                                                                                                    \
            uint16_t __FIRST_CHUNK_SIZE__ = (__SRC_SIZE__) - (__SRC_HEAD__);                                    \
            if((__LEN__) <= (__FIRST_CHUNK_SIZE__)) {                                                           \
                memcpy((__DST__), &(__SRC__)[(__SRC_HEAD__)], (__LEN__));                                       \
            } else {                                                                                            \
                memcpy((__DST__), &(__SRC__)[(__SRC_HEAD__)], (__FIRST_CHUNK_SIZE__));                          \
                memcpy((__DST__) + (__FIRST_CHUNK_SIZE__), &(__SRC__)[0], (__LEN__) - (__FIRST_CHUNK_SIZE__));  \
            }                                                                                                   \
        } while (0)                                                                         

    // STM32 IMPL
    typedef UART_HandleTypeDef uart_t;
    #define UART_TXDMA_START(__HANDLE__)        (HAL_UART_Transmit_DMA((__HANDLE__)->instance, &((__HANDLE__)->txdma_buf)[(__HANDLE__)->txdma_cmd_head], (__HANDLE__)->txdma_cmd_len) == HAL_OK)
    #define UART_RXDMA_START(__HANDLE__)        (HAL_UART_Receive_DMA((__HANDLE__)->instance, (__HANDLE__)->rxdma_buf, (__HANDLE__)->dmabuf_len) == HAL_OK)
    #define UART_STOP(__HANDLE__)               (HAL_UART_DMAStop((__HANDLE__)->instance) == HAL_OK)
    #define UART_IS_TX_BUSY(__HANDLE__)         ((__HANDLE__)->instance->gState != HAL_UART_STATE_READY)
    #define UART_IS_RX_BUSY(__HANDLE__)         ((__HANDLE__)->instance->RxState != HAL_UART_STATE_READY)
    #define UART_GET_RXDMA_POS(__HANDLE__)      ((__HANDLE__)->dmabuf_len - __HAL_DMA_GET_COUNTER((__HANDLE__)->instance->hdmarx))
    #define UART_RXDMA_CIR_CHECK(__HANDLE__)    (__HAL_DMA_GET_COUNTER((__HANDLE__)->instance->hdmarx) != 0)

    typedef uint8_t uart_comm_error_t;
    typedef struct uart_ringbuf_t {
        uart_t* instance;                       // uart perh instance
        uint8_t* rxdma_buf;                     // uart rxdma buffer
        uint8_t* txdma_buf;                     // uart txdma buffer
        uint16_t dmabuf_len;                    // buffer length
        uint16_t rxdma_pos_wr, rxdma_pos_rd;    // rxdma buffer read and write cursor
        uint16_t rxdma_pos_parse;               // rxdma buffer cmd parse cursor
        uint16_t txdma_cmd_head, txdma_cmd_len; // txdma buffer cmd head and length
        uart_comm_error_t error;
    } uart_ringbuf_t;

    uart_ringbuf_t* uart_ringbuf_create(uart_t* huart, uint16_t dmabuf_len);
    void uart_ringbuf_destory(uart_ringbuf_t* rb);
    void uart_ringbuf_print_info(const uart_ringbuf_t* rb);
    void uart_ringbuf_start(uart_ringbuf_t* rb);
    void uart_ringbuf_stop(uart_ringbuf_t* rb);
    void uart_ringbuf_write(uart_ringbuf_t* rb, const uint8_t* txcmd, uint16_t size);
    uint16_t uart_ringbuf_read(uart_ringbuf_t* rb, uint8_t* buf, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _UART_RINGBUF_H_
