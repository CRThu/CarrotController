/****************************
 * BSP IO
 * CARROT HU
 * 2025.03.27
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


    /* from stm32h5xx_hal.h
        #define SET_BIT(REG, BIT)     ((REG) |= (BIT))
        #define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
        #define READ_BIT(REG, BIT)    ((REG) & (BIT))
        #define CLEAR_REG(REG)        ((REG) = (0x0))
        #define WRITE_REG(REG, VAL)   ((REG) = (VAL))
        #define READ_REG(REG)         ((REG))
        #define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
        #define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))
    */

    #define BITSMASK(START, END)                    ((((1U) << ((END) - (START) + 1)) - 1) << (START))
    #define WRITE_RS_REG(REG, DATA, MASK)           WRITE_REG((REG), ((DATA) & (MASK)) | ((~(DATA) & (MASK)) << 16U))

    #define WRITE_DB_MASK(GPIOx, DATA, MASK)        WRITE_RS_REG((GPIOx)->BSRR, (DATA), (MASK))
    #define WRITE_DB(GPIOx, DATA)                   WRITE_DB_MASK((GPIOx), (DATA), AD7616_DB_MASK)
    #define WRITE_IO(GPIOx, PINMASK, STATE)         WRITE_REG((GPIOx)->BSRR, ((STATE)? (PINMASK) : (PINMASK) << 16U))
    #define READ_DB(GPIOx)                          (uint32_t)(READ_REG((GPIOx)->IDR))
    #define READ_IO(GPIOx, PINMASK)                 ((READ_REG((GPIOx)->IDR) & (PINMASK)) != 0 ? 1 : 0)

    #define BITS_GET(REG, START, END)               (((REG) & BITSMASK((START), (END))) >> (START))
    #define BITS_SET(REG, START, END, DATA)         (((REG) & (~BITSMASK((START), (END))) | (((DATA) << (START)) & BITSMASK((START), (END)))))


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
    #define IO_PIN_NAME_MAX_LEN     (32)

    #define gpio_write      GPIO_WRITE
    #define gpio_read       GPIO_READ

    gpio_config_status_t gpio_init(io_t* gpio);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_IO_H_
