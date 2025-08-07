/****************************
 * BSP UART DRIVER
 * CRTHu
 * 2025.08.07
 *****************************/
#pragma once
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_UART_VERSION "2.0.0"

    #include <stdint.h>
    #include "usart.h"
    #include "uart_ringbuf.h"
    #include "comm.h"

    /*
        initial:
        comm_t* uart4_ringbuf = bsp_uart_ringbuf_create(&huart4);
        uart4_ringbuf->init(uart4_ringbuf->handle);

        usage:
        uint8_t recv_bytes[256];
        uint16_t recv_len = 0;

        recv_len = uart4_ringbuf->read(uart4_ringbuf->handle, recv_bytes, sizeof(recv_bytes));
        if (recv_len != 0)
        {
            uart4_ringbuf->write(uart4_ringbuf->handle, recv_bytes, recv_len);
        }
    */

    comm_t* bsp_uart_ringbuf_create(uart_t* handle);
    void bsp_uart_init(comm_handle handle);
    uint16_t bsp_uart_read(comm_handle handle, uint8_t* buffer, uint16_t size);
    void bsp_uart_write(comm_handle handle, uint8_t* buffer, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_UART_H_
