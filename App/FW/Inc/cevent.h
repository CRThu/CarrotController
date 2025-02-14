/****************************
 * CEVENT
 * CARROT HU
 * 2025.01.22
 *****************************/
#pragma once
#ifndef _CEVENT_H_
#define _CEVENT_H_

#ifdef __cplusplus
extern "C"
{
#endif
#define CEVENT_VERSION "1.0.0"

#include <stdint.h>
#include <string.h>

/*
    USAGE:

    INITIAL:
    
 */

    typedef uint8_t cevent_error_t;
    typedef struct {
        cevent_error_t error;
    }cevent_t;




#ifdef __cplusplus
}
#endif

#endif // _UART_COMM_H_
