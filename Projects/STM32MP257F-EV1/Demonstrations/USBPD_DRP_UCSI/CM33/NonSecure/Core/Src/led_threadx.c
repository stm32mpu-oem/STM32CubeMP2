/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    led_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX LED file
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

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"
#include "led_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_azure_rtos_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TX_THREAD ThreadLed;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void ThreadX_Led_Entry(ULONG thread_input);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */

UINT ThreadX_Led_Init(TX_BYTE_POOL* tx_pool)
{
  UINT ret = TX_SUCCESS;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
#if (USE_STATIC_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for ThreadLed.  */
  if (tx_byte_allocate(tx_pool, (VOID **) &pointer,
		  	  	       THREAD_LED_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	return TX_POOL_ERROR;
  }

  /* Create ThreadLed.  */
  if (tx_thread_create(&ThreadLed, "Thread Led", ThreadX_Led_Entry, 0,
                       pointer, THREAD_LED_STACK_SIZE,
                       THREAD_LED_PRIO, THREAD_LED_PREEMPTION_THRESHOLD,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
	return TX_THREAD_ERROR;
  }

#endif
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  Function implementing the Led blinking thread.
  *
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadX_Led_Entry(ULONG thread_input)
{
  /* Infinite loop */
  while(1)
  {
    BSP_LED_On(LED_ORANGE);
    tx_thread_sleep(300);
    BSP_LED_Off(LED_ORANGE);
    tx_thread_sleep(300);
  }
}

/* USER CODE END 1 */
