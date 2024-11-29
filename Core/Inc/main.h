/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define charging_cut_off_Pin GPIO_PIN_1
#define charging_cut_off_GPIO_Port GPIOC
#define ac_led8_Pin GPIO_PIN_2
#define ac_led8_GPIO_Port GPIOC
#define sw8_ac_Pin GPIO_PIN_3
#define sw8_ac_GPIO_Port GPIOC
#define dc_volt_sense_Pin GPIO_PIN_0
#define dc_volt_sense_GPIO_Port GPIOA
#define ac_volt_sense_Pin GPIO_PIN_1
#define ac_volt_sense_GPIO_Port GPIOA
#define ac_current_sense_Pin GPIO_PIN_2
#define ac_current_sense_GPIO_Port GPIOA
#define torch_led7_Pin GPIO_PIN_0
#define torch_led7_GPIO_Port GPIOB
#define sw7_torch_Pin GPIO_PIN_1
#define sw7_torch_GPIO_Port GPIOB
#define buzzer_Pin GPIO_PIN_2
#define buzzer_GPIO_Port GPIOB
#define lcd_d7_Pin GPIO_PIN_11
#define lcd_d7_GPIO_Port GPIOB
#define lcd_d6_Pin GPIO_PIN_12
#define lcd_d6_GPIO_Port GPIOB
#define lcd_d5_Pin GPIO_PIN_13
#define lcd_d5_GPIO_Port GPIOB
#define lcd_d4_Pin GPIO_PIN_14
#define lcd_d4_GPIO_Port GPIOB
#define lcd_Enable_Pin GPIO_PIN_15
#define lcd_Enable_GPIO_Port GPIOB
#define lcd_rs_Pin GPIO_PIN_6
#define lcd_rs_GPIO_Port GPIOC
#define sw1_on_off_Pin GPIO_PIN_7
#define sw1_on_off_GPIO_Port GPIOC
#define sw2_screen_status_Pin GPIO_PIN_8
#define sw2_screen_status_GPIO_Port GPIOC
#define sw3_qc_Pin GPIO_PIN_9
#define sw3_qc_GPIO_Port GPIOC
#define sw4_pd_Pin GPIO_PIN_8
#define sw4_pd_GPIO_Port GPIOA
#define sw5_9v_Pin GPIO_PIN_9
#define sw5_9v_GPIO_Port GPIOA
#define sw6_12v_Pin GPIO_PIN_10
#define sw6_12v_GPIO_Port GPIOA
#define on_off_led1_Pin GPIO_PIN_11
#define on_off_led1_GPIO_Port GPIOA
#define sreen_status_led2_Pin GPIO_PIN_12
#define sreen_status_led2_GPIO_Port GPIOA
#define qc_led3_Pin GPIO_PIN_10
#define qc_led3_GPIO_Port GPIOC
#define pd_led4_Pin GPIO_PIN_11
#define pd_led4_GPIO_Port GPIOC
#define nine_led5_Pin GPIO_PIN_12
#define nine_led5_GPIO_Port GPIOC
#define led6_Pin GPIO_PIN_2
#define led6_GPIO_Port GPIOD
#define pwm_L2_Pin GPIO_PIN_4
#define pwm_L2_GPIO_Port GPIOB
#define pmm_H2_Pin GPIO_PIN_5
#define pmm_H2_GPIO_Port GPIOB
#define pwm_L1_Pin GPIO_PIN_6
#define pwm_L1_GPIO_Port GPIOB
#define pwm_H1_Pin GPIO_PIN_7
#define pwm_H1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
