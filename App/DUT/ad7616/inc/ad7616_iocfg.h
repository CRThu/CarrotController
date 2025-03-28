/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_IOCFG_H_
#define _AD7616_IOCFG_H_

#include <stdint.h>
#include "dut_ad7616.h"
#include "ad7616_def.h"
#include "bsp_inc.h"


typedef struct ad7616_t
{
    dut_interface_t* dut_interface;  // hardware pin configs
} ad7616_t;


void ad7616_reset(ad7616_t* adc);

#endif // _AD7616_IOCFG_H_
