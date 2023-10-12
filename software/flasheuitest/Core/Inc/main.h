/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Debugger.h"
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
#define D9__Pin GPIO_PIN_13
#define D9__GPIO_Port GPIOC
#define LED2_ORG_Pin GPIO_PIN_14
#define LED2_ORG_GPIO_Port GPIOC
#define LED1_GRN_Pin GPIO_PIN_15
#define LED1_GRN_GPIO_Port GPIOC
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOA
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOA
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOA
#define A3_Pin GPIO_PIN_3
#define A3_GPIO_Port GPIOA
#define F_CS_Pin GPIO_PIN_4
#define F_CS_GPIO_Port GPIOA
#define A6_Pin GPIO_PIN_0
#define A6_GPIO_Port GPIOB
#define A7_Pin GPIO_PIN_1
#define A7_GPIO_Port GPIOB
#define LED4_BLU_Pin GPIO_PIN_2
#define LED4_BLU_GPIO_Port GPIOB
#define LED3_RED_Pin GPIO_PIN_8
#define LED3_RED_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_15
#define D2_GPIO_Port GPIOA
#define D3__Pin GPIO_PIN_4
#define D3__GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_5
#define D4_GPIO_Port GPIOB
#define D5__Pin GPIO_PIN_6
#define D5__GPIO_Port GPIOB
#define D6__Pin GPIO_PIN_7
#define D6__GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_8
#define D7_GPIO_Port GPIOB
#define D8_Pin GPIO_PIN_9
#define D8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
static Debugger* DBG=NULL;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
