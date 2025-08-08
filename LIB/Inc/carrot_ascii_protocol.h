/****************************
 * CARROT PROTOCOL
 * CARROT HU
 * 2025.08.08
 *****************************/
#pragma once

#ifndef _CARROT_ASCII_PROTOCOL_H_
#define _CARROT_ASCII_PROTOCOL_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifdef __cplusplus
extern "C"
{
    #endif
    #define CARROT_ASCII_PROTOCOL_VERSION "1.1.0"

    #include <stdint.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include "comm.h"
    
    #include "carrot_binary_protocol.h"

    // typedef int8_t(*protocol_parse_t)(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);

    typedef struct {
        comm_t* comm;
        carrot_binary_protocol_config_t data_protocol;
    } carrot_ascii_protocol_config_t;

    //void protocol_parse(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);

    
    extern carrot_ascii_protocol_config_t carrot_ascii_protocol_config;


    void write_msg(const char* format, ...);
    void write_data(uint8_t* data, uint16_t len);


    #ifdef __cplusplus
}
#endif

#endif // _CARROT_ASCII_PROTOCOL_H_