
/****************************
 * COMMON
 * CARROT HU
 * 2025.03.27
 *****************************/
#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define COMMON_VERSION "1.0.1"

    #define USE_CDELAY_IMPL
    #define USE_PRINTF_IMPL
    #define USE_IO_IMPL
    #define USE_STM32H5_HAL_IMPL

    /* MODULE INCLUDE */
    #ifdef USE_CDELAY_IMPL
    #include "cdelay.h"
    #endif

    #ifdef USE_IO_IMPL
    #include "io_utils.h"
    #endif

    #ifdef USE_STM32H5_HAL_IMPL
    #include "stm32h5xx_hal.h"
    #endif

    /* DELAY IMPL */
    #ifdef USE_CDELAY_IMPL
    #define delay_ns                                cdelay_ns
    #define delay_us                                cdelay_us
    #define delay_ms                                cdelay_ms
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

#endif // _COMMON_H_
