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

extern DMA_HandleTypeDef handle_HPDMA3_Channel0;

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
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if(huart->Instance == UART5)
  {
  /* USER CODE BEGIN UART5_MspInit 0 */

  /* USER CODE END UART5_MspInit 0 */
    /* Peripheral clock enable */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_UART5_ID))
	{
		Error_Handler();
	}
    __HAL_RCC_UART5_CLK_ENABLE();

    /* Acquire GPIOG10 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOG, RESMGR_GPIO_PIN(10)))
	{
		Error_Handler();
	}
	/* Acquire GPIOG9 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOG, RESMGR_GPIO_PIN(9)))
	{
		Error_Handler();
	}
	/* Enable GPIOs power supplies */
	if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(96)))
	{
	    __HAL_RCC_GPIOG_CLK_ENABLE();
	}
    /**UART5 GPIO Configuration
    PG10     ------> UART5_RX
    PG9     ------> UART5_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_UART5;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN UART5_MspInit 1 */

  /* USER CODE END UART5_MspInit 1 */
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==UART5)
  {
  /* USER CODE BEGIN UART5_MspDeInit 0 */

  /* USER CODE END UART5_MspDeInit 0 */
    /* Peripheral clock disable */
	__HAL_RCC_UART5_CLK_DISABLE();

    /**UART5 GPIO Configuration
    PG10     ------> UART5_RX
    PG9     ------> UART5_TX
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_10 | GPIO_PIN_9);

    /* Acquire GPIOG10 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOG, RESMGR_GPIO_PIN(10)))
	{
		Error_Handler();
	}
	/* Acquire GPIOG9 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOG, RESMGR_GPIO_PIN(9)))
	{
		Error_Handler();
	}
    if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_UART5_ID))
	{
		Error_Handler();
	}

  /* USER CODE BEGIN UART5_MspDeInit 1 */

  /* USER CODE END UART5_MspDeInit 1 */
  }

}

/**
* @brief OSPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hospi: OSPI handle pointer
* @retval None
*/
void HAL_OSPI_MspInit(OSPI_HandleTypeDef* hospi)
{
  if(OCTOSPI2 == hospi->Instance)
  {
  /* USER CODE BEGIN OCTOSPI2_MspInit 0 */

  /* USER CODE END OCTOSPI2_MspInit 0 */

    /* Peripheral clock enable */
    /* Enable the OctoSPI memory interface clock */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_OCTOSPI2_ID))
	{
		Error_Handler();
	}
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_OCTOSPIM_ID))
	{
		Error_Handler();
	}
	if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(111)))
	{
		__HAL_RCC_OSPI2_CLK_ENABLE();
		/* Reset the OctoSPI memory interface */
		__HAL_RCC_OSPI2_FORCE_RESET();
		__HAL_RCC_OSPI2_RELEASE_RESET();
	}

	__HAL_RCC_OSPIIOM_CLK_ENABLE();
	__HAL_RCC_OSPIIOM_CLK_SLEEP_ENABLE();
	__HAL_RCC_OSPIIOM_FORCE_RESET();
	__HAL_RCC_OSPIIOM_RELEASE_RESET();
    /*## Configure the OCTOSPI2 DMA ##*/
    handle_HPDMA3_Channel0.Instance                 = HPDMA3_Channel0;
    handle_HPDMA3_Channel0.Init.Request             = HPDMA_REQUEST_OCTOSPI2;
    handle_HPDMA3_Channel0.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    handle_HPDMA3_Channel0.Init.SrcInc              = DMA_SINC_INCREMENTED;
    handle_HPDMA3_Channel0.Init.DestInc             = DMA_DINC_FIXED;
    handle_HPDMA3_Channel0.Init.SrcDataWidth        = DMA_SRC_DATAWIDTH_BYTE;
    handle_HPDMA3_Channel0.Init.DestDataWidth       = DMA_DEST_DATAWIDTH_BYTE;
    handle_HPDMA3_Channel0.Init.SrcBurstLength      = 1;
    handle_HPDMA3_Channel0.Init.DestBurstLength     = 1;
    handle_HPDMA3_Channel0.Init.Priority            = DMA_HIGH_PRIORITY;
    handle_HPDMA3_Channel0.Init.TransferEventMode   = DMA_TCEM_BLOCK_TRANSFER;

    HAL_DMA_DeInit(&handle_HPDMA3_Channel0);
    /* Associate the DMA handle */
    __HAL_LINKDMA(hospi, hdma, handle_HPDMA3_Channel0);

    /* Initialize the DMA channel */
    HAL_DMA_Init(&handle_HPDMA3_Channel0);

    /* OCTOSPI2 interrupt Init */
    HAL_NVIC_SetPriority(OCTOSPI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI2_IRQn);

    /* HPDMA3 interrupt Init */
    HAL_NVIC_SetPriority(HPDMA3_Channel0_IRQn, 0x00, 0);
    HAL_NVIC_EnableIRQ(HPDMA3_Channel0_IRQn);

  /* USER CODE BEGIN OCTOSPI2_MspInit 1 */

  /* USER CODE END OCTOSPI2_MspInit 1 */
  }

}

