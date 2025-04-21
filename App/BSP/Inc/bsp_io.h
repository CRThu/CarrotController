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

    #include "io_utils.h"

    #include "bsp_inc.h"
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    /*
        USAGE:

        INITIAL:

     */

    typedef GPIO_TypeDef gpio_port_t;
    typedef uint16_t gpio_pin_t;

    #define GPIO_CLOCK_EN(X)                __HAL_RCC_GPIO##X##_CLK_ENABLE()
    #define GPIO_PORT(X)                    GPIO##X
    #define GPIO_PIN(X)                     GPIO_PIN_##X

    typedef enum {
        IO_STATE_LOW = 0,
        IO_STATE_HIGH = 1,
        //IO_STATE_RESERVED
    } io_state;

    typedef enum {
        IO_TYPE_IN = GPIO_MODE_INPUT,
        IO_TYPE_OUT = GPIO_MODE_OUTPUT_PP,
        IO_TYPE_PERH = GPIO_MODE_AF_PP,
        //IO_TYPE_RESERVED
    } io_type;

    typedef enum {
        IO_SPEED_NORMAL = GPIO_SPEED_FREQ_MEDIUM,
        IO_SPEED_FAST = GPIO_SPEED_FREQ_VERY_HIGH,
        //IO_SPEED_RESERVED
    } io_speed;

    typedef struct io_t {
        uint16_t btb_pin;           // btb pin num
        const char* pin_name;       // btb pin num

        gpio_port_t* port;          // gpio port
        gpio_pin_t pin;             // gpio pin
        io_state state;             // gpio state

        uint32_t type;
        uint32_t speed;
        uint32_t af;                // alternate function
    } io_t;

    typedef gpio_port_t db_t;

    #define IO_ARR_END_ID               (uint16_t)(-1)
    #define IO_PIN_NAME_MAX_LEN         (32)

    // BTB IMPL
    #define BTB_DB_PORT                 GPIO_PORT(D)

    #define BSP_IO_SET_AF(IO, AF)       IO_SET_AF((IO)->port, (IO)->pin, AF)
    #define BSP_IO_TYPE(IO, TYPE)       IO_SET_MODE((IO)->port, (IO)->pin, TYPE)
    #define BSP_IO_SPEED(IO, SPEED)     IO_SET_SPEED((IO)->port, (IO)->pin, SPEED)
    #define BSP_IO_WRITE(IO, STATE)     IO_WRITE((IO)->port, (IO)->pin, ((STATE) == IO_STATE_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET)
    #define BSP_IO_READ(IO)             ((IO_READ((IO)->port, (IO)->pin) == GPIO_PIN_SET) ? IO_STATE_HIGH : IO_STATE_LOW)

    // DB OPER(DB实现无法重置AF寄存器)
    #define BSP_DB_TYPE(PORT, TYPE)     DB_SET_MODE(PORT, TYPE)
    #define BSP_DB_SPEED(PORT, SPEED)   DB_SET_SPEED(PORT, SPEED)
    #define BSP_DB_WRITE(PORT, DATA)    DB_WRITE(PORT, DATA)
    #define BSP_DB_READ(PORT)           DB_READ(PORT)

    // alias
    #define io_write                    BSP_IO_WRITE
    #define io_read                     BSP_IO_READ
    #define db_write                    BSP_DB_WRITE
    #define db_read                     BSP_DB_READ

    void bsp_gpio_init();
    void bsp_io_setup_impl(io_t* gpio, io_type type, uint32_t af, io_speed speed, io_state state);
    void bsp_db_setup_impl(db_t* gpio, io_type type, io_speed speed, io_state state);
    int8_t bsp_io_preset(io_t* gpio);
    void bsp_io_setup(io_t* gpio, io_type type, io_speed speed, io_state state);
    void bsp_io_setup_unused(io_t* gpio);
    void bsp_io_setup_af(io_t* gpio, uint32_t af, io_speed speed);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_IO_H_
