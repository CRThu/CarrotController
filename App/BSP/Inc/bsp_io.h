/****************************
 * BSP IO
 * CARROT HU
 * 2025.02.19
 *****************************/
#pragma once
#ifndef _BSP_IO_H_
#define _BSP_IO_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_IO_VERSION "1.0.0"

    #include "bsp_inc.h"
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    /*
        USAGE:

        INITIAL:

     */

    #define GPIO_CONFIG_STATUS_NO_ERR   (0)

     // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef GPIO_TypeDef gpio_port_t;
    typedef uint16_t gpio_pin_t;

    #define GPIO_CLOCK(X)                   __HAL_RCC_GPIO##X##_CLK_ENABLE()
    #define GPIO_PORT(X)                    GPIO##X
    #define GPIO_PIN(X)                     GPIO_PIN_##X

    #define GPIO_WRITE(IO, STATE)           HAL_GPIO_WritePin((IO)->port, (IO)->pin, ((STATE) == IO_STATE_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET)
    #define GPIO_READ(IO)                   ((HAL_GPIO_ReadPin((IO)->port, (IO)->pin) == GPIO_PIN_SET) ? IO_STATE_HIGH : IO_STATE_LOW)
    #endif


    typedef enum {
        BSP_IO_FUNC_NONE,
        BSP_IO_SWITCH_SEL,
        // IO
        BSP_IO_FUNC_IN,
        BSP_IO_FUNC_OUT,
        BSP_IO_FUNC_INOUT,
        // SPI
        BSP_IO_FUNC_SPI_NSS,
        BSP_IO_FUNC_SPI_SCK,
        BSP_IO_FUNC_SPI_MOSI,
        BSP_IO_FUNC_SPI_MISO,
        // PRESERVED
        BSP_IO_FUNC_CUSTOM_BASE = 100
    } bsp_io_func;

    typedef enum {
        IO_STATE_LOW,
        IO_STATE_HIGH,
        IO_STATE_RESERVED
    } io_state;


    typedef uint16_t gpio_config_status_t;
    typedef struct io_t {
        uint16_t btb_pin;           // btb pin num
        const char* pin_name;       // btb pin num

        gpio_port_t* port;          // gpio port
        gpio_pin_t pin;             // gpio pin
        io_state state;             // gpio state

        bsp_io_func func;           // gpio func
        //void* perh;               // perh instance
    } io_t;

    #define IO_ARR_END_ID           (uint16_t)(-1)

    #define gpio_write      GPIO_WRITE
    #define gpio_read       GPIO_READ

    gpio_config_status_t gpio_init(io_t* gpio);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_IO_H_
