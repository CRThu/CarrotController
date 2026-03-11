/****************************
 * BSP PSRAM DRIVER
 * CRTHu
 * 2026.03.11
 *****************************/
#pragma once
#ifndef _BSP_PSRAM_H_
#define _BSP_PSRAM_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_PSRAM_VERSION "1.2.1"

    #include <stdint.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "main.h"
    #include "bsp_def.h"
    #include "common.h"
    #include "gpio.h"
    #if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)
    #include "spi.h"
    #elif(CARROT_CONTROLLER_HW == STM32H563_MINI)
    #include "octospi.h"
    #endif

    #define BSP_PSRAM_TIMEOUT   100


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

    void bsp_psram_reset();
    uint8_t bsp_psram_ping();
    int8_t bsp_psram_read(uint32_t addr, uint8_t* data, uint32_t size);
    int8_t bsp_psram_write(uint32_t addr, uint8_t* data, uint32_t size);
    void psram_test();

    #ifdef __cplusplus
}
#endif

#endif // _BSP_PSRAM_H_