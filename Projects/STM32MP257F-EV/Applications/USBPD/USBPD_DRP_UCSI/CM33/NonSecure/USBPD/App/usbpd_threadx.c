/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"
#include "usbpd_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_azure_rtos_config.h"
#include "usbpd.h"
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
TX_THREAD ThreadUsbpd;

static TX_EVENT_FLAGS_GROUP * tx_EventFlag;
static TX_BYTE_POOL *tx_system_pool;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void Thread_Usbpd_Entry(ULONG thread_input);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  USBPD ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT ThreadX_Usbpd_Init(TX_BYTE_POOL* tx_pool, TX_EVENT_FLAGS_GROUP *EventFlag)
{
  UINT ret = TX_SUCCESS;

  tx_system_pool = tx_pool;
  tx_EventFlag = EventFlag;

  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
#if (USE_STATIC_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for ThreadUsbpd.  */
  if (tx_byte_allocate(tx_system_pool, (VOID **) &pointer,
		  	  	  	   THREAD_USBPD_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	return TX_POOL_ERROR;
  }

  /* Create ThreadUsbpd.  */
  if (tx_thread_create(&ThreadUsbpd, "Thread Usbpd init", Thread_Usbpd_Entry, 0,
                       pointer, THREAD_USBPD_STACK_SIZE,
                       THREAD_USBPD_PRIO, THREAD_USBPD_PREEMPTION_THRESHOLD,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
	return TX_THREAD_ERROR;
  }

#endif
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  Function implementing the ThreadOpenamp thread.
  * @param  thread_input: Not used
  * @retval None
  */
static void Thread_Usbpd_Entry(ULONG thread_input)
{
  (void) thread_input;
  UINT ret = 0;

if(!IS_DEVELOPER_BOOT_MODE())
  {
     ULONG   actual_flags = 0;
     if ((ret = tx_event_flags_get(tx_EventFlag, THREAD_OPENAMP_INIT_DONE_EVT, TX_OR_CLEAR,
             &actual_flags, TX_WAIT_FOREVER)) != TX_SUCCESS)
     {
        Error_Handler();
     }
  }

  /* OpenAMP is now Synchronized */

  /* Initialize USBPD stack, start related threads */
  ret = MX_USBPD_Init(tx_system_pool);

  while (1)
  {
    /* USBPD initialized. Put this thread to sleep. */
    tx_thread_sleep(2000U);
  }
}

/* USER CODE END 1 */
