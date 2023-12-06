/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the MSP.
  * @retval None
  */
void HAL_MspInit(void)
{

}

/**
* @brief TIM MSP Initialization
* This function configures the hardware resources used in this example
* @param hospi: TIM handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (TIM6 == htim->Instance)
	{
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM6_ID))
		{
			Error_Handler();
		}
	    /* Enable TIM6 clock */
	    __HAL_RCC_TIM6_CLK_ENABLE();
	}
}

/**
* @brief TIM MSP DeInitialization
* This function release the hardware resources used in this example
* @param hospi: TIM handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (TIM6 == htim->Instance)
	{
	    /* Enable TIM6 clock */
	    __HAL_RCC_TIM6_CLK_DISABLE();
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM6_ID))
		{
			Error_Handler();
		}
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
