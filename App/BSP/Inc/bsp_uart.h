/****************************
 * BSP UART DRIVER
 * CRTHu
 * 2025.04.08
 *****************************/
#pragma once
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_UART_VERSION "1.0.0"


    #include "bsp_inc.h"

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef UART_HandleTypeDef bsp_uart_handle_t;
    #endif


    typedef struct bsp_uart_t
    {
        bsp_uart_handle_t* handle;
    } bsp_uart_t;

    void bsp_comm_uart_init();
    void bsp_comm_uart_init_by_cubemx(bsp_uart_handle_t* handle);
    bsp_uart_t* get_comm_uart();
    void bsp_uart_write(bsp_uart_t* uart, uint8_t* data, uint32_t size);


    #ifdef __cplusplus
}
#endif

#endif // _BSP_UART_H_
