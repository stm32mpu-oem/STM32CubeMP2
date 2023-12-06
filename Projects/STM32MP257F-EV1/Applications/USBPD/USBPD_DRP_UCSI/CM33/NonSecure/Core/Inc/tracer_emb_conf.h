/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tracer_emb_conf.h
  * @author  MCD Application Team
  * @brief   This file contains the Trace HW related defines.
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
/* USER CODE END Header */

#ifndef TRACER_EMB_CONF_H
#define TRACER_EMB_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_ll_bus.h"
#include "stm32mp2xx_ll_dma.h"
#include "stm32mp2xx_ll_gpio.h"
#include "stm32mp2xx_ll_rcc.h"
#include "stm32mp2xx_ll_usart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* -----------------------------------------------------------------------------
      Definitions for TRACE feature
-------------------------------------------------------------------------------*/
void ResMgr_LL_RCC_HPDMA3_EnableClock();
void ResMgr_LL_RCC_GPIOG_EnableClock();
#define TRACER_EMB_BAUDRATE                          921600UL

#define TRACER_EMB_DMA_MODE                          1UL
#define TRACER_EMB_IT_MODE                           0UL

#define TRACER_EMB_BUFFER_SIZE                       8192UL

/* -----------------------------------------------------------------------------
      Definitions for TRACE Hw information
-------------------------------------------------------------------------------*/

#define TRACER_EMB_IS_INSTANCE_LPUART_TYPE           0UL /* set to 0UL if USART is used */

#define TRACER_EMB_USART_INSTANCE                    UART5

#define TRACER_EMB_TX_GPIO                           GPIOG
#define TRACER_EMB_TX_PIN                            LL_GPIO_PIN_9
#define TRACER_EMB_TX_AF                             LL_GPIO_AF_5
#define TRACER_EMB_TX_GPIO_ENABLE_CLOCK()            ResMgr_LL_RCC_GPIOG_EnableClock()
#define TRACER_EMB_RX_GPIO                           GPIOG
#define TRACER_EMB_RX_PIN                            LL_GPIO_PIN_10
#define TRACER_EMB_RX_AF                             LL_GPIO_AF_5
#define TRACER_EMB_RX_GPIO_ENABLE_CLOCK()            ResMgr_LL_RCC_GPIOG_EnableClock()
#define TRACER_EMB_ENABLE_CLK_USART()                LL_RCC_UART5_EnableClock()
#define TRACER_EMB_DISABLE_CLK_USART()               LL_RCC_UART5_DisableClock()
#define TRACER_EMB_SET_CLK_SOURCE_USART()            /* No need for clock source selection in case of USART5 */
#define TRACER_EMB_USART_IRQ                         UART5_IRQn
#define TRACER_EMB_USART_IRQHANDLER                  UART5_IRQHandler
#define TRACER_EMB_TX_AF_FUNCTION                    LL_GPIO_SetAFPin_0_7
#define TRACER_EMB_RX_AF_FUNCTION                    LL_GPIO_SetAFPin_0_7

#define TRACER_EMB_DMA_INSTANCE                      HPDMA3
#define TRACER_EMB_ENABLE_CLK_DMA()                  ResMgr_LL_RCC_HPDMA3_EnableClock()

#define TRACER_EMB_TX_DMA_REQUEST                    LL_HPDMA_REQUEST_UART5_TX
#define TRACER_EMB_TX_DMA_CHANNEL                    LL_DMA_CHANNEL_0
#define TRACER_EMB_ENABLECHANNEL                     LL_DMA_ResumeChannel
#define TRACER_EMB_DISABLECHANNEL                    LL_DMA_SuspendChannel
#define TRACER_EMB_TX_DMA_IRQ                        HPDMA3_Channel0_IRQn
#define TRACER_EMB_TX_DMA_IRQHANDLER                 HPDMA3_Channel0_IRQHandler
#define TRACER_EMB_TX_DMA_ACTIVE_FLAG(_DMA_)         LL_DMA_IsActiveFlag_TC(_DMA_, TRACER_EMB_TX_DMA_CHANNEL)
#define TRACER_EMB_TX_DMA_CLEAR_FLAG(_DMA_)          LL_DMA_ClearFlag_TC(_DMA_, TRACER_EMB_TX_DMA_CHANNEL)

#ifdef __cplusplus
}
#endif

#endif /* TRACER_EMB_CONF_H */
