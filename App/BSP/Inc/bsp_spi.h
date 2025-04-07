/****************************
 * BSP SPI
 * CARROT HU
 * 2025.02.24
 *****************************/
#pragma once
#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_SPI_VERSION "1.0.0"

    #include "bsp_inc.h"

    #include "spi.h"
    //#include "stm32h5xx_hal_spi.h"

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef SPI_HandleTypeDef spi_t;

    #define __SPI_TIMEOUT__                                         (0xFFFF)
    #define SPI_WRITE(__INSTANCE__, __BUF__, __SIZE__)              HAL_SPI_Transmit((__INSTANCE__), __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define SPI_READ(__INSTANCE__, __BUF__, __SIZE__)               HAL_SPI_Receive((__INSTANCE__), __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define SPI_RW(__INSTANCE__, __WRBUF__, __RDBUF__, __SIZE__)    HAL_SPI_TransmitReceive((__INSTANCE__), __WRBUF__, __RDBUF__, __SIZE__, __SPI_TIMEOUT__)

    #endif
    extern const void* const spi_instances[];

    #define spi_write                   SPI_WRITE
    #define spi_read                    SPI_READ
    #define spi_readwrite               SPI_RW

    #define BTB_SPIA                    hspi1
    #define BTB_SPIB                    hspi3

    #define BSP_SPI_MODE_SCK_IN         (1 << 4)
    #define BSP_SPI_MODE_CS_IN          (1 << 3)
    #define BSP_SPI_MODE_CS_EN          (1 << 2)
    #define BSP_SPI_MODE_RX_EN          (1 << 1)
    #define BSP_SPI_MODE_TX_EN          (1 << 0)

    /* SPI MODE = ++++++++
                  ---kcCRT

                k: SCK DIR  (0:out, 1:in)
                c: CS DIR   (0:out, 1:in)
                C: CS EN
                R: RX EN
                T: TX EN
    */
    typedef enum bsp_spi_mode {
        /* BSP_SPI_MODE_OFF when not use spi perh */
        BSP_SPI_MODE_OFF = 0,
        /* BSP_SPI_MODE_CRT when use spi cs, sck, rx, tx */
        BSP_SPI_MODE_CRT = BSP_SPI_MODE_CS_EN | BSP_SPI_MODE_RX_EN | BSP_SPI_MODE_TX_EN,
        /* BSP_SPI_MODE_CR_CSIN_SCKIN when use spi cs(in), sck(in), rx */
        BSP_SPI_MODE_CR_CSIN_SCKIN = BSP_SPI_MODE_CS_EN | BSP_SPI_MODE_RX_EN | BSP_SPI_MODE_CS_IN | BSP_SPI_MODE_SCK_IN,
    } bsp_spi_mode;


    spi_t* bsp_get_spi_instance(uint8_t index);
    void bsp_spi_init(uint8_t index, bsp_spi_mode spi_mode);
    void bsp_spi_init_all(bsp_spi_mode spi_mode);


    #ifdef __cplusplus
}
#endif

#endif // _BSP_SPI_H_
