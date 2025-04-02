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
    typedef TIM_HandleTypeDef tim_t;
    typedef void (*tim_callback_t)(tim_t* htim);

    #define TIM_REGISTER_CALLBACK(__INSTANCE__, __CALLBACK__) HAL_TIM_RegisterCallback((__INSTANCE__), HAL_TIM_PERIOD_ELAPSED_CB_ID, (__CALLBACK__))

    #endif

    void bsp_pwm_init();
    void bsp_pwm_start();
    void bsp_pwm_stop();
    void bsp_pwm_callback(pTIM_CallbackTypeDef pCallback);

    #ifdef __cplusplus
}
#endif

#endif // _BSP_TIM_H_
