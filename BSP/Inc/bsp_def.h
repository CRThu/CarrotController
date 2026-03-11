/****************************
 * BSP DEF
 * CRTHu
 * 2025.09.11
 *****************************/
#pragma once
#ifndef _BSP_DEF_H_
#define _BSP_DEF_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_DEF_VERSION "1.0.0"

    /* MODIFY HERE*/
    /* USING STM32H563_CONTROLLER BOARD */
    /* PSRAM */
    // #define BSP_PSRAM_U7_EN
    #define BSP_PSRAM_U8_EN


    /* USING STM32H563_MINI BOARD */


    /* USING LIBRARY */
    #define USING_BSP_DRIVER
    #define USING_REMOTE_CONTROL

    #include "main.h"

    /* BOARD VERSION */
    #define STM32H563_CONTROLLER    (20250107UL)
    #define STM32H563_MINI          (20250905UL)
    
    #ifdef __cplusplus
}
#endif

#endif // _BSP_DEF_H_
