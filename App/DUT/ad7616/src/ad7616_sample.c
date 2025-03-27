/****************************
 AD7616 SAMPLE
 CRTHu
 2025.03.27
 ****************************/

#include "ad7616_sample.h"

uint32_t adc_data_buffer[AD7616_CONV_BUFFER_LEN] = {0};
uint32_t adc_data_count = {0};

void ad7616_adc_convst_signal_start(uint8_t conv_mode, uint32_t freq)
{
}

void ad7616_adc_convst_signal_pulse(uint8_t conv_mode)
{
}

void ad7616_adc_convst_signal_stop(uint8_t conv_mode)
{
}

void ad7616_adc_sample_cont(uint32_t channel_mask, uint32_t count, uint32_t freq)
{
}

void ad7616_adc_sample_single(uint32_t channel_mask)
{
}
