/****************************
 AD7616 DEF
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_DEF_H_
#define _AD7616_DEF_H_

#include <stdint.h>
#include "bsp_inc.h"

#define AD7616_CONV_BUFFER_LEN          65536

#define AD7616_PAR_WR                   1
#define AD7616_PAR_RD                   0

typedef enum ad7616_mode{
    AD7616_SER_SW,
    AD7616_PAR_SW,
    AD7616_SER_HW,
    AD7616_PAR_HW
} ad7616_mode;

/* T (ns) */
#define T_MIN(t1, t2)                   (((t1) < (t2)) ? t1 : t2 )
#define T_MAX(t1, t2)                   (((t1) > (t2)) ? t1 : t2 )
#define T_ADD(t1, t2)                   ((t1) + (t2))
#define T_SUB(t1, t2)                   (((int)(t1) - (int)(t2)) >= 0 ? ((int)(t1) - (int)(t2)) : 0 )

#define AD7616_DELAY(t)                 delay_ns(T_ADD(T_MAX(t, AD7616_DEBUG_DELAY), AD7616_RESERVED_DELAY))

#define AD7616_DEBUG_DELAY              0
#define AD7616_RESERVED_DELAY           0

#define AD7616_PAR_T_RDN_SETUP          10
#define AD7616_PAR_T_RDN_HOLD           10
#define AD7616_PAR_T_RDN_HIGH           10
#define AD7616_PAR_T_RDN_LOW            30
#define AD7616_PAR_T_DOUT_SETUP         30
#define AD7616_PAR_T_DOUT_3STATE        11
#define AD7616_PAR_T_WRN_SETUP          10
#define AD7616_PAR_T_WRN_HOLD           10
#define AD7616_PAR_T_WRN_HIGH           20
#define AD7616_PAR_T_WRN_LOW            30
#define AD7616_PAR_T_DIN_SETUP          30

#endif // _AD7616_DEF_H_
