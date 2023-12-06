/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file         stm32mp2xx_hal_msp.c
 * @brief        This file provides code for the MSP Initialization
 *               and de-Initialization codes.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "res_mgr.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */
  /* Acquire TIM6 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM6_ID) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* USER CODE END MspInit 0 */
}

/**
 * DeInitializes the Global MSP.
 */
void HAL_MspDeInit(void)
{
  /* USER CODE BEGIN MspInit 0 */
  /* Release TIM6 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_TIM6_ID) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* USER CODE END MspInit 0 */
}

/**
 * @brief  Initializes the ETH MSP.
 * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @retval None
 */

void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Acquire ETH1 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_ETH1_ID) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOA11 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(11))  != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOA13 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(13)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOA14 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(14)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOA15 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(15)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOC0 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(0)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOC1 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(1)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOC2 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(2)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOF0 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(0)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOF1 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(1)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOF2 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(2)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOH9 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(9)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOH10 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(10)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOH11 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(11)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOH12 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(12)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOH13 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(13)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Acquire GPIOJ9 using Resource manager */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_GPIOJ, RESMGR_GPIO_PIN(9)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Enable Ethernet clocks */
  __HAL_RCC_ETH1_CLK_ENABLE();
  __HAL_RCC_ETH1MAC_CLK_ENABLE();
  __HAL_RCC_ETH1TX_CLK_ENABLE();
  __HAL_RCC_ETH1RX_CLK_ENABLE();
  /* Select Ethernet 125MHz internal clock from RCC */
  HAL_SYSCFG_ETH1ClockSelect(SYSCFG_ETH_RCC_CLK);

  /* Enable GPIOA clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(90)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  /* Enable GPIOC clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(92)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  /* Enable GPIOF clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(95)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOF_CLK_ENABLE();
  }
  /* Enable GPIOH clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(97)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOH_CLK_ENABLE();
  }
  /* Enable GPIOJ clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(99)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOJ_CLK_ENABLE();
  }

  /* ETH_RGMII_RX_CTL, ETH_RGMII_TX_CTL, ETH_RGMII_RX_CLK, ETH_RGMII_TXD0 */
  GPIO_InitStructure.Pin =  GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL ;
  GPIO_InitStructure.Alternate = GPIO_AF10_ETH1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* ETH_RGMII_TXD1, ETH_RGMII_RXD1 */
  GPIO_InitStructure.Alternate = GPIO_AF10_ETH1;
  GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ETH_RGMII_GTX_CLK */
  GPIO_InitStructure.Alternate = GPIO_AF12_ETH1;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ETH_RGMII_CLK125, ETH_RGMII_TXD2, ETH_RGMII_TXD3, ETH_RGMII_RXD2, ETH_RGMII_RXD3 */
  GPIO_InitStructure.Alternate = GPIO_AF10_ETH1;
  GPIO_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* ETH_RGMII_RXD0 */
  GPIO_InitStructure.Alternate = GPIO_AF10_ETH1;
  GPIO_InitStructure.Pin = GPIO_PIN_1;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* ETH_MDC */
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* ETH_MDIO */
  GPIO_InitStructure.Pin = GPIO_PIN_2;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

  /* PHY Reset */
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL ;
  GPIO_InitStructure.Pin = GPIO_PIN_9;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStructure);
  HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_9, GPIO_PIN_RESET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_9, GPIO_PIN_SET);
  HAL_Delay(80);

  /* Enable the Ethernet global Interrupt */
  HAL_NVIC_SetPriority(ETH1_SBD_IRQn, 0x7, 0);
  HAL_NVIC_EnableIRQ(ETH1_SBD_IRQn);

  /* Apply GPIO delay & retiming parameters */
  GPIOA->DELAYRL = 0x00000000;
  GPIOA->DELAYRH = 0x00000000;
  GPIOA->ADVCFGRL = 0x00000000;
  GPIOA->ADVCFGRH = 0xA0A0A000;

  GPIOC->DELAYRL = 0x00000008;
  GPIOC->DELAYRH = 0x00000000;
  GPIOC->ADVCFGRL = 0x00000AA0;
  GPIOC->ADVCFGRH = 0x00000000;

  GPIOF->DELAYRL = 0x00000000;
  GPIOF->DELAYRH = 0x00000000;
  GPIOF->ADVCFGRL = 0x000000A0;
  GPIOF->ADVCFGRH = 0x00000000;

  GPIOH->DELAYRL = 0x00000000;
  GPIOH->DELAYRH = 0x00000000;
  GPIOH->ADVCFGRL = 0x00000000;
  GPIOH->ADVCFGRH = 0x00AAAA00;
}

/**
 * @brief  DeInitializes ETH MSP.
 * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
 *         the configuration information for ETHERNET module
 * @retval None
 */
void HAL_ETH_MspDeInit(ETH_HandleTypeDef *heth)
{
  /* Disable GPIOA clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(90)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOA_CLK_DISABLE();
  }
  /* Disable GPIOC clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(92)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOC_CLK_DISABLE();
  }
  /* Disable GPIOF clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(95)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOF_CLK_DISABLE();
  }
  /* Disable GPIOH clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(97)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOH_CLK_DISABLE();
  }
  /* Disable GPIOJ clock */
  if (ResMgr_Request(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(99)) == RESMGR_STATUS_ACCESS_OK)
  {
    __HAL_RCC_GPIOJ_CLK_DISABLE();
  }

  /* Disable Ethernet clocks */
  __HAL_RCC_ETH1_CLK_DISABLE();
  __HAL_RCC_ETH1MAC_CLK_DISABLE();
  __HAL_RCC_ETH1TX_CLK_DISABLE();
  __HAL_RCC_ETH1RX_CLK_DISABLE();

  /* Disable IRQ */
  HAL_NVIC_DisableIRQ(ETH1_SBD_IRQn);

  /* Release GPIOA clock */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(90)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOC clock */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(92)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOF clock */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(95)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH clock */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(97)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOJ clock */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_RCC, RESMGR_RCC_RESOURCE(99)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release ETH1 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIFSC, STM32MP25_RIFSC_ETH1_ID) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOA11 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(11))  != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOA13 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(13)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOA14 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(14)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOA15 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOA, RESMGR_GPIO_PIN(15)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOC0 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(0)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOC1 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(1)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOC2 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOC, RESMGR_GPIO_PIN(2)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOF0 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(0)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOF1 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(1)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOF2 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOF, RESMGR_GPIO_PIN(2)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH9 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(9)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH10 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(10)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH11 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(11)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH12 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(12)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOH13 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOH, RESMGR_GPIO_PIN(13)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
  /* Release GPIOJ9 using Resource manager */
  if (ResMgr_Release(RESMGR_RESOURCE_RIF_GPIOJ, RESMGR_GPIO_PIN(9)) != RESMGR_STATUS_ACCESS_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

