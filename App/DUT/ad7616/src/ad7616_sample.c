/****************************
 AD7616 SAMPLE
 CRTHu
 2025.04.01
 ****************************/

#include "ad7616_sample.h"

uint16_t adc_data_buffer[AD7616_CONV_BUFFER_LEN] = { 0 };
uint32_t adc_data_count = 0;

__FORCEINLINE void ad7616_convst_generate_by_io(ad7616_t* adc)
{
    ad7616_set_io_convst(adc, AD7616_CONVST_IO);
    BSP_IO_WRITE(&(adc->convst), IO_STATE_HIGH);
    delay_ns(AD7616_T_CONV_HIGH);
    BSP_IO_WRITE(&(adc->convst), IO_STATE_LOW);
}

__FORCEINLINE void ad7616_convst_generate_by_pwm(ad7616_t* adc)
{
    ad7616_set_io_convst(adc, AD7616_CONVST_PWM);
}

__FORCEINLINE void ad7616_sample_by_io(ad7616_t* adc, uint16_t channel_mask, uint32_t count)
{
    adc_data_count = 0;

    // TODO: channel_mask
    for (uint32_t i = 0; i < count; i++)
    {
        ad7616_convst_generate_by_io(adc);

        delay_ns(600);
        ad7616_sample_read_adc(adc);

        delay_us(10);
    }
}

volatile uint8_t flag = 0;
void set_flag(TIM_HandleTypeDef* htim)
{
    flag = 1;
}

__FORCEINLINE void ad7616_sample_by_pwm(ad7616_t* adc, uint16_t channel_mask, uint32_t count)
{
    ad7616_convst_generate_by_pwm(adc);

    // TODO重构
    bsp_tim_set(&htim5, 100000);
    bsp_pwm_set(&htim5, TIM_CHANNEL_2, 0.01);

    bsp_tim_start(&htim5, set_flag);
    bsp_pwm_start(&htim5, TIM_CHANNEL_2);

    while (!flag);
    flag = 0;
    while (!flag);
    flag = 0;
    while (!flag);
    flag = 0;

    adc_data_count = 0;

    // TODO: channel_mask
    for (uint32_t i = 0; i < count; i++)
    {
        // wait for convst
        while (!flag);
        flag = 0;

        ad7616_sample_read_adc(adc);
    }

    bsp_tim_stop(&htim5);
    bsp_pwm_stop(&htim5, TIM_CHANNEL_2);
}

__FORCEINLINE void ad7616_sample_read_adc(ad7616_t* adc)
{
    ad7616_data_read_two(adc, &adc_data_buffer[adc_data_count], &adc_data_buffer[adc_data_count + 1]);
    adc_data_count += 2;
}