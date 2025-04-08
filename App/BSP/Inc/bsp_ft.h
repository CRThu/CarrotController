/****************************
 * BSP FT DRIVER
 * CRTHu
 * 2025.04.08
 *****************************/
#pragma once
#ifndef _BSP_FT_H_
#define _BSP_FT_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_FT_VERSION "1.0.0"


    #include "bsp_inc.h"

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    #endif

    void bsp_ft_init();

    #ifdef __cplusplus
}
#endif

#endif // _BSP_FT_H_
