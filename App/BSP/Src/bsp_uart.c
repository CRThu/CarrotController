#include "bsp_inc.h"

bsp_uart_t comm_uart;

void bsp_comm_uart_init()
{
    // todo
}

void bsp_comm_uart_init_by_cubemx(bsp_uart_handle_t* handle)
{
    comm_uart.handle = handle;
    if (handle->gState != HAL_UART_STATE_READY)
    {
        Error_Handler();
    }
}

bsp_uart_t* get_comm_uart()
{
    return &comm_uart;
}

void bsp_uart_write(bsp_uart_t* uart, uint8_t* data, uint16_t size)
{
    while (uart->handle->gState != HAL_UART_STATE_READY);
    HAL_UART_Transmit_DMA(uart->handle, data, size);
}