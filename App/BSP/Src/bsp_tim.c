/****************************
 * BSP TIM
 * CRTHu
 * 2025.04.01
 *****************************/
#include "bsp_inc.h"

//typedef void (*BaseCallback)();
//BaseCallback cb;

//   HAL_TIM_RegisterCallback(&htim6, HAL_TIM_PERIOD_ELAPSED_CB_ID, test);
//   HAL_TIM_Base_Start_IT(&htim6);


// HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, set_flag);
// HAL_TIM_Base_Start_IT(&htim5);
// HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

// void bsp_pwm_init_msp_init(TIM_HandleTypeDef* tim_baseHandle)
// {
// }


/* TIM5 init function */
void bsp_pwm_init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_OC_InitTypeDef sConfigOC = { 0 };

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 1 - 1;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 2499;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    /* TIM5 interrupt Init */
    HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);

    // HAL_TIM_RegisterCallback(&htim5, HAL_TIM_BASE_MSPINIT_CB_ID, bsp_pwm_init_msp_init);

    /* CALLBACK: HAL_TIM_BASE_MSPINIT_CB_ID inside */
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 2450;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;//TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    if ((&htim5)->Instance == TIM5)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM5 GPIO Configuration
        PA1     ------> TIM5_CH2
        */
        GPIO_InitStruct.Pin = GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    }
}

//void bsp_pwm_callback_func(TIM_HandleTypeDef* tim_baseHandle)
//{
//    if (tim_baseHandle->Instance == TIM5)
//    {
//        cb();
//    }
//}

void bsp_pwm_start()
{
//    HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, bsp_pwm_callback_func);
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
}

void bsp_pwm_stop()
{
    //HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, set_flag);
    HAL_TIM_Base_Stop_IT(&htim5);
    HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_2);
}


// void bsp_pwm_callback(BaseCallback _cb)
// {
//     cb = _cb;
//     HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, bsp_pwm_callback_func);
// }