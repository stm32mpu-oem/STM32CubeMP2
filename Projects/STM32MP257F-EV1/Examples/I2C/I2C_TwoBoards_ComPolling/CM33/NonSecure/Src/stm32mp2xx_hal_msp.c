/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
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

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  if(I2C8 == hi2c->Instance)
  {
    /* USER CODE BEGIN I2C8_MspInit 0 */
    /* USER CODE END I2C8_MspInit 0 */
	/* Acquire I2C8 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_I2C8_ID))
	{
		Error_Handler();
	}

	__HAL_RCC_I2C8_CLK_ENABLE();
	__HAL_RCC_I2C8_FORCE_RESET();
	__HAL_RCC_I2C8_RELEASE_RESET();

    /* USER CODE BEGIN I2C8_MspInit 1 */
    /* USER CODE END I2C8_MspInit 1 */
  }

}

void HAL_I2C_MspPostInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* USER CODE BEGIN I2C_MspPostInit 0 */

	/* USER CODE END I2C_MspPostInit 0 */
	if(I2C8 == hi2c->Instance)
	{
		/* Acquire GPIOZ3 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOZ, RESMGR_GPIO_PIN(3)))
		{
			Error_Handler();
		}
		/* Acquire GPIOZ4 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOZ, RESMGR_GPIO_PIN(4)))
		{
			Error_Handler();
		}
	    /**I2C8 GPIO Configuration
			PZ3      ------> I2C8_SDA
			PZ4      ------> I2C8_SCL
	    */
		/* Enable GPIOs power supplies */
		if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(101)))
		{
			__HAL_RCC_GPIOZ_CLK_ENABLE();
		}

	    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF8_I2C8;
	    HAL_GPIO_Init(GPIOZ, &GPIO_InitStruct);
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  /* USER CODE BEGIN I2C8_MspDeInit 0 */

  /* USER CODE END I2C8_MspDeInit 0 */
  if(I2C8 == hi2c->Instance)
  {
	/* Peripheral clock disable */
  __HAL_RCC_I2C8_CLK_DISABLE();

    /**I2C8 GPIO Configuration
    PZ3      ------> I2C8_SDA
    PZ4      ------> I2C8_SCL
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4 | GPIO_PIN_5);

    /* I2C8 interrupt DeInit */
    HAL_NVIC_DisableIRQ(I2C8_IRQn);

	/* Release I2C8 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_I2C8_ID))
	{
		Error_Handler();
	}
	/* Release GPIOZ3 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOZ, RESMGR_GPIO_PIN(3)))
	{
		Error_Handler();
	}
	/* Release GPIOZ4 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOZ, RESMGR_GPIO_PIN(4)))
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C8_MspDeInit 1 */
	/* USER CODE END I2C8_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */
