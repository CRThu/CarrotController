/****************************
 * BSP MUX
 * CARROT HU
 * 2025.02.19
 *****************************/
#pragma once
#ifndef _BSP_MUX_H_
#define _BSP_MUX_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define BSP_MUX_VERSION "1.0.0"

    #include "bsp_inc.h"

    /*
        USAGE:

        INITIAL:

     */

    typedef uint16_t io_switch_state_t;
    typedef struct io_switch_t
    {
        uint8_t id;                 // switch id

        io_t sw_sel;               // switch sel   (used when can_sel=1)

        //io_t sw_a;                 // switch a
        //io_t sw_b;                 // switch b (unused when not connected to io)
    } io_switch_t;

    #define IO_SWITCH_ARR_END_ID        (uint8_t)(-1)

    #define SWITCH_EN(_MUX_ID_)          ( 1 << ((_MUX_ID_) - 1))


    extern io_switch_t switch_config[];

    gpio_config_status_t switch_init(io_switch_t* switch_configs);
    gpio_config_status_t switch_set(io_switch_t* switch_configs, uint16_t value);
    uint32_t switch_get(io_switch_t* switch_configs);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_MUX_H_
