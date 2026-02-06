/****************************
 * CARROT PROTOCOL
 * CARROT HU
 * 2026.02.06
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
    #define CARROT_ASCII_PROTOCOL_VERSION "1.2.0"

    #include <stdint.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include "comm.h"
    
    #include "carrot_binary_protocol.h"

    // protocol test
      /*
      uint16_t test_data[300];
      for (int i = 0;i < 300;i++)
          test_data[i] = i + 1;

      carrot_ascii_protocol_config.data_protocol.data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_NOT_USED;
      carrot_ascii_protocol_config.data_protocol.data_channel = 0xAA;
      write_data((uint8_t*)test_data, sizeof(uint16_t) * 300);

      carrot_ascii_protocol_config.data_protocol.data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED;
      carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_4CH;
      write_data((uint8_t*)test_data, sizeof(uint16_t) * 300);
      */

    // typedef int8_t(*protocol_parse_t)(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);

    typedef struct {
        comm_t* comm;
        //carrot_binary_protocol_config_t data_protocol;
    } carrot_ascii_protocol_config_t;

    //void protocol_parse(uint8_t* buf, uint16_t len, uint16_t* comsumed, frame_t* p);

    
    extern carrot_ascii_protocol_config_t carrot_ascii_protocol_config;


    void write_msg(const char* format, ...);
    void write_data(const char* path, const char* format, ...);
    void reply_reg(uint32_t addr, uint32_t val);
    void reply_bits(uint32_t addr, uint8_t start, uint8_t end, uint32_t val);


    #ifdef __cplusplus
}
#endif

#endif // _CARROT_ASCII_PROTOCOL_H_