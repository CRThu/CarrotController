#include "bsp_inc.h"
#include <stdarg.h>

uart_t* bsp_uart[] =
{
    &huart4,
};

void bsp_uart_init()
{
    // todo
}

void bsp_uart_init_by_cubemx(uart_t* handle)
{
    if (handle->gState != HAL_UART_STATE_READY)
    {
        Error_Handler();
    }
}

uart_t* get_comm_uart()
{
    return bsp_uart[0];
}

void bsp_uart_write(uart_t* uart, uint8_t* data, uint32_t size)
{
    uint16_t dmasize = size;
    uint32_t offset = 0;
    while (size)
    {
        if (size >= UINT16_MAX)
            dmasize = UINT16_MAX;
        else
            dmasize = size;

        while (uart->gState != HAL_UART_STATE_READY);
        HAL_StatusTypeDef ret = HAL_UART_Transmit_DMA(uart, &data[offset], dmasize);
        if (ret != HAL_OK)
        {
            Error_Handler();
        }

        size -= dmasize;
        offset += dmasize;
    }
}


#define UART_TX_BUFFER_SIZE 2048
uint8_t UartTxBuffer[UART_TX_BUFFER_SIZE];
volatile uint32_t UartTxBufferPacketSize = 0;
void bsp_uart_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    UartTxBufferPacketSize = vsnprintf((char *)UartTxBuffer, 2048, (char *)format, args);
    va_end(args);

    while (HAL_UART_Transmit(get_comm_uart(), UartTxBuffer, UartTxBufferPacketSize, 100))
        ;
}
