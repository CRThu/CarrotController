/****************************
 * BSP MUX
 * CARROT HU
 * 2025.02.19
 *****************************/
#pragma once
#ifndef _BSP_MUX_H_
#define _BSP_MUX_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define BSP_MUX_VERSION "1.0.0"

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

    // PRINTF IMPL
    #ifdef USE_PRINTF_IMPL
    #define PRINTF                  printf
    #endif

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef GPIO_TypeDef gpio_t;
    #endif

    typedef struct muxcfg_t {
        gpio_t* mux1;                       // uart perh instance
    } muxcfg_t;

    #ifdef __cplusplus
}
#endif

#endif // _BSP_MUX_H_
