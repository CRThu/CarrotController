/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MUX_SEL09_Pin GPIO_PIN_13
#define MUX_SEL09_GPIO_Port GPIOC
#define MUX_SEL12_Pin GPIO_PIN_14
#define MUX_SEL12_GPIO_Port GPIOC
#define MUX_SEL11_Pin GPIO_PIN_15
#define MUX_SEL11_GPIO_Port GPIOC
#define FT_D0_Pin GPIO_PIN_0
#define FT_D0_GPIO_Port GPIOF
#define FT_D1_Pin GPIO_PIN_1
#define FT_D1_GPIO_Port GPIOF
#define FT_D2_Pin GPIO_PIN_2
#define FT_D2_GPIO_Port GPIOF
#define FT_D3_Pin GPIO_PIN_3
#define FT_D3_GPIO_Port GPIOF
#define FT_D4_Pin GPIO_PIN_4
#define FT_D4_GPIO_Port GPIOF
#define FT_D5_Pin GPIO_PIN_5
#define FT_D5_GPIO_Port GPIOF
#define FT_D6_Pin GPIO_PIN_6
#define FT_D6_GPIO_Port GPIOF
#define FT_D7_Pin GPIO_PIN_7
#define FT_D7_GPIO_Port GPIOF
#define LEDA_Pin GPIO_PIN_8
#define LEDA_GPIO_Port GPIOF
#define LEDB_Pin GPIO_PIN_9
#define LEDB_GPIO_Port GPIOF
#define KEYA_Pin GPIO_PIN_10
#define KEYA_GPIO_Port GPIOF
#define MUX_SEL08_Pin GPIO_PIN_5
#define MUX_SEL08_GPIO_Port GPIOA
#define MUX_SEL07_Pin GPIO_PIN_5
#define MUX_SEL07_GPIO_Port GPIOC
#define FT_RXFN_Pin GPIO_PIN_11
#define FT_RXFN_GPIO_Port GPIOF
#define FT_TXEN_Pin GPIO_PIN_12
#define FT_TXEN_GPIO_Port GPIOF
#define FT_RDN_Pin GPIO_PIN_13
#define FT_RDN_GPIO_Port GPIOF
#define FT_WRN_Pin GPIO_PIN_14
#define FT_WRN_GPIO_Port GPIOF
#define FT_SIWUA_Pin GPIO_PIN_15
#define FT_SIWUA_GPIO_Port GPIOF
#define MUX_SEL05_Pin GPIO_PIN_13
#define MUX_SEL05_GPIO_Port GPIOB
#define MUX_SEL06_Pin GPIO_PIN_14
#define MUX_SEL06_GPIO_Port GPIOB
#define MUX_SEL01_Pin GPIO_PIN_15
#define MUX_SEL01_GPIO_Port GPIOB
#define MUX_SEL04_Pin GPIO_PIN_8
#define MUX_SEL04_GPIO_Port GPIOC
#define MUX_SEL03_Pin GPIO_PIN_9
#define MUX_SEL03_GPIO_Port GPIOC
#define MUX_SEL02_Pin GPIO_PIN_8
#define MUX_SEL02_GPIO_Port GPIOA
#define MUX_SEL10_Pin GPIO_PIN_0
#define MUX_SEL10_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
