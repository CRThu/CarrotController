#pragma once
#ifndef _CDELAY_H_
#define _CDELAY_H_

#ifdef __cplusplus
extern "C"
{
    #endif

    #include <stdint.h>
    
    #define CDELAY_VERSION                  "2.0.0"             // Library version

    ////////////////////////////////////////////////////////////////////////////
    // Configuration Parameters
    ////////////////////////////////////////////////////////////////////////////
    #define CDELAY_SYSFREQ                  250000000           // System clock: 250 MHz
    #define CDELAY_NS_IMPL_THRESHOLD        (20)                // Threshold (ticks) for switching NOP/TICK impl
    #define CDELAY_NOP_CAL_THRESHOLD        (5)                 // Threshold (ticks) for NOP calibration
    #define CDELAY_NOP_CAL                  (0.54)              // NOP calibration factor


    ////////////////////////////////////////////////////////////////////////////
    // Performance Report (STM32H563 @ 250MHz, ICACHE ON, CAL=[20, 5, 0.54])
    ////////////////////////////////////////////////////////////////////////////
    /*
    ### Implementation Strategy
    - **NOP Impl**: Used when `ticks < CDELAY_NS_IMPL_THRESHOLD`
    - **TICK Impl**: Used when `ticks >= CDELAY_NS_IMPL_THRESHOLD`
    - **NOP Calibration**: Applied when `ticks < CDELAY_NOP_CAL_THRESHOLD`

    ### Latency Benchmarks
    | Function                      | Input       | Measured Time | Conditions                     |
    |-------------------------------|-------------|---------------|--------------------------------|
    | **GPIO Toggle**               | L->H/H->L   | 4 ns          | Bare metal pin toggle          |
    | **cdelay_nops (const)**       | 1 NOP       | 4 ns          | Direct NOP execution           |
    |                               | 10 NOPs     | 28 ns         |                                |
    |                               | 100 NOPs    | 208 ns        |                                |
    | **cdelay_nops_safe (const)**  | 1 NOP       | 20 ns         | IRQ-disabled NOP execution     |
    |                               | 10 NOPs     | 40 ns         |                                |
    |                               | 100 NOPs    | 220 ns        |                                |
    | **cdelay_nops (var)**         | 1 NOP       | 36 ns         | Direct NOP execution           |
    |                               | 10 NOPs     | 70 ns         |                                |
    |                               | 100 NOPs    | 520 ns        |                                |
    | **cdelay_ns (const)**         | 0 ns        | 4 ns          | NOP impl (no calibration)      |
    |                               | 4 ns        | 4 ns          |                                |
    |                               | 12 ns       | 12 ns         |                                |
    |                               | 16 ns       | 16 ns         |                                |
    |                               | 20 ns       | 28 ns         | NOP impl + calibration         |
    |                               | 50 ns       | 52 ns         |                                |
    |                               | 78 ns       | 80 ns         |                                |
    |                               | 80 ns       | 128 ns        | TICK impl                      |
    |                               | 1000 ns     | 1048 ns       |                                |
    | **cdelay_ns (var)**           | 100 ns      | 1252 ns       | Always TICK impl               |
    |                               | 1000 ns     | 1868 ns       |                                |
    | **cdelay_us (const)**         | 0 μs        | 24 ns         | TICK impl                      |
    |                               | 1 μs        | 1.048 μs      |                                |
    |                               | 10 μs       | 10.05 μs      |                                |
    |                               | 1 s         | 1.000 s       |                                |
    | **cdelay_us (var)**           | 0 μs        | 276 ns        | TICK impl                      |
    |                               | 1 μs        | 1.760 μs      |                                |
    |                               | 1 s         | 1.000 s       |                                |
    | **cdelay_ms (const)**         | 0 ms        | 24 ns         | TICK impl                      |
    |                               | 1 ms        | 1.000 ms      |                                |
    |                               | 10 ms       | 10.00 ms      |                                |
    |                               | 17 s        | 17.00 s       |                                |
    |                               | 30 s        | OVERFLOW      | Tick counter wrap-around       |
    | **cdelay_ms (var)**           | 0 ms        | 280 ns        | TICK impl                      |
    |                               | 1 ms        | 1.001 ms      |                                |
    |                               | 10 ms       | 10.00 ms      |                                |

    ### Critical Notes
    - **TICK Impl** uses DWT cycle counter (`CDELAY_TICKS`).
    - **NOP Calibration**: Reduces error for mid-range delays (5-20 ticks).
    - Variable inputs always use TICK impl for runtime safety.
    */

    #define CDELAY_NS2TICK(ns)              (uint64_t)( (uint64_t)ns * CDELAY_SYSFREQ / 1000000000 )
    #define CDELAY_US2TICK(us)              (uint64_t)( (uint64_t)us * CDELAY_SYSFREQ / 1000000 )
    #define CDELAY_MS2TICK(ms)              (uint64_t)( (uint64_t)ms * CDELAY_SYSFREQ / 1000 )

    #define cdelay_nops                     CDELAY_NOPS
    #define cdelay_nops_safe                CDELAY_NOPS_SAFE
    #define cdelay_ticks                    CDELAY_TICKS

    #define cdelay_init()                   CDELAY_INIT()
    #define cdelay_ns(ns)                   CDELAY_NS(ns)
    #define cdelay_us(us)                   CDELAY_TICKS(CDELAY_US2TICK(us))
    #define cdelay_ms(ms)                   CDELAY_TICKS(CDELAY_MS2TICK(ms))

    #define CDELAY_INIT() ({                                    \
        if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))   \
        {                                                       \
            CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;     \
        }                                                       \
        __DSB();                                                \
                                                                \
        DWT->CYCCNT = 0;                                        \
        __DSB();                                                \
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;                    \
        __DSB();                                                \
                                                                \
        (DWT->CYCCNT) ? 1 : 0;                                  \
    })

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
        uint32_t __start = DWT->CYCCNT;                         \
        while ((uint32_t)(DWT->CYCCNT - __start) < ticks);      \
    } while(0)

    #define CDELAY_NS(n)       do {                                 \
        if(__builtin_constant_p(n)) {                               \
            if(CDELAY_NS2TICK(n) >= CDELAY_NS_IMPL_THRESHOLD) {     \
                CDELAY_TICKS(CDELAY_NS2TICK(n));                    \
            }                                                       \
            else if(CDELAY_NS2TICK(n) < CDELAY_NOP_CAL_THRESHOLD) { \
                CDELAY_NOPS(CDELAY_NS2TICK(n));                     \
            }                                                       \
            else {                                                  \
                CDELAY_NOPS(CDELAY_NS2TICK(n) / CDELAY_NOP_CAL);    \
            }                                                       \
        }                                                           \
        else {                                                      \
                CDELAY_TICKS(CDELAY_NS2TICK(n));                    \
        }                                                           \
    } while(0)

    #define CDELAY_TEST(f, n, io_port, io_pin)   do {               \
        f(n);                                                       \
        f(n);                                                       \
        (io_port)->BSRR = (io_pin);                                 \
        f(n);                                                       \
        (io_port)->BRR = (io_pin);                                  \
        f(n);                                                       \
        (io_port)->BSRR = (io_pin);                                 \
        f(n);                                                       \
        (io_port)->BRR = (io_pin);                                  \
        f(n);                                                       \
        (io_port)->BSRR = (io_pin);                                 \
        f(n);                                                       \
        (io_port)->BRR = (io_pin);                                  \
        f(n);                                                       \
        (io_port)->BSRR = (io_pin);                                 \
        f(n);                                                       \
        f(n);                                                       \
    } while(0)

    #ifdef __cplusplus
}
#endif
#endif // _CDELAY_H_