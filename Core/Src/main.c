/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "cordic.h"
#include "gpdma.h"
#include "i2c.h"
#include "icache.h"
#include "memorymap.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "uart_comm.h"

#include "ad7616_iocfg.h"
#include "ad7616_sample.h"

#include "bsp_inc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/*
uart_comm_t* comm_pc = NULL;

volatile uint8_t flag = 0;
volatile double cnt = 0;

uint8_t recv_bytes[256];
uint16_t recv_len = 0;
*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
void test(TIM_HandleTypeDef* htim)
{
    recv_len = uart_comm_read(comm_pc, recv_bytes, sizeof(recv_bytes));
    if (recv_len != 0)
    {
        uart_comm_write(comm_pc, recv_bytes, recv_len);
    }
}
void set_flag(TIM_HandleTypeDef* htim)
{
    flag = 1;
}
*/
ad7616_t adc;

void read_data()
{
    ad7616_sample_callback(&adc);
}

void bsp_clock_init()
{
    RCC_PLL2InitTypeDef pll2;
    if (~RCC->CR & RCC_CR_PLL2ON)
    {
        pll2.PLL2Source = RCC_PLL2_SOURCE_HSE;
        pll2.PLL2M = 5;
        pll2.PLL2N = 80;
        pll2.PLL2P = 2;
        pll2.PLL2Q = 2;
        pll2.PLL2R = 2;
        pll2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
        pll2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
        pll2.PLL2FRACN = 0;
        pll2.PLL2ClockOut = RCC_PLL2_DIVP;
        if (HAL_RCCEx_EnablePLL2(&pll2) != HAL_OK)
        {
            Error_Handler();
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* Configure the peripherals common clocks */
    //PeriphCommonClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_GPDMA1_Init();
    MX_UART4_Init();
    MX_I2C1_Init();
    MX_CORDIC_Init();
    MX_ICACHE_Init();
    MX_TIM5_Init();
    MX_SPI1_Init();
    MX_SPI3_Init();
    /* USER CODE BEGIN 2 */

        // initial cdelay module
    if (cdelay_init() == 0)      Error_Handler();

    // initial bsp perh
    bsp_clock_init();
    bsp_gpio_init();
    bsp_spi_init_all(BSP_SPI_MODE_OFF);
    bsp_switch_init(BSPMUX_DEFAULT);

    // initial dut ad7616 board
    /* PAR SW*/
    ad7616_set_mode(&adc, AD7616_PAR_SW);
    /* SER SW*/
    //ad7616_set_mode(&adc, AD7616_SER_SW);
    
    ad7616_set_io(&adc, &ad7616_profiles[0]);
    ad7616_full_reset(&adc);

    //bsp_pwm_init();
    //bsp_pwm_callback(read_data);
    //bsp_pwm_start();

    //ad7616_sample_start(&adc, 0x00, 16);

    /*
    comm_pc = uart_comm_create(&huart4, 2048);
    uart_comm_start(comm_pc);

    HAL_TIM_RegisterCallback(&htim6, HAL_TIM_PERIOD_ELAPSED_CB_ID, test);
    HAL_TIM_Base_Start_IT(&htim6);
    */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        ad7616_reg_write(&adc, 0x2F, 0x11);
        ad7616_reg_write(&adc, 0x3F, 0x122);

        volatile uint16_t reg2f = ad7616_reg_read(&adc, 0x2F);
        volatile uint16_t reg3f = ad7616_reg_read(&adc, 0x3F);

        delay_us(1000);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
    */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 80;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1_VCIRANGE_2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
        | RCC_CLOCKTYPE_PCLK3;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure the programming delay
    */
    __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_2);
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

    /** Initializes the peripherals clock
    */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI1 | RCC_PERIPHCLK_SPI3;
    PeriphClkInitStruct.PLL2.PLL2Source = RCC_PLL2_SOURCE_HSE;
    PeriphClkInitStruct.PLL2.PLL2M = 5;
    PeriphClkInitStruct.PLL2.PLL2N = 80;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2_VCIRANGE_2;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2_VCORANGE_WIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.PLL2.PLL2ClockOut = RCC_PLL2_DIVP;
    PeriphClkInitStruct.Spi1ClockSelection = RCC_SPI1CLKSOURCE_PLL2P;
    PeriphClkInitStruct.Spi3ClockSelection = RCC_SPI3CLKSOURCE_PLL2P;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
                          /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
                          /* User can add his own implementation to report the file name and line number,
                             ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
                             /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
