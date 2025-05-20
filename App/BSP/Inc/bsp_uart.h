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

    #include "usart.h"

    typedef UART_HandleTypeDef uart_t;

    void bsp_uart_init();
    void bsp_uart_init_by_cubemx(uart_t* handle);
    uart_t* get_comm_uart();
    void bsp_uart_write(uart_t* uart, uint8_t* data, uint32_t size);

    void bsp_uart_printf(const char *format, ...);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_UART_H_