void HAL_OSPI_MspPostInit(OSPI_HandleTypeDef* hospi)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* USER CODE BEGIN OSPI_MspPostInit 0 */

	/* USER CODE END OSPI_MspPostInit 0 */
	if(OCTOSPI2 == hospi->Instance)
	{
		/* Acquire GPIOD0 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(0)))
		{
			Error_Handler();
		}
		/* Acquire GPIOD3 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(3)))
		{
			Error_Handler();
		}
		/* Acquire GPIOD4 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(4)))
		{
			Error_Handler();
		}
		/* Acquire GPIOD5 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(5)))
		{
			Error_Handler();
		}
		/* Acquire GPIOD6 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(6)))
		{
			Error_Handler();
		}
		/* Acquire GPIOD7 using Resource manager */
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(7)))
		{
			Error_Handler();
		}
		/* Enable GPIOs power supplies */
		if (RESMGR_STATUS_ACCESS_OK == ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(93)))
		{
			__HAL_RCC_GPIOD_CLK_ENABLE();
		}


	    /**OCTOSPI2 GPIO Configuration
	    PD0     ------> OCTOSPIM_P1_CLK
	    PD4     ------> OCTOSPIM_P1_IO0
	    PD5     ------> OCTOSPIM_P1_IO1
	    PD6     ------> OCTOSPIM_P1_IO2
	    PD7     ------> OCTOSPIM_P1_IO3
	    PD3     ------> OCTOSPIM_P1_NCS
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    if (IS_DEVELOPER_BOOT_MODE())
	    {
	    	HAL_PWREx_EnableSupply(PWR_PVM_VDDIO3);
	    }
	}
}

/**
* @brief OSPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hospi: OSPI handle pointer
* @retval None
*/
void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* hospi)
{
  if(hospi->Instance == OCTOSPI2)
  {
  /* USER CODE BEGIN OCTOSPI2_MspDeInit 0 */

  /* USER CODE END OCTOSPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OSPI2_CLK_DISABLE();

    /**OCTOSPI2 GPIO Configuration
    PD0     ------> OCTOSPIM_P1_CLK
    PD4     ------> OCTOSPIM_P1_IO0
    PD5     ------> OCTOSPIM_P1_IO1
    PD6     ------> OCTOSPIM_P1_IO2
    PD7     ------> OCTOSPIM_P1_IO3
    PD3     ------> OCTOSPIM_P1_NCS
    */

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 |
    		GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

	/* Acquire GPIOD0 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(0)))
	{
		Error_Handler();
	}
	/* Acquire GPIOD3 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(3)))
	{
		Error_Handler();
	}
	/* Acquire GPIOD4 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(4)))
	{
		Error_Handler();
	}
	/* Acquire GPIOD5 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(5)))
	{
		Error_Handler();
	}
	/* Acquire GPIOD6 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(6)))
	{
		Error_Handler();
	}
	/* Acquire GPIOD7 using Resource manager */
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOD, RESMGR_GPIO_PIN(7)))
	{
		Error_Handler();
	}

    /* OCTOSPI2 DMA DeInit */
    HAL_DMA_DeInit(hospi->hdma);
    /* OCTOSPI2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(OCTOSPI2_IRQn);

	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_OCTOSPI2_ID))
	{
		Error_Handler();
	}
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_OCTOSPIM_ID))
	{
		Error_Handler();
	}
	if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(111)))
	{
		Error_Handler();
	}
  /* USER CODE BEGIN OCTOSPI2_MspDeInit 1 */

  /* USER CODE END OCTOSPI2_MspDeInit 1 */
  }

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
* This function releases the hardware resources used in this example
* @param hospi: TIM handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (TIM6 == htim->Instance)
	{
	    /* Disable TIM6 clock */
	    __HAL_RCC_TIM6_CLK_DISABLE();
		if (RESMGR_STATUS_ACCESS_OK != ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM6_ID))
		{
			Error_Handler();
		}
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

