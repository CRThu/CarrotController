/****************************
 AD7616 SAMPLE
 CRTHu
 2025.04.01
 ****************************/

#include "ad7616_sample.h"

uint16_t adc_data_buffer[AD7616_CONV_BUFFER_LEN] = { 0 };
uint32_t adc_data_count = 0;


__FORCEINLINE uint8_t ad7616_hw_set_seq(ad7616_t* adc, uint8_t seq)
{
    if (adc->mode & AD7616_MODE_HW_FLAG)
    {
        /* HW */
        BSP_IO_WRITE(&(adc->seqen), seq ? IO_STATE_HIGH : IO_STATE_LOW);

        return 0;
    }
    else
        return -1;
}

__FORCEINLINE uint8_t ad7616_hw_set_seq_chsel(ad7616_t* adc, uint8_t chseq)
{
    if (adc->mode & AD7616_MODE_HW_FLAG)
    {
        /* HW */
        /* AD7616 手册chsel错误 */
        uint8_t chsel2 = (chseq >> 2) & 0x01;
        uint8_t chsel1 = (chseq >> 1) & 0x01;
        uint8_t chsel0 = (chseq >> 0) & 0x01;

        BSP_IO_WRITE(&(adc->chsel2), chsel2 ? IO_STATE_HIGH : IO_STATE_LOW);
        BSP_IO_WRITE(&(adc->chsel1), chsel1 ? IO_STATE_HIGH : IO_STATE_LOW);
        BSP_IO_WRITE(&(adc->chsel0), chsel0 ? IO_STATE_HIGH : IO_STATE_LOW);

        return 0;
    }
    else
        return -1;
}

__FORCEINLINE void ad7616_set_channel(ad7616_t* adc, uint8_t adc_ch_a, uint8_t adc_ch_b)
{
    adc->adc_ch_a_en = (adc_ch_a != AD7616_CHANNEL_OFF);
    adc->adc_ch_b_en = (adc_ch_b != AD7616_CHANNEL_OFF);
    adc->adc_ch_a = (adc_ch_a != AD7616_CHANNEL_OFF) ? adc_ch_a : 0x00;
    adc->adc_ch_b = (adc_ch_b != AD7616_CHANNEL_OFF) ? adc_ch_b : 0x00;

    if (adc->mode == AD7616_SER_SW
        || adc->mode == AD7616_PAR_SW)
    {
        ad7616_reg_write(adc, AD7616_REG_CHANNEL, adc_ch_b << 4 | adc_ch_a << 0);

    }
    else
    {
        // TODO
    }
}

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

__FORCEINLINE void ad7616_sample_by_io(ad7616_t* adc, uint32_t count)
{
    adc_data_count = 0;

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

__FORCEINLINE void ad7616_sample_by_pwm(ad7616_t* adc, uint32_t count)
{
    if (count > sizeof(adc_data_buffer) / sizeof(uint16_t))
        Error_Handler();

    adc_data_count = 0;

    ad7616_convst_generate_by_pwm(adc);

    bsp_tim_set(adc->pwm1->tim, adc->convst_freq);
    bsp_pwm_set(adc->pwm1, 0.01);

    bsp_tim_start(adc->pwm1->tim, set_flag);
    bsp_pwm_start(adc->pwm1);

    // for first isr
    while (!flag);
    flag = 0;

    // ad7616 update
    while (!flag);
    flag = 0;

    for (uint32_t i = 0; i < count; i++)
    {
        // wait for convst
        while (!flag);
        flag = 0;

        delay_ns(200);
        ad7616_sample_read_adc(adc);
    }

    bsp_tim_stop(adc->pwm1->tim);
    bsp_pwm_stop(adc->pwm1);
}

__FORCEINLINE void ad7616_sample_read_adc(ad7616_t* adc)
{
    uint16_t adc_data_temp_a = 0;
    uint16_t adc_data_temp_b = 0;
    ad7616_data_read_two(adc, &adc_data_temp_a, &adc_data_temp_b);

    if (adc->adc_ch_a_en)
    {
        adc_data_buffer[adc_data_count] = adc_data_temp_a;
        adc_data_count += 1;
    }
    if (adc->adc_ch_b_en)
    {
        adc_data_buffer[adc_data_count] = adc_data_temp_b;
        adc_data_count += 1;
    }
}