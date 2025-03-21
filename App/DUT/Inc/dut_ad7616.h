
/****************************
 * DUT AD7616 BOARD
 * CARROT HU
 * 2025.03.21
 *****************************/
#pragma once
#ifndef _DUT_AD7616_H_
#define _DUT_AD7616_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define DUT_AD7616_VERSION "1.0.0"
    #include "bsp_inc.h"

    extern dut_interface_t ad7616_profiles[];


    void dut_ad7616_init();
    
    #ifdef __cplusplus
}
#endif

#endif // _DUT_AD7616_H_
