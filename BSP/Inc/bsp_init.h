/****************************
 * BSP INITIAL
 * CRTHu
 * 2025.09.11
 *****************************/
#pragma once
#ifndef _BSP_INIT_H_
#define _BSP_INIT_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_INIT_VERSION "1.0.0"

    #include "bsp_def.h"
    #include "common.h"
    #ifdef USING_BSP_DRIVER
        #include "bsp_sw.h"
        #include "bsp_psram.h"
        #include "bsp_uart.h"
        #include "bsp_ft.h"
    #endif
    #ifdef USING_REMOTE_CONTROL
        #include "carrot_ascii_protocol.h"
        #include "dyncall.h"
        #include "cmdparse.h"
    #endif

    extern comm_t* default_comm;

    void bsp_init();

    #ifdef __cplusplus
}
#endif

#endif // _BSP_UART_H_
