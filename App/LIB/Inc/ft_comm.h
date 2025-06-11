/****************************
 * FT COMM
 * CARROT HU
 * 2025.06.05
 *****************************/
#pragma once
#ifndef _FT_COMM_H_
#define _FT_COMM_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define FT_COMM_VERSION "0.1.0"

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

    #include "bsp_ft.h"

    /*
        USAGE:

        INITIAL:
        ft_comm_t* comm_pc = NULL;
        comm_pc = ft_comm_create(&huart4, 2048);

        START SERVICE:
        ft_comm_start(comm_pc);

        LOOP TEST:
        uint8_t recv_bytes[256];
        uint16_t recv_len = 0;

        recv_len = ft_comm_read(comm_pc, recv_bytes, sizeof(recv_bytes));
        if (recv_len != 0)
        {
            ft_comm_write(comm_pc, recv_bytes, recv_len);
        }
     */

    #define FT_COMM_NO_ERR        (0)
    #define FT_COMM_READ_BUF_OVF  (-1)

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

    typedef uint8_t ft_comm_error_t;
        
    typedef struct ft_comm_t {
        ft_t* instance;                         // ft perh instance
        uint8_t* rxdma_buf;                     // ft rxdma buffer
        uint16_t dmabuf_len;                    // buffer length
        uint16_t rxdma_pos_wr, rxdma_pos_rd;    // rxdma buffer read and write cursor
        uint16_t rxdma_pos_parse;               // rxdma buffer cmd parse cursor
        ft_comm_error_t error;
    } ft_comm_t;


    ft_comm_t* ft_comm_create(ft_t* hft, uint16_t dmabuf_len);
    void ft_comm_destory(ft_comm_t* comm);
    void ft_comm_print_info(const ft_comm_t* comm);
    void ft_comm_start(ft_comm_t* comm);
    void ft_comm_stop(ft_comm_t* comm);
    void ft_comm_write(ft_comm_t* comm, const uint8_t* txcmd, uint16_t size);
    uint16_t ft_comm_read(ft_comm_t* comm, uint8_t* buf, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _FT_COMM_H_
