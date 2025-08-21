/****************************
 * BSP PSRAM DRIVER
 * CRTHu
 * 2025.08.20
 *****************************/
#pragma once
#ifndef _BSP_PSRAM_H_
#define _BSP_PSRAM_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_PSRAM_VERSION "1.0.0"

    #include <stdint.h>
    #include <stdlib.h>
    #include "main.h"
    #include "spi.h"
    #include "gpio.h"

    // #define BSP_PSRAM_U7_EN
    #define BSP_PSRAM_U8_EN

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

    #define BSP_PSRAM_TIMEOUT   100

    static inline void bsp_psram_reset()
    {
        #ifdef BSP_PSRAM_SPI
        uint8_t cmd = 0x66;
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&BSP_PSRAM_SPI, &cmd, 1, 0xFFFF);
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
        cmd = 0x99;
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&BSP_PSRAM_SPI, &cmd, 1, 0xFFFF);
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
        #endif
    }

    static inline uint8_t bsp_psram_ping()
    {
        #ifdef BSP_PSRAM_SPI
        /* RX: 07 00 00 00 0D 5D 53 15 3C 6D 71 AA 0D 5D */
        uint8_t eid[14] = { 0 };
        eid[0] = 0x9F;
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(&BSP_PSRAM_SPI, eid, eid, sizeof(eid), 0xFFFF);
        HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);
        return (eid[5] == 0x5D);
        #else
        return 0x00;
        #endif
    }


    static inline int8_t bsp_psram_read(uint32_t addr, uint8_t* data, uint32_t size)
    {
        #ifdef BSP_PSRAM_SPI
        uint8_t prefix[5] = { 0 };

        uint32_t curr_addr = addr;
        uint32_t curr_size = 0;
        uint32_t remain_size = size;

        while (remain_size > 0)
        {
            if (curr_addr % 1024 == 0)
            {
                // aligned
                curr_size = remain_size >= 1024 ? 1024 : remain_size;
            }
            else
            {
                // unaligned
                curr_size = (remain_size >= (1024 - curr_addr % 1024)) ? (1024 - curr_addr % 1024) : remain_size;
            }

            prefix[0] = 0x0B;
            prefix[1] = curr_addr >> 16;
            prefix[2] = curr_addr >> 8;
            prefix[3] = curr_addr;
            prefix[4] = 0x00;

            HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
            HAL_SPI_Transmit(&BSP_PSRAM_SPI, prefix, sizeof(prefix), 0xFFFF);
            //HAL_SPI_Receive(&BSP_PSRAM_SPI, data, curr_size, 0xFFFF);
            HAL_SPI_Receive_DMA(&BSP_PSRAM_SPI, data, curr_size);

            // wait for transfer
            uint32_t tickstart = HAL_GetTick();
            while (HAL_SPI_GetState(&BSP_PSRAM_SPI) != HAL_SPI_STATE_READY)
            {
                if ((HAL_GetTick() - tickstart) >= BSP_PSRAM_TIMEOUT)
                {
                    return -2;
                }
            }

            HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);

            remain_size -= curr_size;
            curr_addr += curr_size;
            data += curr_size;
        }
        return 0;
        #else
        return -1;
        #endif
    }

    static inline int8_t bsp_psram_write(uint32_t addr, uint8_t* data, uint32_t size)
    {
        #ifdef BSP_PSRAM_SPI
        uint8_t prefix[4] = { 0 };

        uint32_t curr_addr = addr;
        uint32_t curr_size = 0;
        uint32_t remain_size = size;

        while (remain_size > 0)
        {
            if (curr_addr % 1024 == 0)
            {
                // aligned
                curr_size = remain_size >= 1024 ? 1024 : remain_size;
            }
            else
            {
                // unaligned
                curr_size = (remain_size >= (1024 - curr_addr % 1024)) ? (1024 - curr_addr % 1024) : remain_size;
            }

            prefix[0] = 0x02;
            prefix[1] = curr_addr >> 16;
            prefix[2] = curr_addr >> 8;
            prefix[3] = curr_addr;

            HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_RESET);
            HAL_SPI_Transmit(&BSP_PSRAM_SPI, prefix, sizeof(prefix), 0xFFFF);
            //HAL_SPI_Transmit(&BSP_PSRAM_SPI, data, curr_size, 0xFFFF);
            HAL_SPI_Transmit_DMA(&BSP_PSRAM_SPI, data, curr_size);

            // wait for transfer
            uint32_t tickstart = HAL_GetTick();
            while (HAL_SPI_GetState(&BSP_PSRAM_SPI) != HAL_SPI_STATE_READY)
            {
                if ((HAL_GetTick() - tickstart) >= BSP_PSRAM_TIMEOUT)
                {
                    return -2;
                }
            }

            HAL_GPIO_WritePin(BSP_PSRAM_NSS_PORT, BSP_PSRAM_NSS_PIN, GPIO_PIN_SET);

            remain_size -= curr_size;
            curr_addr += curr_size;
            data += curr_size;
        }
        return 0;
        #else
        return -1;
        #endif
    }

    #ifdef __cplusplus
    }
#endif

#endif // _BSP_PSRAM_H_