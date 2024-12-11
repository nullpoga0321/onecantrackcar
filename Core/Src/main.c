/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "user_car.h"
#include "user_motor.h"
#include "user_serial.h"
#include "user_servo.h"
#include "sr04.h"
#include "user_autogo.h"
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

extern uint8_t rx_buf[2];
extern float distance;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    //如果不调用这个函数就不会产生PWM
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);

  /*
  默认情况下的话我们在stm32f1xx_it.c中中断函数中写的程序是不会执行在
  串口1的中断里面的，所以要在主函数里面打开它的接收中断，然后只要我�?????
  的串口接收到数据就进到这个中断里面，后面才能进行下一步的操作�?????
  */
  HAL_UART_Receive_IT(&huart1,rx_buf,1);
  /*
  同时这个函数的作用是打开我们蓝牙串口1的接收中断，然后我们接收到了数据�?????
  我们把数据存在RX_BUF数据里面，最后这个数字表示我们每接收到一个数据我
  们就进一次中断，然后这个中断时�?�数据就保存在我们这个数组里�?????
  */
  

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
    auto_go();

    if(
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 
    ){auto_go();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 
    ){auto_go();}//这里应该是没有黑色路径了直接停止但我们让小车进行行动
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 
    ){self_right();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0
    ){car_goright();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 
    ){car_goright();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 
    ){car_goleft();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0
    ){self_left();}
    else if (
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==1 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 &&
      HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)==0 
    ){car_goleft();}
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
