/****************************
 * BSP FT DRIVER
 * CRTHu
 * 2025.08.15
 *****************************/
#pragma once
#ifndef _BSP_FT_H_
#define _BSP_FT_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_FT_VERSION "1.1.0"

    #include <stdint.h>
    #include <stdlib.h>
    #include "main.h"
    #include "io_utils.h"
    #include "cdelay.h"
    #include "comm.h"

    #define BSP_FT_DELAY            cdelay_ns

    #define BSP_FT_T_RD_D           30
    #define BSP_FT_T_RD_RXF         63
    #define BSP_FT_T_WR             30
    #define BSP_FT_T_WR_TXE         33

    // PORT INFO:
    // D15      O       SIWUA   FAST
    // D14      O       WRN     FAST
    // D13      O       RDN     FAST
    // D12      I       TXEN    LOW
    // D11      I       RXFN    LOW
    // D10      I       KEY1    LOW
    // D9       O       LED2    LOW
    // D8       O       LED1    LOW
    // D[7:0]   I/O     D[7:0]  FAST
    #define BSP_FT_IO_PIN_RXFN          GPIO_PIN_11
    #define BSP_FT_IO_PIN_TXEN          GPIO_PIN_12
    #define BSP_FT_IO_PIN_RDN           GPIO_PIN_13
    #define BSP_FT_IO_PIN_WRN           GPIO_PIN_14
    #define BSP_FT_IO_PIN_SIWUA         GPIO_PIN_15

    // DIR[15:0]: OOOI IIOO DDDD DDDD
    #define BSP_FT_DDIR(GPIOx, DDIR)    (WRITE_REG(((GPIO_TypeDef*)GPIOx)->MODER, (DDIR == GPIO_MODE_INPUT) ? 0x54050000UL : 0x54055555UL))
    #define BSP_FT_IO_SPEED(GPIOx)      (WRITE_REG(((GPIO_TypeDef*)GPIOx)->OSPEEDR, 0xFC00FFFFUL))

    #define BSP_FT_DDIR_IN(GPIOx)       BSP_FT_DDIR(GPIOx, GPIO_MODE_INPUT)
    #define BSP_FT_DDIR_OUT(GPIOx)      BSP_FT_DDIR(GPIOx, GPIO_MODE_OUTPUT_PP)
    #define BSP_FT_READ_D(GPIOx)        DB_READ_MASK((GPIO_TypeDef*)GPIOx, 0x00FF)
    #define BSP_FT_WRITE_D(GPIOx, X)    DB_WRITE_MASK((GPIO_TypeDef*)GPIOx, (X), 0x00FF)
    #define BSP_FT_READ_RXFN(GPIOx)     ((IO_READ((GPIO_TypeDef*)GPIOx, BSP_FT_IO_PIN_RXFN) == GPIO_PIN_RESET) ? 0 : 1)
    #define BSP_FT_READ_TXEN(GPIOx)     ((IO_READ((GPIO_TypeDef*)GPIOx, BSP_FT_IO_PIN_TXEN) == GPIO_PIN_RESET) ? 0 : 1)
    #define BSP_FT_WRITE_RDN(GPIOx, X)  (IO_WRITE((GPIO_TypeDef*)GPIOx, BSP_FT_IO_PIN_RDN, ((X) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET))
    #define BSP_FT_WRITE_WRN(GPIOx, X)  (IO_WRITE((GPIO_TypeDef*)GPIOx, BSP_FT_IO_PIN_WRN, ((X) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET))

    comm_t* bsp_ft_create(GPIO_TypeDef* GPIOx);
    void bsp_ft_destory(comm_t* comm);
    void bsp_ft_init(comm_handle handle);
    uint16_t bsp_ft_read(comm_handle handle, uint8_t* buffer, uint16_t size);
    void bsp_ft_write(comm_handle handle, uint8_t* buffer, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_FT_H_
