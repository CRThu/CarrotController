/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN(PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT(PH1)   ------> RCC_OSC_OUT
     PA13(JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14(JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MUX_SEL09_Pin|MUX_SEL12_Pin|MUX_SEL11_Pin|MUX_SEL07_Pin
                          |MUX_SEL04_Pin|MUX_SEL03_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LEDA_Pin|LEDB_Pin|FT_RDN_Pin|FT_WRN_Pin
                          |FT_SIWUA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MUX_SEL08_Pin|MUX_SEL02_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MUX_SEL05_Pin|MUX_SEL06_Pin|MUX_SEL01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MUX_SEL10_GPIO_Port, MUX_SEL10_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MUX_SEL09_Pin MUX_SEL12_Pin MUX_SEL11_Pin MUX_SEL07_Pin
                           MUX_SEL04_Pin MUX_SEL03_Pin */
  GPIO_InitStruct.Pin = MUX_SEL09_Pin|MUX_SEL12_Pin|MUX_SEL11_Pin|MUX_SEL07_Pin
                          |MUX_SEL04_Pin|MUX_SEL03_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : FT_D0_Pin FT_D1_Pin FT_D2_Pin FT_D3_Pin
                           FT_D4_Pin FT_D5_Pin FT_D6_Pin FT_D7_Pin
                           FT_RXFN_Pin FT_TXEN_Pin */
  GPIO_InitStruct.Pin = FT_D0_Pin|FT_D1_Pin|FT_D2_Pin|FT_D3_Pin
                          |FT_D4_Pin|FT_D5_Pin|FT_D6_Pin|FT_D7_Pin
                          |FT_RXFN_Pin|FT_TXEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDA_Pin LEDB_Pin FT_RDN_Pin FT_WRN_Pin
                           FT_SIWUA_Pin */
  GPIO_InitStruct.Pin = LEDA_Pin|LEDB_Pin|FT_RDN_Pin|FT_WRN_Pin
                          |FT_SIWUA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : KEYA_Pin */
  GPIO_InitStruct.Pin = KEYA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEYA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_SEL08_Pin MUX_SEL02_Pin */
  GPIO_InitStruct.Pin = MUX_SEL08_Pin|MUX_SEL02_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_SEL05_Pin MUX_SEL06_Pin MUX_SEL01_Pin */
  GPIO_InitStruct.Pin = MUX_SEL05_Pin|MUX_SEL06_Pin|MUX_SEL01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MUX_SEL10_Pin */
  GPIO_InitStruct.Pin = MUX_SEL10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MUX_SEL10_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
