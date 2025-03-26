#pragma once
#ifndef _CDELAY_H_
#define _CDELAY_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #include <stdint.h>
    #include "stm32h5xx_hal.h"

    #define CDELAY_VERSION          "1.0.0"

    #define CDELAY_SYSFREQ                  250000000
    #define CDELAY_NS2TICK(ns)              (uint64_t)( (uint64_t)ns * CDELAY_SYSFREQ / 1000000000 )
    #define CDELAY_NS_IMPL_THRESHOLD        (20)
    #define CDELAY_NOP_ELAPSED_CAL          (0.54)



    #define cdelay_nops             CDELAY_NOPS
    #define cdelay_nops_safe        CDELAY_NOPS_SAFE
    #define cdelay_ticks            CDELAY_TICKS

    #define cdelay_ns(n)       do {                             \
        if(__builtin_constant_p(n)) {                           \
            if(CDELAY_NS2TICK(n) >= CDELAY_NS_IMPL_THRESHOLD) { \
                CDELAY_TICKS(CDELAY_NS2TICK(n));                \
            }                                                   \
            else if(CDELAY_NS2TICK(n) >= 3){                                              \
                CDELAY_NOPS(CDELAY_NS2TICK(n) / CDELAY_NOP_ELAPSED_CAL);  \
            }                                                   \
            else {                                              \
                CDELAY_NOPS(CDELAY_NS2TICK(n) / CDELAY_NOP_ELAPSED_CAL);  \
            }                                                   \
        }                                                       \
        else {                                                  \
                CDELAY_TICKS(CDELAY_NS2TICK(n));                \
        }                                                       \
    } while(0)

    #define CDELAY_NOPS(n)  do {                                \
        _Pragma("unroll")                                       \
        for(uint32_t _i=0; _i < (n); ++_i) {                    \
            __NOP();                                            \
        }                                                       \
    } while(0)

    #define CDELAY_NOPS_SAFE(n)  do {                           \
        uint32_t primask = __get_PRIMASK();                     \
        __disable_irq();                                        \
        CDELAY_NOPS(n);                                         \
        __set_PRIMASK(primask);                                 \
    } while(0)

    #define CDELAY_TICKS(ticks)  do{                            \
        uint32_t __end = DWT->CYCCNT + (ticks);                 \
        while ((DWT->CYCCNT) < __end) {}                        \
    } while(0)

    void cdelay_init();

    void cdelay_us(uint32_t us);
    void cdelay_ms(uint32_t ms);

    #ifdef __cplusplus
}
#endif
#endif // _CDELAY_H_