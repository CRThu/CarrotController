#include "bsp_inc.h"

void bsp_gpio_init()
{
    #ifdef GPIOA
    GPIO_CLOCK_EN(A);
    #endif
    #ifdef GPIOB
    GPIO_CLOCK_EN(B);
    #endif
    #ifdef GPIOC
    GPIO_CLOCK_EN(C);
    #endif
    #ifdef GPIOD
    GPIO_CLOCK_EN(D);
    #endif
    #ifdef GPIOE
    GPIO_CLOCK_EN(E);
    #endif
    #ifdef GPIOF
    GPIO_CLOCK_EN(F);
    #endif
    #ifdef GPIOG
    GPIO_CLOCK_EN(G);
    #endif
    #ifdef GPIOH
    GPIO_CLOCK_EN(H);
    #endif
    #ifdef GPIOI
    GPIO_CLOCK_EN(I);
    #endif
}

void io_setup(io_t* gpio, io_type type, io_speed speed, io_state state)
{
    BSP_IO_WRITE(gpio, state);
    BSP_IO_SPEED(gpio, speed);
    BSP_IO_TYPE(gpio, type);
}

void db_setup(db_t* gpio, io_type type, io_speed speed, io_state state)
{
    BSP_DB_WRITE(gpio, state);
    BSP_DB_SPEED(gpio, speed);
    BSP_DB_TYPE(gpio, type);
}

int8_t bsp_io_init(io_t* gpio)
{
    if (!gpio)
    {
        return -1;
    }
    io_setup(gpio, gpio->type, gpio->speed, gpio->state);
    return 0;
}
