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


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
* @brief IPCC MSP Initialization
* This function configures the hardware resources used in this example
* @param hipcc: IPCC handle pointer
  * @retval None
  */
void HAL_IPCC_MspInit(IPCC_HandleTypeDef* hipcc)
{

  if(hipcc->Instance==IPCC1)
  {
    /* USER CODE BEGIN IPCC_MspInit 0 */

    /* USER CODE END IPCC_MspInit 0 */
    /* Peripheral clock enable */
	  if(ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(87)) == RESMGR_STATUS_ACCESS_OK) {
		  __HAL_RCC_IPCC1_CLK_ENABLE();
	  } else {
		  /* RCC->HPDMA3CFGR not already enabled */
		  if(READ_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN) != RCC_IPCC1CFGR_IPCC1EN) {
			  Error_Handler();
		  }
	  }
    /* USER CODE BEGIN IPCC_MspInit 1 */

    /* USER CODE END IPCC_MspInit 1 */
  }
}

  /**
  * @brief IPCC MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hipcc: IPCC handle pointer
  * @retval None
  */

void HAL_IPCC_MspDeInit(IPCC_HandleTypeDef* hipcc)
{

  if(hipcc->Instance==IPCC1)
  {
    /* USER CODE BEGIN IPCC_MspDeInit 0 */

    /* USER CODE END IPCC_MspDeInit 0 */
    /* Peripheral clock disable */

	if(ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(87)) == RESMGR_STATUS_ACCESS_OK) {
	  __HAL_RCC_IPCC1_CLK_DISABLE();
	}

    /* IPCC interrupt DeInit */
    HAL_NVIC_DisableIRQ(IPCC1_RX_IRQn);
    /* USER CODE BEGIN IPCC_MspDeInit 1 */

    /* USER CODE END IPCC_MspDeInit 1 */
  }
 }
void ResMgr_LL_RCC_GPIOG_EnableClock()
{
	  if(ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(96)) == RESMGR_STATUS_ACCESS_OK) {
		  LL_RCC_GPIOG_EnableClock();
	  } else {
		  /* RCC->GPIOGCFGR not already enabled */
		  if(!READ_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN)) {
			  loc_printf("RCC GPIO G Clock get resource failed\n");
			  Error_Handler();
		  }
	  }
}
void ResMgr_LL_RCC_HPDMA3_EnableClock()
{
	  /* Peripheral clock enable */
	  if(ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(85)) == RESMGR_STATUS_ACCESS_OK) {
		  LL_RCC_HPDMA3_EnableClock();
	  } else {
		  /* RCC->HPDMA3CFGR not already enabled */
		  if(READ_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN) != RCC_HPDMA3CFGR_HPDMA3EN) {
			  loc_printf("RCC HPDMA3 Clock get resource failed\n");
			  Error_Handler();
		  }
	  }
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
