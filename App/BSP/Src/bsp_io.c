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

void bsp_io_setup_impl(io_t* gpio, io_type type, uint32_t af, io_speed speed, io_state state)
{
    BSP_IO_SET_AF(gpio, af);
    BSP_IO_WRITE(gpio, state);
    BSP_IO_SPEED(gpio, speed);
    BSP_IO_TYPE(gpio, type);
}

void bsp_db_setup_impl(db_t* gpio, io_type type, io_speed speed, io_state state)
{
    BSP_DB_WRITE(gpio, state);
    BSP_DB_SPEED(gpio, speed);
    BSP_DB_TYPE(gpio, type);
}

int8_t bsp_io_preset(io_t* gpio)
{
    if (!gpio)
    {
        return -1;
    }
    bsp_io_setup_impl(gpio, gpio->type, gpio->af, gpio->speed, gpio->state);
    return 0;
}

__FORCEINLINE void bsp_io_setup(io_t* gpio, io_type type, io_speed speed, io_state state)
{
    bsp_io_setup_impl(gpio, type, 0, speed, state);
}

__FORCEINLINE void bsp_io_setup_unused(io_t* gpio)
{
    bsp_io_setup_impl(gpio, IO_TYPE_IN, 0, IO_SPEED_NORMAL, IO_STATE_LOW);
}

__FORCEINLINE void bsp_io_setup_af(io_t* gpio, uint32_t af, io_speed speed)
{
    bsp_io_setup_impl(gpio, IO_TYPE_PERH, af, speed, IO_STATE_LOW);
}
