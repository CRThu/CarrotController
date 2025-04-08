/****************************
 AD7616 SAMPLE
 CRTHu
 2025.04.01
 ****************************/

#ifndef _AD7616_SAMPLE_H_
#define _AD7616_SAMPLE_H_

#include <stdint.h>
#include "ad7616_def.h"
#include "ad7616_iocfg.h"
#include "ad7616_def.h"
#include "bsp_inc.h"

extern uint16_t adc_data_buffer[AD7616_CONV_BUFFER_LEN];
extern uint32_t adc_data_count;


void ad7616_set_convst_mode(ad7616_t* adc, ad7616_convst_mode mode);
void ad7616_set_convst_freq(ad7616_t* adc, uint32_t freq);
void ad7616_convst_generate(ad7616_t* adc);
void ad7616_sample_start(ad7616_t* adc, uint16_t channel_mask, uint32_t count);
void ad7616_sample_callback(ad7616_t* adc);

#endif // _AD7616_SAMPLE_H_
