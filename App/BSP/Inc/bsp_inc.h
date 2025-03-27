
/****************************
 * BSP INC
 * CARROT HU
 * 2025.03.27
 *****************************/
#pragma once
#ifndef _BSP_INC_H_
#define _BSP_INC_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define BSP_INC_VERSION "1.0.0"

    #define USE_CDELAY_IMPL
    #define USE_PRINTF_IMPL
    #define USE_STM32H5_HAL_IMPL

    /* MODULE INCLUDE */
    #ifdef USE_CDELAY_IMPL
    #include "cdelay.h"
    #endif

    #ifdef USE_PRINTF_IMPL
    #include <stdio.h>
    #endif

    #ifdef USE_STM32H5_HAL_IMPL
    #include "stm32h5xx_hal.h"
    #endif

    /* BSP MODULE INCLUDE */
    #include "bsp_io.h"
    #include "bsp_spi.h"
    #include "bsp_tim.h"
    #include "bsp_dut.h"
    #include "bsp_mux.h"

    /* DELAY IMPL */ 
    #ifdef USE_CDELAY_IMPL
    #define delay_ns                                cdelay_ns
    #define delay_us                                cdelay_us
    #define delay_ms                                cdelay_ms

    #define DELAY_NS                                delay_ns
    #define DELAY_US                                delay_us
    #define DELAY_MS                                delay_ms
    #endif

    /* PRINTF IMPL */ 
    #ifdef USE_PRINTF_IMPL
    #define PRINTF                                  printf
    #endif

    /* INLINE IMPL */ 
    /* from cmsis_armclang.h */
    #ifndef   __INLINE
    #define __INLINE                                __inline
    #endif
    #ifndef   __FORCEINLINE
    #define __FORCEINLINE                           __attribute__((always_inline)) __inline
    #endif

    /* BREAKPOINT IMPL */ 
    /* for debug */
    #ifndef   __DBG_BREAKPOINT
    #define __DBG_BREAKPOINT                        __NOP
    #endif

    #ifdef __cplusplus
}
#endif

#endif // _BSP_INC_H_
