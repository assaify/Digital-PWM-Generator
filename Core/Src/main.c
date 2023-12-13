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
#include "stdio.h"
#include "LCD16x2.h"
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
static void LCD_Change_Menu(void);
static void LCD_Update(void);
static void LCD_Update_Mul(void);
static void Menu_Front(void);
static void Menu_Set(void);
static void Menu_Set_DS(void);
static void Menu_Set_Freq(void);
static void PWM_Calc(void);
static void PWM_Gen(void);
static void PWM_Stop(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int ds;
int freq;
int menu;
int pointer_pos;
int multiplier;
int generate_pwm;

char int_str_ds[3];
char int_str_freq[5];
char int_str_mul;

int LCDRefresh;
int LCDRefreshMenu;
int LCDRefreshPWM;
int LCDRefreshMul;
int PWMRefresh;
int PWMToggle;

int CLKNow;
int CLKPrev;
int DTNow;
int DTPrev;
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
  CLKPrev = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
  DTPrev = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
  ds = 50;
  freq = 1000;
  menu = 1;
  pointer_pos = 1;
  multiplier = 0;
  generate_pwm = 0;

  LCDRefresh = 1;
  LCDRefreshPWM = 1;
  LCDRefreshMenu = 1;
  LCDRefreshMul = 0;
  PWMRefresh = 1;
  PWMToggle = 0;

  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (LCDRefresh == 1)
	  {
		  if (LCDRefreshMenu == 1)
		  {
			  LCD_Change_Menu();
			  LCDRefreshMenu = 0;
		  }
		  LCD_Update();
		  LCDRefresh = 0;
		  LCDRefreshPWM = 0;
	  }
	  if (LCDRefreshMul == 1)
	  {
		  LCD_Update_Mul();
		  LCDRefreshMul = 0;
	  }
	  if (PWMRefresh == 1)
	  {
		  PWM_Calc();
		  PWMRefresh = 0;
	  }
	  if (PWMToggle == 1)
	  {
		  if(generate_pwm == 1)
		  {
			  PWM_Gen();
		  }
		  else
		  {
			  PWM_Stop();
		  }
		  PWMToggle = 0;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1399;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6
                           PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void LCD_Change_Menu(void)
{
	LCD_Clear();
	switch (menu)
	{
	case 1:
		Menu_Front();
	break;
	case 2:
		Menu_Set();
	break;
	case 3:
		Menu_Set_DS();
	break;
	case 4:
		Menu_Set_Freq();
	break;
	}
	pointer_pos = 1;
	multiplier = 0;
}
static void LCD_Update(void)
{
	switch (menu)
	{
	case 1:
		LCD_Set_Cursor(1, 3);
		LCD_Write_String("     ");
		LCD_Set_Cursor(2, 3);
		LCD_Write_String("     ");
		sprintf(int_str_ds, "%d", ds);
		LCD_Set_Cursor(1, 3);
		LCD_Write_String(int_str_ds);
		sprintf(int_str_freq, "%d", freq);
		LCD_Set_Cursor(2, 3);
		LCD_Write_String(int_str_freq);
		if (LCDRefreshPWM == 1)
		{
			LCD_Set_Cursor(1, 14);
			if (generate_pwm == 1)
			{
				LCD_Write_String("ON ");
			}
			else
			{
				LCD_Write_String("OFF");
			}
		}
		if (pointer_pos == 1)
		{
			LCD_Set_Cursor(2, 13);
			LCD_Write_Char(0xFE);
			LCD_Set_Cursor(1, 13);
			LCD_Write_Char(0x7E);
		}
		else
		{
			LCD_Set_Cursor(1, 13);
			LCD_Write_Char(0xFE);
			LCD_Set_Cursor(2, 13);
			LCD_Write_Char(0x7E);
		}
	break;
	case 2:
		LCD_Set_Cursor(1, 1);
		LCD_Write_Char(0xFE);
		LCD_Set_Cursor(2, 1);
		LCD_Write_Char(0xFE);
		LCD_Set_Cursor(1, 10);
		LCD_Write_Char(0xFE);
		if(pointer_pos == 1)
		{
			LCD_Set_Cursor(1, 1);
			LCD_Write_Char(0x7E);
		}
		else if(pointer_pos == 2)
		{
			LCD_Set_Cursor(2, 1);
			LCD_Write_Char(0x7E);
		}
		else
		{
			LCD_Set_Cursor(1, 10);
			LCD_Write_Char(0x7E);
		}
	break;
	case 3:
		sprintf(int_str_ds, "%d", ds);
		LCD_Set_Cursor(2, 1);
		LCD_Write_String("   ");
		LCD_Set_Cursor(2, 1);
		LCD_Write_String(int_str_ds);
	break;
	case 4:
		sprintf(int_str_freq, "%d", freq);
		LCD_Set_Cursor(2, 1);
		LCD_Write_String("     ");
		LCD_Set_Cursor(2, 1);
		LCD_Write_String(int_str_freq);
	break;
	}
}
static void LCD_Update_Mul(void)
{
	if (menu == 3 || menu == 4)
	{
		int_str_mul = multiplier + '0';
		LCD_Set_Cursor(1, 16);
		LCD_Write_Char(int_str_mul);
	}
}
static void Menu_Front(void)
{
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("D        %      ");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String("F        Hz  SET");
}
static void Menu_Set(void)
{
	LCD_Set_Cursor(1, 1);
	LCD_Write_String(" DS       Return");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String(" Freq           ");
}
static void Menu_Set_DS(void)
{
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("Duty Cycle    M ");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String("               %");
}
static void Menu_Set_Freq(void)
{
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("Frequency     M ");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String("              Hz");
}
static void PWM_Calc(void)
{
	if (freq > 0)
	{
		//TIM2->ARR = 84004200 - (4200 * freq);
		TIM2->PSC = (60000 / freq) - 1;
		if (ds != 0 && ds != 100)
		{
//			TIM2->CCR1 = (TIM2->ARR / 100) * ds;
			TIM2->CCR1 = (TIM2->ARR / 100) * ds;
		}
	}
}
static void PWM_Gen(void)
{
	if (ds == 100 || freq == 0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	}
	else if (ds == 0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	}
	else
	{
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	}
}
static void PWM_Stop(void)
{
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_1)
    {
    	switch(menu)
    	{
    	case 1:
    			if (pointer_pos == 1)
    			{
    				pointer_pos = 2;
    			}
    			else
    			{
    				pointer_pos = 1;
    			}
    	break;
    	case 2:
    			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
    			{
    				if (pointer_pos < 3)
    				{
    					pointer_pos++;
    				}
    				else
    				{
    					pointer_pos = 1;
    				}
    			}
    			else
    			{
    				if (pointer_pos > 1 )
    				{
    					pointer_pos--;
    				}
    				else
    				{
    					pointer_pos = 3;
    				}
    			}
    	break;
    	case 3:
    			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
    			{
    				if (ds < 100)
    				{
    					if(multiplier == 1 && ds <= 90)
    					{
    						ds = ds + 10;
    					}
    					else if (multiplier == 1 && ds > 90)
    					{
    						ds = 100;
    					}
    					else
    					{
    						ds++;
    					}
    				}
    				else
    				{
    					ds = 100;
    				}
    			}
    			else if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1))
    			{
    				if (ds > 0)
    				{
    					if(multiplier == 1 && ds >= 10)
    					{
    						ds = ds - 10;
    					}
    					else if (multiplier == 1 && ds < 10)
    					{
    						ds = 0;
    					}
    					else
    					{
    						ds--;
    					}
    				}
    				else
    				{
    					ds = 0;
    				}
    			}
    	break;
    	case 4:
    			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0)
    			{
    				if (freq < 20000)
    				{
    					if(multiplier == 1 && freq <= 19990)
    					{
    						freq = freq + 10;
    					}
    					else if (multiplier == 1 && freq > 19990)
    					{
    						freq = 20000;
    					}
    					else if (multiplier == 2 && freq <= 19900)
    					{
    						freq = freq + 100;
    					}
    					else if (multiplier == 2 && freq > 19900)
    					{
    						freq = 20000;
    					}
    					else if (multiplier == 3 && freq <= 19000)
    					{
    						freq = freq + 1000;
    					}
    					else if (multiplier == 3 && freq > 19000)
    					{
    						freq = 20000;
    					}
    					else
    					{
    						freq++;
    					}
    				}
    				else
    				{
    					freq = 20000;
    				}
    			}
    			else
    			{
    				if (freq > 0)
    				{
    					if(multiplier == 1 && freq >= 10)
    					{
    						freq = freq - 10;
    					}
    					else if (multiplier == 1 && freq < 10)
    					{
    						freq = 0;
    					}
    					else if (multiplier == 2 && freq >= 100)
    					{
    						freq = freq - 100;
    					}
    					else if (multiplier == 2 && freq < 100)
    					{
    						freq = 0;
    					}
    					else if (multiplier == 3 && freq >= 1000)
    					{
    						freq = freq - 1000;
    					}
    					else if (multiplier == 3 && freq < 1000)
    					{
    						freq = 0;
    					}
    					else
    					{
    						freq--;
    					}
    				}
    				else
    				{
    					freq = 0;
    				}
    			}
    	break;
    	}
    	LCDRefresh = 1;
    }
    else if (GPIO_Pin == GPIO_PIN_12)
    {
    	switch(menu)
    	{
    	case 1:
    		if (pointer_pos == 1)
    		{
    			generate_pwm ^= 1;
    			LCDRefreshPWM = 1;
    			PWMToggle = 1;
    		}
    		else
    		{
    			menu = 2;
    			LCDRefreshMenu = 1;
    		}
    	break;
    	case 2:
    	    if (pointer_pos == 1)
    	    {
    	    	menu = 3;
    	    	LCDRefreshMul = 1;
    	    }
    	    else if (pointer_pos == 2)
    	    {
    	    	menu = 4;
    	    	LCDRefreshMul = 1;
    	    }
    	    else
    	    {
    	    	menu = 1;
    	    	LCDRefreshPWM = 1;
    	    	LCDRefresh = 1;
    	    	PWMRefresh = 1;
    	    }
    	    LCDRefreshMenu = 1;
    	break;
    	case 3:
    		menu = 2;
    		LCDRefreshMenu = 1;
    	break;
    	case 4:
    		menu = 2;
    		LCDRefreshMenu = 1;
    	break;
    	}
    	LCDRefresh = 1;
    }
    else if (GPIO_Pin == GPIO_PIN_13)
    {
    	if (menu == 3)
    	{
    		if (multiplier == 0)
    		{
    			multiplier = 1;
    		}
    		else
    		{
    			multiplier = 0;
    		}
    		LCDRefreshMul = 1;
    	}
    	else if (menu == 4)
    	{
    		if (multiplier < 3)
    		{
    			multiplier ++;
    		}
    		else
    		{
    			multiplier = 0;
    		}
    		LCDRefreshMul = 1;
    	}
    	else
    	{
    		multiplier = 0;
    	}
    }
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
