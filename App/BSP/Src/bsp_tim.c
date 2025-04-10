/****************************
 * BSP TIM
 * CRTHu
 * 2025.04.01
 *****************************/
#include "bsp_inc.h"



 /* TIM5 init function */
 // void bsp_pwm_init(void)
 // {
 //     TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
 //     TIM_OC_InitTypeDef sConfigOC = { 0 };

 //     htim5.Instance = TIM5;
 //     htim5.Init.Prescaler = 1 - 1;
 //     htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
 //     htim5.Init.Period = 2499;
 //     htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
 //     htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

 //     /* TIM5 clock enable */
 //     __HAL_RCC_TIM5_CLK_ENABLE();

 //     /* TIM5 interrupt Init */
 //     HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
 //     HAL_NVIC_EnableIRQ(TIM5_IRQn);

 //     // HAL_TIM_RegisterCallback(&htim5, HAL_TIM_BASE_MSPINIT_CB_ID, bsp_pwm_init_msp_init);

 //     /* CALLBACK: HAL_TIM_BASE_MSPINIT_CB_ID inside */
 //     if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
 //     {
 //         Error_Handler();
 //     }
 //     sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
 //     if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
 //     {
 //         Error_Handler();
 //     }
 //     if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
 //     {
 //         Error_Handler();
 //     }
 //     sConfigOC.OCMode = TIM_OCMODE_PWM1;
 //     sConfigOC.Pulse = 2450;
 //     sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;//TIM_OCPOLARITY_HIGH;
 //     sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
 //     if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
 //     {
 //         Error_Handler();
 //     }

 //     GPIO_InitTypeDef GPIO_InitStruct = { 0 };
 //     if ((&htim5)->Instance == TIM5)
 //     {
 //         __HAL_RCC_GPIOA_CLK_ENABLE();
 //         /**TIM5 GPIO Configuration
 //         PA1     ------> TIM5_CH2
 //         */
 //         GPIO_InitStruct.Pin = GPIO_PIN_1;
 //         GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
 //         GPIO_InitStruct.Pull = GPIO_NOPULL;
 //         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
 //         GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
 //         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

 //     }
 // }

void bsp_tim_set(tim_t* tim, uint32_t freq)
{
    uint32_t arr = (double)ST_TIM_MAIN_CLOCK / (double)freq - 1;
    // arr range check
    ST_TIM_SET_FREQ(tim, arr);
}

void bsp_pwm_set(tim_t* pwm, bsp_tim_ch_t ch, double duty)
{
    uint32_t ccr = (double)duty * (double)ST_TIM_GET_FREQ(pwm);
    ST_TIM_SET_DUTY(pwm, ch, ccr);
}

void bsp_tim_start(tim_t* tim, tim_callback_t callback)
{
    ST_TIM_REGISTER_CALLBACK(tim, callback);
    ST_TIM_START(tim);
}

void bsp_tim_stop(tim_t* tim)
{
    ST_TIM_STOP(tim);
}

void bsp_pwm_start(tim_t* pwm, bsp_tim_ch_t ch)
{
    ST_PWM_START(pwm, ch);
}

void bsp_pwm_stop(tim_t* pwm, bsp_tim_ch_t ch)
{
    ST_PWM_STOP(pwm, ch);
}