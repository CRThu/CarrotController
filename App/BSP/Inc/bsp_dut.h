
/****************************
 * BSP DUT
 * CARROT HU
 * 2025.02.24
 *****************************/
#pragma once
#ifndef _BSP_DUT_H_
#define _BSP_DUT_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_DUT_VERSION "1.0.0"

    #include "bsp_inc.h"


    /*
        USAGE:

        INITIAL:

     */
    #define DUT_MAX_PERH_NUM                (8)

    typedef struct dut_interface_t
    {
        uint16_t id;                        // dut id
        const char* name;                   // dut name

        uint16_t preset_id;                 // dut preset id
        const char* preset_name;            // dut preset name

        io_t* pin_configs;                  // btb pin configs
        uint32_t switch_value;              // switch value

        void* perh[DUT_MAX_PERH_NUM];       // perh instances
    } dut_interface_t;


    gpio_config_status_t dut_init(dut_interface_t* dut);
    io_t* dut_get_io(dut_interface_t* dut, const char* name);
    io_t* dut_get_io_id(dut_interface_t* dut, uint8_t id, const char* name);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_DUT_H_
