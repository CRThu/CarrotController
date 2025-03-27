
/****************************
 * DUT DAC11001 BOARD
 * CARROT HU
 * 2025.02.24
 *****************************/
#pragma once
#ifndef _DUT_DAC11001_H_
#define _DUT_DAC11001_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define DUT_DAC11001_VERSION "1.0.0"
    #include "bsp_inc.h"

    /*
        USAGE:

        HAL_Delay(1000);
        dut_dac11001_set_code(0, 0x00000); // MIN
        dut_dac11001_set_code(1, 0xFFFFF); // MAX
        HAL_Delay(1000);
        dut_dac11001_set_code(0, 0x7FFFF); // MID
        dut_dac11001_set_code(1, 0x7FFFF); // MID
        HAL_Delay(1000);
        dut_dac11001_set_code(0, 0xFFFFF); // MAX
        dut_dac11001_set_code(1, 0x00000); // MIN
        HAL_Delay(1000);
        dut_dac11001_set_code(0, 0x7FFFF); // MID
        dut_dac11001_set_code(1, 0x7FFFF); // MID

        
        INITIAL:

     */


    extern dut_interface_t dac11001_profile;


    void dut_dac11001_init();
    void dut_dac11001_set_spi(uint8_t id, spi_t* hspi);
    void dut_dac11001_reg_write(uint8_t id, uint8_t addr, uint32_t data);
    void dut_dac11001_set_code(uint8_t id, uint32_t code);



    #ifdef __cplusplus
}
#endif

#endif // _DUT_DAC11001_H_
