/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX Openamp header file
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OPENAMP_THREADX_H
#define __OPENAMP_THREADX_H

#include "openamp.h"
#include "openamp_log.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
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
 /* Exported functions prototypes ---------------------------------------------*/
 UINT ThreadX_Openamp_Init(TX_BYTE_POOL* tx_pool,TX_EVENT_FLAGS_GROUP *EventFlag);

 /* USER CODE BEGIN EFP */

 /* USER CODE END EFP */

 /* Private defines -----------------------------------------------------------*/
 /* USER CODE BEGIN PD */
 #define THREAD_OPENAMP_PRIO                          5
 #define THREAD_OPENAMP_PREEMPTION_THRESHOLD          THREAD_OPENAMP_PRIO

/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __OPENAMP_THREADX_H__ */
