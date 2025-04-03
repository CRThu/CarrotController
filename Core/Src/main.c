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
    //MX_SPI1_Init();
    //MX_SPI3_Init();
    /* USER CODE BEGIN 2 */

        // initial cdelay module
    if (cdelay_init() == 0)      Error_Handler();

    // initial bsp perh
    bsp_gpio_init();
    bsp_switch_init(BSPMUX_DEFAULT);

    // initial dut ad7616 board
    ad7616_set_mode(&adc, AD7616_PAR_SW);
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

    ad7616_convst_generate(&adc);

    // wait busy
    delay_ns(60000);

    ad7616_reg_bits_write(&adc, 0x02, 5, 5, 1);     // SEQ
    ad7616_reg_bits_write(&adc, 0x02, 6, 6, 1);     // BURST

    ad7616_reg_write(&adc, 0x20, 0x11);
    ad7616_reg_write(&adc, 0x21, 0x00);
    ad7616_reg_write(&adc, 0x22, 0x11);
    ad7616_reg_write(&adc, 0x23, 0x11);
    ad7616_reg_write(&adc, 0x24, 0x11);
    ad7616_reg_write(&adc, 0x25, 0x22);
    ad7616_reg_write(&adc, 0x26, 0x11);
    ad7616_reg_write(&adc, 0x27, 0x33);

    ad7616_reg_write(&adc, 0x28, 0x33);
    ad7616_reg_write(&adc, 0x29, 0x00);
    ad7616_reg_write(&adc, 0x2A, 0x33);
    ad7616_reg_write(&adc, 0x2B, 0x11);
    ad7616_reg_write(&adc, 0x2C, 0x33);
    ad7616_reg_write(&adc, 0x2D, 0x22);
    ad7616_reg_write(&adc, 0x2E, 0x33);
    ad7616_reg_write(&adc, 0x2F, 0x33);

    ad7616_reg_write(&adc, 0x30, 0x55);
    ad7616_reg_write(&adc, 0x31, 0x00);
    ad7616_reg_write(&adc, 0x32, 0x55);
    ad7616_reg_write(&adc, 0x33, 0x11);
    ad7616_reg_write(&adc, 0x34, 0x55);
    ad7616_reg_write(&adc, 0x35, 0x22);
    ad7616_reg_write(&adc, 0x36, 0x55);
    ad7616_reg_write(&adc, 0x37, 0x33);

    ad7616_reg_write(&adc, 0x38, 0x77);
    ad7616_reg_write(&adc, 0x39, 0x00);
    ad7616_reg_write(&adc, 0x3A, 0x77);
    ad7616_reg_write(&adc, 0x3B, 0x11);
    ad7616_reg_write(&adc, 0x3C, 0x77);
    ad7616_reg_write(&adc, 0x3D, 0x22);
    ad7616_reg_write(&adc, 0x3E, 0x77);
    ad7616_reg_write(&adc, 0x3F, 0x33 | 0x1 << 8);

    volatile uint16_t ret = ad7616_reg_read(&adc, 0x3F);

    volatile double x[128];
    // dummy
    delay_us(100);
    ad7616_convst_generate(&adc);
    delay_us(100);

    // convstart 
    ad7616_convst_generate(&adc);
    delay_us(100);

    for (int j = 0; j < 16; j++)
    {
        // conv sxa,sxb
        ad7616_sample_callback(&adc);
        ad7616_sample_callback(&adc);

        delay_us(10);
    }

    ad7616_reg_write(&adc, 0x2F, 0x33 | 0x1 << 8);
    ad7616_reg_write(&adc, 0x3F, 0x33);

    delay_us(100);
    ad7616_convst_generate(&adc);
    delay_us(100);
    //ad7616_convst_generate(&adc);
    //delay_us(100);

    for (int j = 0; j < 64; j++)
    {
        // conv sxa,sxb
        ad7616_sample_callback(&adc);
        ad7616_sample_callback(&adc);

        delay_us(10);
    }

    for (int i = 0; i < 128; i++)
    {
        x[i] = (double)adc_data_buffer[i] * 10.0 / (double)(1 << 15);
    }

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
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
