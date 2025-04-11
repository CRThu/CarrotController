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

    #define __SPI_TIMEOUT__                                             (100)
    #define BSP_SPI_WRITE(__INSTANCE__, __BUF__, __SIZE__)              HAL_SPI_TransmitReceive((__INSTANCE__), __BUF__, __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define BSP_SPI_READ(__INSTANCE__, __BUF__, __SIZE__)               HAL_SPI_TransmitReceive((__INSTANCE__), __BUF__, __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define BSP_SPI_RW(__INSTANCE__, __WRBUF__, __RDBUF__, __SIZE__)    HAL_SPI_TransmitReceive((__INSTANCE__), __WRBUF__, __RDBUF__, __SIZE__, __SPI_TIMEOUT__)

    #endif

    #define bsp_spi_write                   BSP_SPI_WRITE
    #define bsp_spi_read                    BSP_SPI_READ
    #define bsp_spi_readwrite               BSP_SPI_RW

    #define BTB_SPIA                        hspi1
    #define BTB_SPIB                        hspi3

    #define BSP_SPI_MODE_SCK_IN             (1 << 4)
    #define BSP_SPI_MODE_CS_IN              (1 << 3)
    #define BSP_SPI_MODE_CS_EN              (1 << 2)
    #define BSP_SPI_MODE_RX_EN              (1 << 1)
    #define BSP_SPI_MODE_TX_EN              (1 << 0)

    /* SPI MODE = ++++++++
                  ---kcCRT

                k: SCK DIR  (0:out, 1:in)
                c: CS DIR   (0:out, 1:in)
                C: CS EN
                R: RX EN
                T: TX EN
    */
    typedef enum bsp_spi_io_mode {
        /* BSP_SPI_IO_MODE_OFF when not use spi perh */
        BSP_SPI_IO_MODE_OFF = 0,
        /* BSP_SPI_IO_MODE_CRT when use spi cs, sck, rx, tx */
        BSP_SPI_IO_MODE_CRT = BSP_SPI_MODE_CS_EN | BSP_SPI_MODE_RX_EN | BSP_SPI_MODE_TX_EN,
        /* BSP_SPI_IO_MODE_CR_CSIN_SCKIN when use spi cs(in), sck(in), rx */
        BSP_SPI_IO_MODE_CR_CSIN_SCKIN = BSP_SPI_MODE_CS_EN | BSP_SPI_MODE_RX_EN | BSP_SPI_MODE_CS_IN | BSP_SPI_MODE_SCK_IN,
    } bsp_spi_io_mode;


    /*
    SPI_CFG2_MASTER         SPI_MODE_SLAVE      SPI_CFG2_MASTER
    SPI_CFG2_CPHA           SPI_PHASE_1EDGE     SPI_PHASE_2EDGE
    SPI_CFG2_CPOL           SPI_POLARITY_LOW    SPI_POLARITY_HIGH
    */
    typedef enum bsp_spi_mode {
        BSP_SPI_MODE_SLAVE = SPI_MODE_SLAVE,
        BSP_SPI_MODE_MASTER = SPI_MODE_MASTER
    } bsp_spi_mode;

    typedef enum bsp_spi_data_size {
        BSP_SPI_DATA_SIZE_8B = SPI_DATASIZE_8BIT,
        BSP_SPI_DATA_SIZE_16B = SPI_DATASIZE_16BIT,
        BSP_SPI_DATA_SIZE_24B = SPI_DATASIZE_24BIT,
        BSP_SPI_DATA_SIZE_32B = SPI_DATASIZE_32BIT
    } bsp_spi_data_size;

    typedef enum bsp_spi_clk_psc {
        BSP_SPI_CLK_PSC_2 = SPI_BAUDRATEPRESCALER_2,
        BSP_SPI_CLK_PSC_4 = SPI_BAUDRATEPRESCALER_4,
        BSP_SPI_CLK_PSC_8 = SPI_BAUDRATEPRESCALER_8,
        BSP_SPI_CLK_PSC_16 = SPI_BAUDRATEPRESCALER_16,
        BSP_SPI_CLK_PSC_32 = SPI_BAUDRATEPRESCALER_32,
        BSP_SPI_CLK_PSC_64 = SPI_BAUDRATEPRESCALER_64,
        BSP_SPI_CLK_PSC_128 = SPI_BAUDRATEPRESCALER_128,
        BSP_SPI_CLK_PSC_256 = SPI_BAUDRATEPRESCALER_256,
    } bsp_spi_clk_psc;

    typedef enum bsp_spi_cpha {
        BSP_SPI_CPHA_0 = SPI_PHASE_1EDGE,
        BSP_SPI_CPHA_1 = SPI_PHASE_2EDGE
    } bsp_spi_cpha;

    typedef enum bsp_spi_cpol {
        BSP_SPI_CPOL_0 = SPI_POLARITY_LOW,
        BSP_SPI_CPOL_1 = SPI_POLARITY_HIGH
    } bsp_spi_cpol;

    spi_t* bsp_get_spi_instance(uint8_t index);
    void bsp_spi_io_config(uint8_t index, bsp_spi_io_mode spi_io_mode);
    void bsp_spi_io_config_all(bsp_spi_io_mode spi_io_mode);
    void bsp_spi_perh_config(uint8_t index, bsp_spi_mode master, bsp_spi_data_size datasize, bsp_spi_clk_psc psc, bsp_spi_cpha cpha, bsp_spi_cpol cpol);


    #ifdef __cplusplus
}
#endif

#endif // _BSP_SPI_H_
