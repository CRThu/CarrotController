/****************************
 * BSP SW
 * CARROT HU
 * 2025.09.11
 *****************************/
#pragma once
#ifndef _BSP_SW_H_
#define _BSP_SW_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define BSP_SW_VERSION "1.0.1"

    #include <stdint.h>
    #include "io_utils.h"
    #include "main.h"
    #include "bsp_def.h"

    #if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)

    /*
        USAGE:
        bsp_sw_enable  ( BSP_SW_BTB_CLK1_TO_MCU_PA01     | BSP_SW_BTB_CLK3_TO_MCU_PC02       );
        bsp_sw_disable ( BSP_SW_BTB_CLK1_TO_SI5351_PLL1  | BSP_SW_BTB_CLK3_TO_SI5351_PLL2    );
        bsp_sw_set     ( BSP_SW_DEFAULT )
        uint16_t sw_status = bsp_sw_get_status();

        INITIAL:
        bsp_sw_default();
     */

    #define BSP_SW01                                (1L << 0)
    #define BSP_SW02                                (1L << 1)
    #define BSP_SW03                                (1L << 2)
    #define BSP_SW04                                (1L << 3)
    #define BSP_SW05                                (1L << 4)
    #define BSP_SW06                                (1L << 5)
    #define BSP_SW07                                (1L << 6)
    #define BSP_SW08                                (1L << 7)
    #define BSP_SW09                                (1L << 8)
    #define BSP_SW10                                (1L << 9)
    #define BSP_SW11                                (1L << 10)
    #define BSP_SW12                                (1L << 11)


    #define BSP_SW_BTB_CLK1_TO_MCU_PA01             BSP_SW01
    #define BSP_SW_BTB_CLK1_TO_SI5351_PLL1          BSP_SW02
    #define BSP_SW_BTB_CLK2_TO_MCU_PB03             BSP_SW03
    #define BSP_SW_BTB_SPIA_SCK_TO_MCU_PB03         BSP_SW04
    #define BSP_SW_MCU_PB03_TO_MCU_PC10             BSP_SW05
    #define BSP_SW_BTB_SPIB_SCK_TO_MCU_PC10         BSP_SW06
    #define BSP_SW_BTB_CLK3_TO_MCU_PC02             BSP_SW07
    #define BSP_SW_BTB_CLK3_TO_SI5351_PLL2          BSP_SW08
    #define BSP_SW_BTB_CLK4_TO_MCU_PC03             BSP_SW09
    #define BSP_SW_BTB_CLK4_TO_SI5351_PLL3          BSP_SW10
    #define BSP_SW_BTB_CLK5_TO_MCU_PA02             BSP_SW11
    #define BSP_SW_BTB_CLK6_TO_MCU_PA03             BSP_SW12

    #define BSP_SW_DEFAULT                         (  BSP_SW_BTB_CLK1_TO_MCU_PA01 \
                                                    | BSP_SW_BTB_SPIA_SCK_TO_MCU_PB03 \
                                                    | BSP_SW_BTB_SPIB_SCK_TO_MCU_PC10 \
                                                    | BSP_SW_BTB_CLK3_TO_MCU_PC02 \
                                                    | BSP_SW_BTB_CLK4_TO_MCU_PC03 \
                                                    | BSP_SW_BTB_CLK5_TO_MCU_PA02 \
                                                    | BSP_SW_BTB_CLK6_TO_MCU_PA03 \
                                                    )

    static inline void bsp_sw_enable(uint16_t mask)
    {
        if (mask & BSP_SW01)    IO_WRITE(MUX_SEL01_GPIO_Port, MUX_SEL01_Pin, 1);
        if (mask & BSP_SW02)    IO_WRITE(MUX_SEL02_GPIO_Port, MUX_SEL02_Pin, 1);
        if (mask & BSP_SW03)    IO_WRITE(MUX_SEL03_GPIO_Port, MUX_SEL03_Pin, 1);
        if (mask & BSP_SW04)    IO_WRITE(MUX_SEL04_GPIO_Port, MUX_SEL04_Pin, 1);
        if (mask & BSP_SW05)    IO_WRITE(MUX_SEL05_GPIO_Port, MUX_SEL05_Pin, 1);
        if (mask & BSP_SW06)    IO_WRITE(MUX_SEL06_GPIO_Port, MUX_SEL06_Pin, 1);
        if (mask & BSP_SW07)    IO_WRITE(MUX_SEL07_GPIO_Port, MUX_SEL07_Pin, 1);
        if (mask & BSP_SW08)    IO_WRITE(MUX_SEL08_GPIO_Port, MUX_SEL08_Pin, 1);
        if (mask & BSP_SW09)    IO_WRITE(MUX_SEL09_GPIO_Port, MUX_SEL09_Pin, 1);
        if (mask & BSP_SW10)    IO_WRITE(MUX_SEL10_GPIO_Port, MUX_SEL10_Pin, 1);
        if (mask & BSP_SW11)    IO_WRITE(MUX_SEL11_GPIO_Port, MUX_SEL11_Pin, 1);
        if (mask & BSP_SW12)    IO_WRITE(MUX_SEL12_GPIO_Port, MUX_SEL12_Pin, 1);
    }

    static inline void bsp_sw_disable(uint16_t mask)
    {
        if (mask & BSP_SW01)    IO_WRITE(MUX_SEL01_GPIO_Port, MUX_SEL01_Pin, 0);
        if (mask & BSP_SW02)    IO_WRITE(MUX_SEL02_GPIO_Port, MUX_SEL02_Pin, 0);
        if (mask & BSP_SW03)    IO_WRITE(MUX_SEL03_GPIO_Port, MUX_SEL03_Pin, 0);
        if (mask & BSP_SW04)    IO_WRITE(MUX_SEL04_GPIO_Port, MUX_SEL04_Pin, 0);
        if (mask & BSP_SW05)    IO_WRITE(MUX_SEL05_GPIO_Port, MUX_SEL05_Pin, 0);
        if (mask & BSP_SW06)    IO_WRITE(MUX_SEL06_GPIO_Port, MUX_SEL06_Pin, 0);
        if (mask & BSP_SW07)    IO_WRITE(MUX_SEL07_GPIO_Port, MUX_SEL07_Pin, 0);
        if (mask & BSP_SW08)    IO_WRITE(MUX_SEL08_GPIO_Port, MUX_SEL08_Pin, 0);
        if (mask & BSP_SW09)    IO_WRITE(MUX_SEL09_GPIO_Port, MUX_SEL09_Pin, 0);
        if (mask & BSP_SW10)    IO_WRITE(MUX_SEL10_GPIO_Port, MUX_SEL10_Pin, 0);
        if (mask & BSP_SW11)    IO_WRITE(MUX_SEL11_GPIO_Port, MUX_SEL11_Pin, 0);
        if (mask & BSP_SW12)    IO_WRITE(MUX_SEL12_GPIO_Port, MUX_SEL12_Pin, 0);
    }

    static inline void bsp_sw_set(uint16_t mask)
    {
        IO_WRITE(MUX_SEL01_GPIO_Port, MUX_SEL01_Pin, (mask & BSP_SW01) ? 1 : 0);
        IO_WRITE(MUX_SEL02_GPIO_Port, MUX_SEL02_Pin, (mask & BSP_SW02) ? 1 : 0);
        IO_WRITE(MUX_SEL03_GPIO_Port, MUX_SEL03_Pin, (mask & BSP_SW03) ? 1 : 0);
        IO_WRITE(MUX_SEL04_GPIO_Port, MUX_SEL04_Pin, (mask & BSP_SW04) ? 1 : 0);
        IO_WRITE(MUX_SEL05_GPIO_Port, MUX_SEL05_Pin, (mask & BSP_SW05) ? 1 : 0);
        IO_WRITE(MUX_SEL06_GPIO_Port, MUX_SEL06_Pin, (mask & BSP_SW06) ? 1 : 0);
        IO_WRITE(MUX_SEL07_GPIO_Port, MUX_SEL07_Pin, (mask & BSP_SW07) ? 1 : 0);
        IO_WRITE(MUX_SEL08_GPIO_Port, MUX_SEL08_Pin, (mask & BSP_SW08) ? 1 : 0);
        IO_WRITE(MUX_SEL09_GPIO_Port, MUX_SEL09_Pin, (mask & BSP_SW09) ? 1 : 0);
        IO_WRITE(MUX_SEL10_GPIO_Port, MUX_SEL10_Pin, (mask & BSP_SW10) ? 1 : 0);
        IO_WRITE(MUX_SEL11_GPIO_Port, MUX_SEL11_Pin, (mask & BSP_SW11) ? 1 : 0);
        IO_WRITE(MUX_SEL12_GPIO_Port, MUX_SEL12_Pin, (mask & BSP_SW12) ? 1 : 0);
    }

    static inline uint16_t bsp_sw_get_status()
    {
        uint16_t status = 0;

        if (IO_READ(MUX_SEL01_GPIO_Port, MUX_SEL01_Pin)) status |= BSP_SW01;
        if (IO_READ(MUX_SEL02_GPIO_Port, MUX_SEL02_Pin)) status |= BSP_SW02;
        if (IO_READ(MUX_SEL03_GPIO_Port, MUX_SEL03_Pin)) status |= BSP_SW03;
        if (IO_READ(MUX_SEL04_GPIO_Port, MUX_SEL04_Pin)) status |= BSP_SW04;
        if (IO_READ(MUX_SEL05_GPIO_Port, MUX_SEL05_Pin)) status |= BSP_SW05;
        if (IO_READ(MUX_SEL06_GPIO_Port, MUX_SEL06_Pin)) status |= BSP_SW06;
        if (IO_READ(MUX_SEL07_GPIO_Port, MUX_SEL07_Pin)) status |= BSP_SW07;
        if (IO_READ(MUX_SEL08_GPIO_Port, MUX_SEL08_Pin)) status |= BSP_SW08;
        if (IO_READ(MUX_SEL09_GPIO_Port, MUX_SEL09_Pin)) status |= BSP_SW09;
        if (IO_READ(MUX_SEL10_GPIO_Port, MUX_SEL10_Pin)) status |= BSP_SW10;
        if (IO_READ(MUX_SEL11_GPIO_Port, MUX_SEL11_Pin)) status |= BSP_SW11;
        if (IO_READ(MUX_SEL12_GPIO_Port, MUX_SEL12_Pin)) status |= BSP_SW12;

        return status;
    }

    static inline void bsp_sw_default()
    {
        bsp_sw_set(BSP_SW_DEFAULT);
    }

    #endif

    #ifdef __cplusplus
}
#endif

#endif // _BSP_SW_H_
