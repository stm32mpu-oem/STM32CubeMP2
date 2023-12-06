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


extern DMA_HandleTypeDef hdma_tim8_up;

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



/**
*/

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspDeInit 0 */

  /* USER CODE END TIM8_MspDeInit 0 */
    if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, RESMGR_RIFSC_TIM8_ID))
    {
      Error_Handler();
    }
    /* TIM8 clock enable */
	__HAL_RCC_TIM8_CLK_ENABLE();

	/* HPDMA controller clock enable */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_HPDMA3, RESMGR_HPDMA_CHANNEL(1)))
	{
	  Error_Handler();
	}
    /* TIM8 HPDMA Init */
    hdma_tim8_up.Instance = HPDMA3_Channel1;
    hdma_tim8_up.Init.Request = HPDMA_REQUEST_TIM8_UP;
    hdma_tim8_up.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim8_up.Init.SrcInc = DMA_SINC_INCREMENTED;
	hdma_tim8_up.Init.DestInc = DMA_DINC_FIXED;
    hdma_tim8_up.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_WORD;
    hdma_tim8_up.Init.DestDataWidth = DMA_DEST_DATAWIDTH_WORD;
    hdma_tim8_up.Init.Mode = DMA_NORMAL;
    hdma_tim8_up.Init.Priority = DMA_HIGH_PRIORITY;

    HAL_DMA_DeInit(&hdma_tim8_up);

    if (HAL_DMA_Init(&hdma_tim8_up) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(htim_pwm, hdma[TIM_DMA_ID_UPDATE], hdma_tim8_up);

    /* HPDMA interrupt init */
    /* HPDMA3_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(HPDMA3_Channel1_IRQn, DEFAULT_IRQ_PRIO, 0);
    HAL_NVIC_EnableIRQ(HPDMA3_Channel1_IRQn);
  }
  /* USER CODE BEGIN TIM8_MspInit 1 */

  /* USER CODE END TIM8_MspInit 1 */

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspPostInit 0 */

  /* USER CODE END TIM8_MspPostInit 0 */
    /**TIM8 GPIO Configuration
    PJ4     ------> TIM8_CH4
    */
	/* Enable GPIOs power supplies */
	if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(99)))
	{
		__HAL_RCC_GPIOJ_CLK_ENABLE();
	}
	if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOJ, RESMGR_GPIO_PIN(4)))
    {
	    GPIO_InitStruct.Pin = GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF8_TIM8;
	    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
	}
  /* USER CODE BEGIN TIM8_MspPostInit 1 */

  /* USER CODE END TIM8_MspPostInit 1 */
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{


  if(htim_pwm->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspDeInit 0 */

  /* USER CODE END TIM8_MspDeInit 0 */
    /* TIM1 DMA DeInit */
    HAL_DMA_DeInit(htim_pwm->hdma[TIM_DMA_ID_UPDATE]);

    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();
    /**TIM8 GPIO Configuration
    PJ4     ------> TIM8_CH4 */
    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_4);
    ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOJ, RESMGR_GPIO_PIN(4));
  }
 /* USER CODE BEGIN TIM8_MspDeInit 1 */

  /* USER CODE END TIM8_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */
