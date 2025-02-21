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

    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    #define USE_PRINTF_IMPL
    #define USE_STM32H5_HAL_IMPL

    #ifdef USE_PRINTF_IMPL
    #include <stdio.h>
    #endif

    #ifdef USE_STM32H5_HAL_IMPL
    #include "stm32h5xx_hal.h"
    #endif

    /*
        USAGE:

        INITIAL:

     */

    #define GPIO_CONFIG_STATUS_NO_ERR   (0)

     // PRINTF IMPL
    #ifdef USE_PRINTF_IMPL
    #define PRINTF                  printf
    #endif

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef GPIO_TypeDef gpio_port_t;
    typedef uint16_t gpio_pin_t;

    #define GPIO_CLOCK(X)                   __HAL_RCC_GPIO##X##_CLK_ENABLE()
    #define GPIO_PORT(X)                    GPIO##X
    #define GPIO_PIN(X)                     GPIO_PIN_##X
    
    #define GPIO_WRITE(PORT, PIN, STATE)    HAL_GPIO_WritePin((PORT),(PIN),(STATE))

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

    typedef uint16_t io_switch_state_t;
    typedef struct io_switch_t
    {
        uint8_t id;                 // switch id

        io_t sw_sel;               // switch sel   (used when can_sel=1)

        //io_t sw_a;                 // switch a
        //io_t sw_b;                 // switch b (unused when not connected to io)
    } io_switch_t;

    #define SWITCH_EN(_MUX_ID_)          ( 1 << ((_MUX_ID_) - 1))

    typedef struct dut_interface_t
    {
        uint16_t id;                        // dut id
        const char* name;                   // dut name

        uint16_t preset_id;                 // dut preset id
        const char* preset_name;            // dut preset name

        io_t** pin_configs;                  // btb pin configs
        uint32_t switch_value;              // switch value

        void* perh[8 + 1];                  // perh instances
    } dut_interface_t;

    gpio_config_status_t gpio_init(io_t* gpio);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_IO_H_
