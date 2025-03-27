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

    #define USE_PRINTF_IMPL
    #define USE_STM32H5_HAL_IMPL

    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    #ifdef USE_PRINTF_IMPL
    #include <stdio.h>
    #endif

    #ifdef USE_STM32H5_HAL_IMPL
    #include "stm32h5xx_hal.h"
    #endif

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
        uart_comm_t* comm_pc = NULL;
        comm_pc = uart_comm_create(&huart4, 2048);

        START SERVICE:
        uart_comm_start(comm_pc);

        LOOP TEST:
        uint8_t recv_bytes[256];
        uint16_t recv_len = 0;

        recv_len = uart_comm_read(comm_pc, recv_bytes, sizeof(recv_bytes));
        if (recv_len != 0)
        {
            uart_comm_write(comm_pc, recv_bytes, recv_len);
        }
     */

    #define UART_COMM_NO_ERR        (0)
    #define UART_COMM_READ_BUF_OVF  (-1)


     // PRINTF IMPL
    #ifdef USE_PRINTF_IMPL
    #define PRINTF                  printf
    #endif

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
    #ifdef USE_STM32H5_HAL_IMPL
    typedef UART_HandleTypeDef uart_t;
    #define UART_TXDMA_START(__HANDLE__)    (HAL_UART_Transmit_DMA((__HANDLE__)->instance, &((__HANDLE__)->txdma_buf)[(__HANDLE__)->txdma_cmd_head], (__HANDLE__)->txdma_cmd_len) == HAL_OK)
    #define UART_RXDMA_START(__HANDLE__)    (HAL_UART_Receive_DMA((__HANDLE__)->instance, (__HANDLE__)->rxdma_buf, (__HANDLE__)->dmabuf_len) == HAL_OK)
    #define UART_STOP(__HANDLE__)           (HAL_UART_DMAStop((__HANDLE__)->instance) == HAL_OK)
    #define UART_IS_TX_BUSY(__HANDLE__)     ((__HANDLE__)->instance->gState != HAL_UART_STATE_READY)
    #define UART_IS_RX_BUSY(__HANDLE__)     ((__HANDLE__)->instance->RxState != HAL_UART_STATE_READY)
    #define UART_GET_RXDMA_POS(__HANDLE__)  ((__HANDLE__)->dmabuf_len - __HAL_DMA_GET_COUNTER((__HANDLE__)->instance->hdmarx))
    #endif

    typedef uint8_t uart_comm_error_t;
    typedef struct uart_comm_t {
        uart_t* instance;                       // uart perh instance
        uint8_t* rxdma_buf;                     // uart rxdma buffer
        uint8_t* txdma_buf;                     // uart txdma buffer
        uint16_t dmabuf_len;                    // buffer length
        uint16_t rxdma_pos_wr, rxdma_pos_rd;    // rxdma buffer read and write cursor
        uint16_t rxdma_pos_parse;               // rxdma buffer cmd parse cursor
        uint16_t txdma_cmd_head, txdma_cmd_len; // txdma buffer cmd head and length
        uart_comm_error_t error;
    } uart_comm_t;


    uart_comm_t* uart_comm_create(uart_t* huart, uint16_t dmabuf_len);
    void uart_comm_destory(uart_comm_t* comm);
    void uart_comm_print_info(const uart_comm_t* comm);
    void uart_comm_start(uart_comm_t* comm);
    void uart_comm_stop(uart_comm_t* comm);
    void uart_comm_write(uart_comm_t* comm, const uint8_t* txcmd, uint16_t size);
    uint16_t uart_comm_read(uart_comm_t* comm, uint8_t* buf, uint16_t size);



    #ifdef __cplusplus
}
#endif

#endif // _UART_COMM_H_
