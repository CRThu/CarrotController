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

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL
    typedef SPI_HandleTypeDef spi_impl_t;

    #define __SPI_TIMEOUT__                                         (0xFFFF)
    #define SPI_WRITE(__INSTANCE__, __BUF__, __SIZE__)              HAL_SPI_Transmit((__INSTANCE__)->instance, __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define SPI_READ(__INSTANCE__, __BUF__, __SIZE__)               HAL_SPI_Receive((__INSTANCE__)->instance, __BUF__, __SIZE__, __SPI_TIMEOUT__)
    #define SPI_RW(__INSTANCE__, __WRBUF__, __RDBUF__, __SIZE__)    HAL_SPI_TransmitReceive((__INSTANCE__)->instance, __WRBUF__, __RDBUF__, __SIZE__, __SPI_TIMEOUT__)
    
    #endif

    typedef struct spi_t {
        uint16_t id;                            // instance id

        spi_impl_t* instance;                   // instance
    } spi_t;

    extern spi_t spi_instances[];

    #define spi_write       SPI_WRITE
    #define spi_read        SPI_READ
    #define spi_readwrite   SPI_RW

    #ifdef __cplusplus
}
#endif

#endif // _BSP_SPI_H_
