/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t MAXLED = 62;   //aantal leds//

uint32_t pData[63]; //TODO check
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI2_Init(void);

/* USER CODE BEGIN PFP */
void zet1LedAanR(uint8_t index, uint32_t * buffer)
{
	buffer[0] = 0x00000000;
	for(int i=1; i < (MAXLED); i++ )
	{
		if(i == index)				// init led
		{
			buffer[i]= 0x25FF0000;
		}
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}

void zetOpLed(uint8_t index, uint32_t * buffer, uint8_t *rdata)
{
	buffer[0] = 0x00000000;
	for(int i=0; i < (MAXLED); i++ )
	{
		switch(rdata[i-1]){
		case '0':
			buffer[i+1] = 0x25000000;
			break;
		case '1':
			buffer[i+1] = 0x25FF0000;
			break;
		case '2':
			buffer[i+1] = 0x2500FF00;
			break;
		case '3':
			buffer[i+1] = 0x25FFFF00;
			break;
		case '4':
			buffer[i+1] = 0x250000FF;
			break;
		case '5':
			buffer[i+1] = 0x25FF00FF;
			break;
		case '6':
			buffer[i+1] = 0x2500FFFF;
			break;
		case '7':
			buffer[i+1] = 0x25FFFFFF;
			break;
		}
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}

void zet1LedAanG(uint8_t index, uint32_t * buffer)
{
	buffer[0] = 0x00000000;
	for(int i=1; i < (MAXLED); i++ )
	{
		if(i == index)				// init led
		{
			buffer[i]= 0x2500FF00;
		}
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}


void zet1LedAanZ(uint8_t index, uint32_t * buffer)
{
//	for(int i=0; i <=(MAXLED+1); i++ )
//		{
//			if (i==0)					// init startbit
//			{
//				pData[i] = 0x00000000;
//
//			} else
//			{
//				if (i==(MAXLED+1))			// init stopbit
//				{
//					pData[i] = 0xFFFFFFFF;
//				}
//				else
//				{
//					if(i == index)				// init led
//					{
//						buffer[i]= 0x50000000;
//					}
//				}
//			}
//		}

	buffer[0] = 0x00000000;
	for(int i=1; i < (MAXLED); i++ )
	{
		if(i == index)				// init led
		{
			buffer[i]= 0x25000000;
		}
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}

void zet1LedAanW(uint8_t index, uint32_t * buffer)
{
//	for(int i=0; i <=(MAXLED+1); i++ )
//	{
//			if (i==0)					// init startbit
//			{
//				pData[i] = 0x00000000;
//
//			} else
//			{
//				if (i==(MAXLED+1))			// init stopbit
//				{
//					pData[i] = 0xFFFFFFFF;
//				}
//				else
//				{
//					if(i == index)				// init led
//					{
//						buffer[i]= 0x50FFFFFF;
//					}
//				}
//			}
//		}


	buffer[0] = 0x00000000;
	for(int i=1; i < (MAXLED); i++ )
	{
		if(i == index)				// init led
		{
			buffer[i]= 0x25FFFFFF;
		}
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}

void zetalleLedUit(uint32_t * buffer)
{
//	for(int i=0; i <=(MAXLED+1); i++ )
//	{
//		if (i==0)					// init startbit
//		{
//			pData[i] = 0x00000000;
//
//		}
//		else
//		{
//			if (i==(MAXLED+1))			// init stopbit
//			{
//				pData[i] = 0xFFFFFFFF;
//			}
//				else								// andere leds uit
//				{
//					buffer[i]   = 0xF0000000; //Uit
//
//				}
//			}
//	}


	buffer[0] = 0x00000000;
	for(int i=1; i < (MAXLED); i++ )
	{
		buffer[i]= 0x25000000;
	}
	buffer[MAXLED] = 0xFFFFFFFF;
}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */
  /*	  zet1LedAanR(10,pData);
   	 HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
   	 HAL_Delay(1000);*/
//  	  zetalleLedUit(pData);
// 	  HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
 	 // HAL_Delay(1000);

  /* USER CODE END 2 */
  zetalleLedUit(pData);
  	  HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  volatile HAL_UART_StateTypeDef wdatest;
	  uint8_t Uartbuffer[62];
	  memset(Uartbuffer, 0, 62);

	  wdatest =  HAL_UART_GetState(&huart1);
	  HAL_UART_Receive(&huart1, Uartbuffer, 61, HAL_MAX_DELAY );

	  zetOpLed(0, pData, Uartbuffer);
	  HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
	  HAL_Delay(100);
  }
	  /*for(int i=0;i<10;i++)
	  {
		  if(Uartbuffer[i] == "0")
		  {
//		  		  for(int i = 0; i < 10; i++){
//		  			  HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_1);
//		  			  HAL_Delay(200);
//		  		  }
//			  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_1,GPIO_PIN_RESET);
			  zet1LedAanZ(i,pData);
			  HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
			  HAL_Delay(100);
		  	  }
		  if (Uartbuffer[i] == '1')
		  {
			zet1LedAanR(i,pData);
			HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
			HAL_Delay(100);
		  }
		  if (Uartbuffer[i] == '2')
		  {
			zet1LedAanG(i,pData);
			HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
			HAL_Delay(100);
		  }
		  	  else
		  	  {
//		  		  for(int i = 0; i < 6; i++)
//		  		  {
//		  			  HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_1);
//		  			  HAL_Delay(500);
//		  		  }
//		  		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_1,GPIO_PIN_SET);
		  		 //zetalleLedUit(pData);
		  		zet1LedAanW(i,pData);
		  		 HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
  				 HAL_Delay(100);
		  	  }
	  }

  }
//	  	  for(uint8_t i=0;i<62;i++)
//	  	  {
//	  		  if(buffer[i] == '0')
//	  		  {
//	  			zet1LedAanZ(i,pData);
//	  		  }
//
//	  		  if(buffer[i] == '1')
//	  		  {
//	  			zet1LedAanR(i,pData);
//	  		  }
//	  		  else
//	  		  {
//	  			zet1LedAanW(i,pData);
//	  		  }
//	  		  HAL_SPI_Transmit(&hspi2, (uint8_t*)pData, sizeof(pData), HAL_MAX_DELAY);
//	  		  HAL_Delay(250);
 */

  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 10;
  RCC_OscInitStruct.PLL.PLLN = 210;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
