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

    #include "main.h"

    /* MODIFY HERE WHEN USING STM32H563_CONTROLLER */
    /* PSRAM */
    // #define BSP_PSRAM_U7_EN
    #define BSP_PSRAM_U8_EN


    /* MODIFY HERE WHEN USING STM32H563_MINI */


    /* BOARD VERSION */
    #define STM32H563_CONTROLLER    (20250107UL)
    #define STM32H563_MINI          (20250905UL)

    #if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)

        #ifdef BSP_PSRAM_U7_EN
        #define BSP_PSRAM_SPI       hspi4
        #define BSP_PSRAM_NSS_PORT  SPI4_NSS1_GPIO_Port
        #define BSP_PSRAM_NSS_PIN   SPI4_NSS1_Pin
        #endif
        #ifdef BSP_PSRAM_U8_EN
        #define BSP_PSRAM_SPI       hspi4
        #define BSP_PSRAM_NSS_PORT  SPI4_NSS2_GPIO_Port
        #define BSP_PSRAM_NSS_PIN   SPI4_NSS2_Pin
        #endif
    #elif(CARROT_CONTROLLER_HW == STM32H563_MINI)
        // OCTOSPI
        #define BSP_PSRAM_OCTOSPI   hospi1
    #endif

    #ifdef __cplusplus
}
#endif

#endif // _BSP_DEF_H_
