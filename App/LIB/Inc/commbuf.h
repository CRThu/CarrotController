/****************************
 * COMM BUF
 * CARROT HU
 * 2025.06.11
 *****************************/
#pragma once
#ifndef __COMMBUF_H__
#define __COMMBUF_H__

#ifdef __cplusplus
extern "C"
{
    #endif

    #define COMMBUF_VERSION             "1.0.0"

    #include <stdint.h>
    #include "stm32h5xx_hal.h"

    // 临界区保护宏（使用CMSIS指令）
    #define COMMBUF_ENTER_CRITICAL()    uint32_t primask = __get_PRIMASK(); __disable_irq()
    #define COMMBUF_EXIT_CRITICAL()     __set_PRIMASK(primask)

    #define COMMBUF_NO_ERR              0
    #define COMMBUF_ERR_NULL            -1
    #define COMMBUF_ERR_OUT_OF_RANGE    -2

    typedef uint32_t commbuf_size_t;
    typedef int8_t commbuf_error_t;

    typedef struct
    {
        uint8_t* buf;
        commbuf_size_t size;
        commbuf_size_t head;
        commbuf_size_t tail;
    } commbuf_t;

    commbuf_t* commbuf_create(commbuf_size_t size);
    void commbuf_free(commbuf_t* buf);
    commbuf_size_t commbuf_get_len(commbuf_t* buf);
    commbuf_size_t commbuf_get_space(commbuf_t* buf);
    void commbuf_flush(commbuf_t* buf);
    commbuf_size_t commbuf_read(commbuf_t* buf, uint8_t* dest, commbuf_size_t destsize);
    commbuf_size_t commbuf_write(commbuf_t* buf, uint8_t* src, commbuf_size_t srcsize);
    commbuf_error_t commbuf_peek(commbuf_t* buf, commbuf_size_t offset, uint8_t* val);


    #ifdef __cplusplus
}
#endif

#endif /* __COMMBUF_H__ */