/****************************
 AD7616 SAMPLE
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_SAMPLE_H_
#define _AD7616_SAMPLE_H_

#include <stdint.h>
#include "ad7616_def.h"
#include "ad7616_iocfg.h"

extern uint32_t adc_data_buffer[AD7616_CONV_BUFFER_LEN];
extern uint32_t adc_data_count;

#endif // _AD7616_SAMPLE_H_
