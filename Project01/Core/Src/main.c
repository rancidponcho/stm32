/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "main.h"

void SystemClock_Config(void);

// arbitrarily measures time
void delay(int t) {
	volatile int i, j;	// compiler would otherwise optimize

	for (i = 0; i < t; i++) {
		j++; // do nothing
	}
}

int main(void) {
	HAL_Init();

	/* RCC_AHBENR - Advanced High-Performance Bus Peripheral Clock Enable Register */
	// activate PortC
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // (1<<20)

	/* ModeR - Mode Register */
	// set 'alternate function' pin mode
	GPIOC->MODER |= GPIO_MODER_MODER6_0; // sets 1st bit to 1
	GPIOC->MODER &= ~GPIO_MODER_MODER6_1; // ensures 2nd bit is 0

	/* OTypeR - Output Type Register */
	// set 'output push-pull (reset state)' PP state :)
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_6;

	/* OSpeedR - Output Speed Register */
	// set 'low' speed
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR6_0; // 2nd bit is inconsequential if 1st bit = 0

	/* PUPDR - Pull Up Pull Down Register */
	// set 'no pull-up, pull down'
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6;

	SystemClock_Config();
	// set control registers for PortC pin 6

	while (1) {
		/* BSRR - Bit Set and Reset Register */
		// blink LED on port 6
		GPIOC->BSRR |= GPIO_BSRR_BS_6; // on
		delay(200000);
		GPIOC->BSRR |= GPIO_BSRR_BR_6; // off
		delay(200000);

	}
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
