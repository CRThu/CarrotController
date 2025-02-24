
/****************************
 * BSP INC
 * CARROT HU
 * 2025.02.24
 *****************************/
#pragma once
#ifndef _BSP_INC_H_
#define _BSP_INC_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define BSP_INC_VERSION "1.0.0"

    #define USE_PRINTF_IMPL
    #define USE_STM32H5_HAL_IMPL

    #ifdef USE_PRINTF_IMPL
    #include <stdio.h>
    #endif

    #ifdef USE_STM32H5_HAL_IMPL
    #include "stm32h5xx_hal.h"
    #endif
		
    #include "bsp_io.h"
    #include "bsp_spi.h"
    #include "bsp_dut.h"
    #include "bsp_mux.h"

     // PRINTF IMPL
    #ifdef USE_PRINTF_IMPL
    #define PRINTF                  printf
    #endif


    #ifdef __cplusplus
}
#endif

#endif // _BSP_INC_H_
