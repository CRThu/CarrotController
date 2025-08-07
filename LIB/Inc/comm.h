/****************************
 * COMM
 * CRTHu
 * 2025.08.07
 *****************************/
#pragma once
#ifndef _COMM_H_
#define _COMM_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #define COMM_VERSION "1.0.0"

    #include <stdint.h>

    typedef void *comm_handle;
    typedef void (*comm_init)(comm_handle handle);
    typedef uint16_t (*comm_read)(comm_handle handle, uint8_t* buffer, uint16_t size);
    typedef void (*comm_write)(comm_handle handle, uint8_t* buffer, uint16_t size);
    typedef struct
    {
        const char* id;
        comm_handle handle;
        comm_init init;
        comm_read read;
        comm_write write;
    } comm_t;

    #ifdef __cplusplus
}
#endif

#endif // _COMM_H_
