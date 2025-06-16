/****************************
 * CARROT PROTOCOL
 * CARROT HU
 * 2024.09.05
 *****************************/
#pragma once

#ifndef _ASCII_PROTOCOL_H_
#define _ASCII_PROTOCOL_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "uart_comm.h"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#ifdef __cplusplus
extern "C"
{
    #endif
    #define ASCII_PROTOCOL_VERSION "1.0.2"

    #define DEBUG_MSG()         protocol_write_msg();


    // typedef int8_t(*protocol_parse_t)(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);
    // typedef void (*protocol_send_msg_t)(const char* format, ...);
    // typedef void (*protocol_send_data_t)(uint8_t channel, uint8_t* data, uint16_t len);
    typedef void (*comm_write_t)(void* comm, const uint8_t* txcmd, uint16_t size);

    typedef struct
    {
        void* comm;
        comm_write_t write;
    }comm_func_t;

    // typedef struct {
    //     uint8_t payload[256];
    // } frame_t;

    //void protocol_parse(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);
    void protocol_write_msg(comm_func_t* c, const char* format, ...);
    void protocol_write_data(comm_func_t* c, uint8_t channel, uint8_t* data, uint16_t len);


    #ifdef __cplusplus
}
#endif

#endif // _ASCII_PROTOCOL_H_