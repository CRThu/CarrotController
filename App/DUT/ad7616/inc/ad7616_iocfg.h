/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_IOCFG_H_
#define _AD7616_IOCFG_H_

#include <stdint.h>
#include "ad7616_def.h"

// #define SET_BIT(REG, BIT)     ((REG) |= (BIT))
// #define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
// #define READ_BIT(REG, BIT)    ((REG) & (BIT))
// #define CLEAR_REG(REG)        ((REG) = (0x0))
// #define WRITE_REG(REG, VAL)   ((REG) = (VAL))
// #define READ_REG(REG)         ((REG))
// #define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
// #define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#ifndef   __INLINE
#define __INLINE                               __inline
#endif
#ifndef   __FORCEINLINE
#define __FORCEINLINE                         __attribute__((always_inline)) __inline
#endif
#ifndef   __DBG_BREAKPOINT
#define __DBG_BREAKPOINT                      __NOP
#endif


#define __AD7616_IOCFG_INLINE                   __FORCEINLINE

#define BITSMASK(START, END)                    ((((1U) << ((END) - (START) + 1)) - 1) << (START))
#define WRITE_RS_REG(REG, DATA, MASK)           WRITE_REG((REG), ((DATA) & (MASK)) | ((~(DATA) & (MASK)) << 16U))

#define WRITE_DB_MASK(GPIOx, DATA, MASK)        WRITE_RS_REG((GPIOx)->BSRR, (DATA), (MASK))
#define WRITE_DB_TEST_MODE(GPIOx, DATA)         WRITE_DB_MASK((GPIOx), (DATA), AD7616_DB_MASK_TEST_MODE)
#define WRITE_DB(GPIOx, DATA)                   WRITE_DB_MASK((GPIOx), (DATA), AD7616_DB_MASK)
#define WRITE_IO(GPIOx, PINMASK, STATE)         WRITE_REG((GPIOx)->BSRR, ((STATE)? (PINMASK) : (PINMASK) << 16U))
#define READ_DB(GPIOx)                          (uint32_t)(READ_REG((GPIOx)->IDR))
#define READ_IO(GPIOx, PINMASK)                 ((READ_REG((GPIOx)->IDR) & (PINMASK)) != 0 ? 1 : 0)

#define BITS_GET(REG, START, END)               (((REG) & BITSMASK((START), (END))) >> (START))
#define BITS_SET(REG, START, END, DATA)         (((REG) & (~BITSMASK((START), (END))) | (((DATA) << (START)) & BITSMASK((START), (END)))))

#define DELAY_NOP(X)                            delay_nop(X)
#define DELAY_US(X)                             delay_us(X)

#define DELAY_S_DB_NWR(X)                       DELAY_NOP(8)

#endif // _AD7616_IOCFG_H_
