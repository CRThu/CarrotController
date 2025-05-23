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
    #define BSP_FT_T_RD_RXF         14
    #define BSP_FT_T_WR             30

    // FIX DIR:
    // D15  O   SIWUA
    // D14  O   WRN
    // D13  O   RDN
    // D12  I   TXEN
    // D11  I   RXFN
    // D10  I   KEY1
    // D9   O   LED2
    // D8   O   LED1

    // DIR[15:0]: OOOI IIOO DDDD DDDD
    #define BSP_FT_DDIR(DDIR)       (WRITE_REG((GPIOx)->MODER, (DDIR == IO_TYPE_IN) ? 0x54050000UL : 0x54055555UL))

    #define BSP_FT_DDIR_IN()        BSP_FT_DDIR(IO_TYPE_IN)
    #define BSP_FT_DDIR_OUT()       BSP_FT_DDIR(IO_TYPE_OUT)
    #define BSP_FT_READ_RXF()       ((IO_READ(BSP_FT_IO_PORT, BSP_FT_IO_PIN_RXFN) == GPIO_PIN_RESET) ? 1 : 0)
    #define BSP_FT_READ_TXE()       ((IO_READ(BSP_FT_IO_PORT, BSP_FT_IO_PIN_TXEN) == GPIO_PIN_RESET) ? 1 : 0)
    #define BSP_FT_WRITE_RD(X)      (IO_WRITE(BSP_FT_IO_PORT, BSP_FT_IO_PIN_RDN, ((X) == 1) ? GPIO_PIN_RESET : GPIO_PIN_SET))
    #define BSP_FT_WRITE_WR(X)      (IO_WRITE(BSP_FT_IO_PORT, BSP_FT_IO_PIN_WRN, ((X) == 1) ? GPIO_PIN_RESET : GPIO_PIN_SET))

    void bsp_ft_init();

    #ifdef __cplusplus
}
#endif

#endif // _BSP_FT_H_
