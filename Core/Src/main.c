/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stdint.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
	uint32_t map(uint32_t x,
	                 uint32_t in_min,  uint32_t in_max,
	                 uint32_t out_min, uint32_t out_max)
	{
	    return ((x - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min;
	}
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
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  char msg[] = "STM32 UART ready\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    int p = 0;
    int c = 0;
    int z = 0;
	uint32_t duty;
     while (1)
     {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
         uint8_t rxByte;
         // Čekaj 1 bajt s PC-a (timeout 1000 ms)

         if (HAL_UART_Receive(&huart2, &rxByte, 1, 1000) == HAL_OK)
         {
        	 //HAL_UART_Transmit(&huart2, &rxByte, 1, HAL_MAX_DELAY);

          /////////plava/////////////////////
       	  if(rxByte == 'a' && p == 0){
       		  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
       		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 255);
       		  char msg[] = "Plava ledica upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  p = 1;
       	  }
       	  else if(rxByte == 'b' && p == 1){
       		  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
       		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);
       		  char msg[] = "Plava ledica ugašena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  p = 0;
       	  }

       	  else if(rxByte == 'a' && p == 1){
       		  char msg[] = "Plava ledica je već upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(rxByte == 'b' && p == 0){
       	      	char msg[] = "Plava ledica je već ugašena\r\n";
       	      	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(p == 1 && rxByte >= 0 && rxByte <= 10){
       		  //uint8_t vrijednost = rxByte;
       		//char msg[] = "Mijenjam vrijednost\r\n";
       		 //HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		duty = map(rxByte, 1, 10, 0, 255);
       		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
       		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty);
       	  }

          /////////crvena/////////////////////
       	  if(rxByte == 'c' && c == 0){
       		  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
       		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 255);
       		  char msg[] = "Crvena ledica upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  c = 1;
       	  }
       	  else if(rxByte == 'd' && c == 1){
       		  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
       		  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
       		  char msg[] = "Crvena ledica ugašena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  c = 0;
       	  }

       	  else if(rxByte == 'c' && c == 1){
       		  char msg[] = "Crvena ledica je već upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(rxByte == 'd' && c == 0){
       	      	char msg[] = "Crvena ledica je već ugašena\r\n";
       	      	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(c == 1 && rxByte >= 11 && rxByte <= 20){
       		  //uint8_t vrijednost = rxByte;
       		//char msg[] = "Mijenjam vrijednost\r\n";
       		 //HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		duty = map(rxByte, 11, 20, 0, 255);
       		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
       		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);
       	  }

          /////////zelena/////////////////////
       	  if(rxByte == 'e' && z == 0){
       		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
       		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 255);
       		  char msg[] = "Zelena ledica upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  z = 1;
       	  }
       	  else if(rxByte == 'f' && z == 1){
       		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
       		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
       		  char msg[] = "Zelena ledica ugašena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		  z = 0;
       	  }

       	  else if(rxByte == 'e' && z == 1){
       		  char msg[] = "Zelena ledica je već upaljena\r\n";
       		  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(rxByte == 'f' && z == 0){
       	      	char msg[] = "Zelena ledica je već ugašena\r\n";
       	      	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       	  }
       	  else if(z == 1 && rxByte >= 21 && rxByte <= 30){
       		  //uint8_t vrijednost = rxByte;
       		//char msg[] = "Mijenjam vrijednost\r\n";
       		 //HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
       		duty = map(rxByte, 21, 30, 0, 255);
       		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
       		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
       	  }


           // Vrati isti bajt nazad na PC (echo)
           //HAL_UART_Transmit(&huart2, &rxByte, 1, HAL_MAX_DELAY);
         }
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
#ifdef USE_FULL_ASSERT
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
