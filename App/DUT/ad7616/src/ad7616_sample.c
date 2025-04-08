/****************************
 AD7616 SAMPLE
 CRTHu
 2025.04.01
 ****************************/

#include "ad7616_sample.h"

uint16_t adc_data_buffer[AD7616_CONV_BUFFER_LEN] = { 0 };
uint32_t adc_data_count = 0;

__FORCEINLINE void ad7616_set_convst_mode(ad7616_t* adc, ad7616_convst_mode mode)
{
    adc->convst_mode = mode;
}

__FORCEINLINE void ad7616_set_convst_freq(ad7616_t* adc, uint32_t freq)
{
    adc->convst_freq = freq;
}

__FORCEINLINE void ad7616_convst_generate(ad7616_t* adc)
{
    BSP_IO_WRITE(&(adc->convst), IO_STATE_HIGH);
    delay_ns(AD7616_T_CONV_HIGH);
    BSP_IO_WRITE(&(adc->convst), IO_STATE_LOW);
}

__FORCEINLINE void ad7616_sample_start(ad7616_t* adc, uint16_t channel_mask, uint32_t count)
{
    // TODO: channel_mask
    for (uint32_t i = 0; i < count; i++)
    {
        ad7616_convst_generate(adc);

        delay_ns(600);
        ad7616_sample_callback(adc);

        delay_us(10);
    }
}

__FORCEINLINE void ad7616_sample_callback(ad7616_t* adc)
{
    ad7616_data_read_two(adc, &adc_data_buffer[adc_data_count], &adc_data_buffer[adc_data_count + 1]);
    adc_data_count += 2;
}