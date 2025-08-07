#include "bsp_uart.h"
#include <stdarg.h>

comm_t* bsp_uart_ringbuf_create(uart_t* handle)
{
    comm_t* comm = (comm_t*)malloc(sizeof(comm_t));
    if (!comm)
        return NULL;

    comm->id = "USART-RINGBUF";
    comm->handle = uart_ringbuf_create(handle, 2048);
    comm->init = bsp_uart_init;
    comm->read = bsp_uart_read;
    comm->write = bsp_uart_write;
    return comm;
}

void bsp_uart_ringbuf_destory(comm_t* comm)
{
    if (comm)
    {
        uart_ringbuf_destory(comm->handle);
        free(comm);
    }
}


void bsp_uart_init(comm_handle handle)
{
    uart_ringbuf_start(handle);
}

uint16_t bsp_uart_read(comm_handle handle, uint8_t* buffer, uint16_t size)
{
    return uart_ringbuf_read(handle, buffer, size);
}

void bsp_uart_write(comm_handle handle, uint8_t* buffer, uint16_t size)
{
    uart_ringbuf_write(handle, buffer, size);
}