/****************************
 * BSP TIM
 * CRTHu
 * 2025.04.01
 *****************************/
#pragma once
#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define BSP_TIM_VERSION "1.0.0"


    #include "bsp_inc.h"



    #include "tim.h"

    // STM32 IMPL
    #ifdef USE_STM32H5_HAL_IMPL

    #define ST_TIM_MAIN_CLOCK                                   250000000

    typedef TIM_HandleTypeDef tim_t;
    typedef uint32_t bsp_tim_ch_t;

    typedef void (*tim_callback_t)(tim_t* htim);

    #define ST_TIM_GET_FREQ                                     __HAL_TIM_GET_AUTORELOAD
    #define ST_TIM_SET_FREQ                                     __HAL_TIM_SET_AUTORELOAD
    #define ST_TIM_SET_DUTY                                     __HAL_TIM_SET_COMPARE



    #define BSP_TIM_REGISTER_CALLBACK(__INSTANCE__, __CALLBACK__)   HAL_TIM_RegisterCallback((__INSTANCE__), HAL_TIM_PERIOD_ELAPSED_CB_ID, (__CALLBACK__))
    #define ST_TIM_START                                        HAL_TIM_Base_Start_IT
    #define ST_TIM_STOP                                         HAL_TIM_Base_Stop_IT
    #define ST_PWM_START                                        HAL_TIM_PWM_Start
    #define ST_PWM_STOP                                         HAL_TIM_PWM_Stop
    #endif

    void bsp_tim_set(tim_t* tim, uint32_t freq);
    void bsp_pwm_set(tim_t* pwm, bsp_tim_ch_t ch, double duty);

    void bsp_tim_start(tim_t* tim);
    void bsp_tim_stop(tim_t* tim);

    //void bsp_pwm_init();
    void bsp_pwm_start(tim_t* pwm, bsp_tim_ch_t ch);
    void bsp_pwm_stop(tim_t* pwm, bsp_tim_ch_t ch);
    //void bsp_pwm_callback(BaseCallback pCallback);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_TIM_H_
