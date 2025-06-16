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
    #include "commbuf.h"

    #include "carrot_protocol.h"

    /*
        USAGE:

        INITIAL:
        ft_comm_t* comm_pc = NULL;
        comm_pc = ft_comm_create(&ft, 2048);

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

    typedef struct ft_comm_t {
        comm_func_t func;                       // func for protocol
        ft_t* instance;                         // ft instance
        commbuf_t* rxbuf;                       // ft rx buffer
    } ft_comm_t;

    ft_comm_t* ft_comm_create(ft_t* hft, uint16_t dmabuf_len);
    void ft_comm_free(ft_comm_t* comm);
    void ft_comm_print_info(const ft_comm_t* comm);
    void ft_comm_write(void* comm, const uint8_t* txcmd, uint16_t size);
    uint16_t ft_comm_read(ft_comm_t* comm, uint8_t* buf, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _FT_COMM_H_
