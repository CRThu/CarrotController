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

    #define BSP_FT_IO_PORT          GPIOF
    #define BSP_FT_IO_PIN_D0        GPIO_PIN_0
    #define BSP_FT_IO_PIN_D1        GPIO_PIN_1
    #define BSP_FT_IO_PIN_D2        GPIO_PIN_2
    #define BSP_FT_IO_PIN_D3        GPIO_PIN_3
    #define BSP_FT_IO_PIN_D4        GPIO_PIN_4
    #define BSP_FT_IO_PIN_D5        GPIO_PIN_5
    #define BSP_FT_IO_PIN_D6        GPIO_PIN_6
    #define BSP_FT_IO_PIN_D7        GPIO_PIN_7
    #define BSP_FT_IO_PIN_RXFN      GPIO_PIN_11
    #define BSP_FT_IO_PIN_TXEN      GPIO_PIN_12
    #define BSP_FT_IO_PIN_RDN       GPIO_PIN_13
    #define BSP_FT_IO_PIN_WRN       GPIO_PIN_14
    #define BSP_FT_IO_PIN_SIWUA     GPIO_PIN_15


    #define BSP_FT_DELAY            delay_ns

    #define BSP_FT_T_RD_D           30
    #define BSP_FT_T_RD_RXF         63
    #define BSP_FT_T_WR             30
    #define BSP_FT_T_WR_TXE         33

    // FIX DIR:
    // D15      O       SIWUA   FAST
    // D14      O       WRN     FAST
    // D13      O       RDN     FAST
    // D12      I       TXEN    LOW
    // D11      I       RXFN    LOW
    // D10      I       KEY1    LOW
    // D9       O       LED2    LOW
    // D8       O       LED1    LOW
    // D[7:0]   I/O     D[7:0]  FAST

    // DIR[15:0]: OOOI IIOO DDDD DDDD
    #define BSP_FT_DDIR(DDIR)       (WRITE_REG(BSP_FT_IO_PORT->MODER, (DDIR == IO_TYPE_IN) ? 0x54050000UL : 0x54055555UL))
    #define BSP_FT_IO_SPEED()       (WRITE_REG(BSP_FT_IO_PORT->OSPEEDR, 0xFC00FFFFUL))

    #define BSP_FT_DDIR_IN()        BSP_FT_DDIR(IO_TYPE_IN)
    #define BSP_FT_DDIR_OUT()       BSP_FT_DDIR(IO_TYPE_OUT)
    #define BSP_FT_READ_D()         DB_READ_MASK(BSP_FT_IO_PORT, 0x00FF)
    #define BSP_FT_WRITE_D(X)       DB_WRITE_MASK(BSP_FT_IO_PORT, (X), 0x00FF)
    #define BSP_FT_READ_RXFN()      ((IO_READ(BSP_FT_IO_PORT, BSP_FT_IO_PIN_RXFN) == GPIO_PIN_RESET) ? 0 : 1)
    #define BSP_FT_READ_TXEN()      ((IO_READ(BSP_FT_IO_PORT, BSP_FT_IO_PIN_TXEN) == GPIO_PIN_RESET) ? 0 : 1)
    #define BSP_FT_WRITE_RDN(X)     (IO_WRITE(BSP_FT_IO_PORT, BSP_FT_IO_PIN_RDN, ((X) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET))
    #define BSP_FT_WRITE_WRN(X)     (IO_WRITE(BSP_FT_IO_PORT, BSP_FT_IO_PIN_WRN, ((X) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET))

    void bsp_ft_init();
    uint16_t bsp_ft_read(uint8_t* buffer, uint16_t size);
    void bsp_ft_write(uint8_t* buffer, uint16_t size);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_FT_H_
