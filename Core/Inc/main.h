/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define A1I6_INVS_Pin GPIO_PIN_0
#define A1I6_INVS_GPIO_Port GPIOC
#define A1I7_C2VS_Pin GPIO_PIN_1
#define A1I7_C2VS_GPIO_Port GPIOC
#define A1I8_C1VS_Pin GPIO_PIN_2
#define A1I8_C1VS_GPIO_Port GPIOC
#define A1I9_B2VS_Pin GPIO_PIN_3
#define A1I9_B2VS_GPIO_Port GPIOC
#define A1I1_B1VS_Pin GPIO_PIN_0
#define A1I1_B1VS_GPIO_Port GPIOA
#define A1I2_A2VS_Pin GPIO_PIN_1
#define A1I2_A2VS_GPIO_Port GPIOA
#define A1I3_A1VS_Pin GPIO_PIN_2
#define A1I3_A1VS_GPIO_Port GPIOA
#define ISENSE_CHC2_A2I13_Pin GPIO_PIN_5
#define ISENSE_CHC2_A2I13_GPIO_Port GPIOA
#define ISENSE_CHC1_A2I3_Pin GPIO_PIN_6
#define ISENSE_CHC1_A2I3_GPIO_Port GPIOA
#define ISENSE_CHB2_A2I4_Pin GPIO_PIN_7
#define ISENSE_CHB2_A2I4_GPIO_Port GPIOA
#define ISENSE_CHB1_A2I5_Pin GPIO_PIN_4
#define ISENSE_CHB1_A2I5_GPIO_Port GPIOC
#define ISENSE_CHA2_A2I11_Pin GPIO_PIN_5
#define ISENSE_CHA2_A2I11_GPIO_Port GPIOC
#define ISENSE_CHA1_A2I12_Pin GPIO_PIN_2
#define ISENSE_CHA1_A2I12_GPIO_Port GPIOB
#define BUZZER_TIM5_CH2_Pin GPIO_PIN_12
#define BUZZER_TIM5_CH2_GPIO_Port GPIOC
#define GPIO_BTN6_Pin GPIO_PIN_2
#define GPIO_BTN6_GPIO_Port GPIOD
#define GPIO_BTN5_Pin GPIO_PIN_3
#define GPIO_BTN5_GPIO_Port GPIOB
#define RGB_T16C1_Pin GPIO_PIN_4
#define RGB_T16C1_GPIO_Port GPIOB
#define GPIO_BTN4_Pin GPIO_PIN_5
#define GPIO_BTN4_GPIO_Port GPIOB
#define GPIO_BTN3_Pin GPIO_PIN_6
#define GPIO_BTN3_GPIO_Port GPIOB
#define GPIO_BTN2_Pin GPIO_PIN_7
#define GPIO_BTN2_GPIO_Port GPIOB
#define GPIO_BTN1_Pin GPIO_PIN_9
#define GPIO_BTN1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
