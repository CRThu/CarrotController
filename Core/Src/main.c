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

#include "dut_inc.h"

#include "arm_math.h"
#include "cdelay.h"
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
  MX_TIM6_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_CORDIC_Init();
  MX_TIM5_Init();
  MX_ICACHE_Init();
  /* USER CODE BEGIN 2 */
    cdelay_init();

    dut_ad7616_init();
    io_t* io_rstn = dut_get_io(&ad7616_profiles[0], "nRESET");
    gpio_write(io_rstn, IO_STATE_LOW);
    HAL_Delay(10);
    gpio_write(io_rstn, IO_STATE_HIGH);
    HAL_Delay(10);
    /*
    comm_pc = uart_comm_create(&huart4, 2048);
    uart_comm_start(comm_pc);

    HAL_TIM_RegisterCallback(&htim6, HAL_TIM_PERIOD_ELAPSED_CB_ID, test);
    HAL_TIM_Base_Start_IT(&htim6);


    dut_dac11001_init();

    HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, set_flag);
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

    // cordic test
    HAL_CORDIC_Configure(&hcordic, &(CORDIC_ConfigTypeDef) {
        .Function = CORDIC_FUNCTION_COSINE,
            .InSize = CORDIC_INSIZE_32BITS,
            .OutSize = CORDIC_OUTSIZE_32BITS,
            .NbWrite = CORDIC_NBWRITE_2,
            .NbRead = CORDIC_NBREAD_2,
            .Precision = CORDIC_PRECISION_8CYCLES,
    });

    int32_t inbuf[16];
    int32_t outbuf[16];
    double arg1, arg2, res1, res2;
    double f = 921;
    double fs = 100000;
    int32_t code;
    //uint8_t buf[256];

    //arg1 = 0.1;
    //arg2 = 1.0;

    //inbuf[0] = (double)arg1 * (double)2147483648.0;
    //inbuf[1] = (double)arg2 * (double)2147483648.0;

    //HAL_CORDIC_CalculateZO(&hcordic, inbuf, outbuf, 1, 0xFFFF);

    //res1 = (double)outbuf[0] / (double)2147483648.0;
    //res2 = (double)outbuf[1] / (double)2147483648.0;

    //// 1.00000000*cos(0.10000000/pi)=0.95105672, sin=0.30901575
    //sprintf(buf, "%.8lf*cos(%.8lf/pi)=%.8lf, sin=%.8lf\r\n", arg2, arg1, res1, res2);

    //uart_comm_write(comm_pc, buf, strlen(buf));

    // dac11001
    inbuf[0] = 0;
    inbuf[1] = 0.9 * (double)2147483648.0;
    */
    io_t* io_convst = dut_get_io(&ad7616_profiles[0], "CONVST");
    
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
        // STM32H563 TEST
        // L->H/H->L                        1nop        4ns

        // cdelay_nops(const)               1nop       	4ns
        // cdelay_nops(const)               10nop       28ns
        // cdelay_nops(const)               100nop      208ns
        
        // cdelay_nops_safe                 1nop       	20ns
        // cdelay_nops_safe                 10nop       40ns
        // cdelay_nops_safe                 100nop      220ns

        // cdelay_nops(var)                 1nop        36ns
        // cdelay_nops(var)                 10nop       70ns
        // cdelay_nops(var)                 100nop      520ns

        // (NOP IMPL when < CDELAY_NS_IMPL_THRESHOLD)
        // cdelay_ns                        0ns         4ns
        // cdelay_ns                        4ns         4ns
        // cdelay_ns                        8ns         12ns
        // cdelay_ns                        12ns        12ns
        // cdelay_ns                        16ns        16ns
        // (NOP IMPL with CAL when < CDELAY_NS_IMPL_THRESHOLD)
        // cdelay_ns                        20ns        28ns
        // cdelay_ns                        50ns        52ns
        // cdelay_ns                        78ns        80ns
        // (TICK IMPL when >= CDELAY_NS_IMPL_THRESHOLD)
        // cdelay_ns                        80ns        112ns
        // cdelay_ns                        1000ns      1024ns
        
        // cdelay_us                        1us         2us
        // cdelay_us                        10us        10.94us
        // cdelay_us                        100us       101us
        // cdelay_us                        100000us    ERROR
        
        // cdelay_ms                        10ms        11ms

        cdelay_ns(18);
        cdelay_ns(18);
        GPIOA->BSRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BSRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BSRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BRR = GPIO_PIN_1;
        cdelay_ns(18);
        GPIOA->BSRR = GPIO_PIN_1;
        cdelay_ns(18);
        cdelay_ns(18);

        /*
        // timer driven ldac
        if (flag)
        {
            cnt += 1;

           if (cnt > (double)fs / (double)2.0 / (double)f)
               cnt -= (double)fs / (double)f;

           inbuf[0] = (double)2.0 / (double)fs * (double)cnt * (double)f * (double)2147483648.0;

           HAL_CORDIC_CalculateZO(&hcordic, inbuf, outbuf, 1, 0xFFFF);

                     //outbuf[0] = arm_cos_q31(inbuf[0]);
                     //outbuf[0] *=0.9;

           code = (double)outbuf[0] / (double)2147483648.0 * (double)524288.0 - (double)524288.0;


            //code = 0.9*cos(2.0*3.14159265*cnt/(double)fs*(double)f) *(double)524288.0 - (double)524288.0 ;

                        //code = 0.9*arm_cos_f32(2.0*3.14159265*cnt/(double)fs*(double)f)*(double)524288.0 - (double)524288.0;

                    //arm_cos_q31

            dut_dac11001_set_code(0, code);
            //code = (double)outbuf[1] / (double)2147483648.0 * (double)524288.0-(double)524288.0;
            dut_dac11001_set_code(1, code);

            flag = 0;
        }
        */
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
              /* User can add his own implementation to report the file name and line number,
                 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
