/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "7segmentLED.h"
#include <stdlib.h>
#include <stdio.h>
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const int MAX_LED = 4;
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
int led_buffer[4] = {1, 8, 0, 9};

// quet cot hang
uint16_t cot[8] = {ENM0_Pin, ENM1_Pin, ENM2_Pin, ENM3_Pin, ENM4_Pin, ENM5_Pin, ENM6_Pin, ENM7_Pin};
uint16_t hang[8] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin};
// ma gui ra cot
uint16_t matrix_buffer[8] = {0x18, 0x3c, 0x66, 0x66, 0x7e, 0x7e, 0x66, 0x66};
// ma quet hang
uint16_t bytes[8] = {
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80,
};
int hour = 18;
int minute = 9;
int second = 50;

void update7SEG(int index)
{
  switch (index)
  {
  case 0:
    display7Seg(led_buffer[0]);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
    break;
  case 1:
    display7Seg(led_buffer[1]);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
    break;
  case 2:
    display7Seg(led_buffer[2]);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
    break;
  case 3:
    display7Seg(led_buffer[3]);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
    break;
  default:
    break;
  }
}
void updateClockBuffer()
{
  led_buffer[0] = hour / 10;
  led_buffer[1] = hour % 10;
  led_buffer[2] = minute / 10;
  led_buffer[3] = minute % 10;
}

void writeByte(GPIO_TypeDef *port, uint16_t *pins, uint16_t byte)
{
  HAL_GPIO_WritePin(port, pins[0], byte & (uint16_t)0x01);
  HAL_GPIO_WritePin(port, pins[1], byte & (uint16_t)0x02);
  HAL_GPIO_WritePin(port, pins[2], byte & (uint16_t)0x04);
  HAL_GPIO_WritePin(port, pins[3], byte & (uint16_t)0x08);
  HAL_GPIO_WritePin(port, pins[4], byte & (uint16_t)0x10);
  HAL_GPIO_WritePin(port, pins[5], byte & (uint16_t)0x20);
  HAL_GPIO_WritePin(port, pins[6], byte & (uint16_t)0x40);
  HAL_GPIO_WritePin(port, pins[7], byte & (uint16_t)0x80);
}

void updateLedMatrix(int index)
{
  uint16_t temp = matrix_buffer[index];
  switch (index)
  {
  case 0:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x01);
    break;
  case 1:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x02);

    break;
  case 2:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x04);

    break;
  case 3:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x08);

    break;
  case 4:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x10);

    break;
  case 5:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x20);

    break;
  case 6:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x40);

    break;
  case 7:
    writeByte(GPIOA, cot, ~(temp));
    writeByte(GPIOB, hang, ~0x80);
    break;
  default:
    break;
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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  setTimer1(100);
  setTimer2(25);
  setTimer3(10); // fai lam tan so  >= 25hz
  clearDisplay7Seg();

  int ledPos = 1;
  HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 1);
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);

  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

  HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_RESET);
  updateLedMatrix(0);
  update7SEG(0);
  updateClockBuffer();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if (timer1_flag == 1)
    {
      second++;
      if (second >= 60)
      {
        second = 0;
        minute++;
      }
      if (minute >= 60)
      {
        minute = 0;
        hour++;
      }
      if (hour >= 24)
      {
        hour = 0;
      }
      updateClockBuffer();
      HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
      setTimer1(100);
    }
    if (timer2_flag == 1)
    {
      update7SEG(ledPos % 4);
      ledPos++;
      if (ledPos > 3)
        ledPos = 0;
      setTimer2(25);
    }
    if (timer3_flag == 1)
    {
      updateLedMatrix(index_led_matrix++);
      if (index_led_matrix >= 8)
      {
        setTimer3(10);
        index_led_matrix = 0;
      }
      else
      {
        setTimer3(5);
      }
    }
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin | ENM1_Pin | DOT_Pin | LED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin | ROW0_Pin | ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin | ENM1_Pin | DOT_Pin | LED_Pin | EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin | ENM2_Pin | ENM3_Pin | ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin | SEG1_Pin | SEG2_Pin | ROW2_Pin | ROW3_Pin | ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin | ROW0_Pin | ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerRun();
}
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
