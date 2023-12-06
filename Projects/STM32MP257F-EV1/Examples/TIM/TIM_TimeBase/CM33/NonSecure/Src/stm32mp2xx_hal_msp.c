/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "res_mgr.h"

extern void Error_Handler(void);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */

  if(htim_base->Instance==TIM3)
  {
	/* Acquire TIM3 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM3_ID))
	{
		Error_Handler();
	}
    /* TIM3 clock enable */
	__HAL_RCC_TIM3_CLK_ENABLE();

	/* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM3_IRQn, DEFAULT_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }

  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  /* USER CODE BEGIN TIM3_MspDeInit 0 */
  /* USER CODE END TIM3_MspDeInit 0 */

  if(htim_base->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

	/* Release TIM3 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM3_ID))
	{
		Error_Handler();
	}
  }

  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */
