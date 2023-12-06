/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX openAMP file
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
#include "openamp_threadx.h"
#include "rsc_table.h"
#include "metal/sys.h"
#include "metal/device.h"

#include "app_azure_rtos_config.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
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

#define SHM_DEVICE_NAME         "STM32_SHM"

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

static TX_THREAD ThreadOpenamp;
static TX_EVENT_FLAGS_GROUP * tx_EventFlag;
static TX_BYTE_POOL *tx_system_pool;


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

static void ThreadX_Openamp_Entry(ULONG thread_input);

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT ThreadX_Openamp_Init(TX_BYTE_POOL* tx_pool, TX_EVENT_FLAGS_GROUP *EventFlag)
{
  UINT ret = TX_SUCCESS;

  tx_system_pool = tx_pool;
  tx_EventFlag = EventFlag;
  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
#if (USE_STATIC_ALLOCATION == 1)
  CHAR *pointer;

  /* Allocate the stack for ThreadOpenamp.  */
  if (tx_byte_allocate(tx_pool, (VOID **) &pointer, THREAD_OPENAMP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
	return TX_POOL_ERROR;
  }

  /* Create ThreadOpenamp.  */
  if (tx_thread_create(&ThreadOpenamp, "Thread OpenAMP", ThreadX_Openamp_Entry, 0,
                       pointer, THREAD_OPENAMP_STACK_SIZE,
                       THREAD_OPENAMP_PRIO, THREAD_OPENAMP_PREEMPTION_THRESHOLD,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
	return TX_THREAD_ERROR;
  }

  #endif
  /* USER CODE END App_ThreadX_Init */

  return ret;
}

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT ThreadX_Openamp_Deinit()
{
  /* USER CODE BEGIN PRE_OPENAMP_DEINIT */

  /* USER CODE END PRE_OPENAMP_DEINIT */

  tx_thread_delete(&ThreadOpenamp);

  OPENAMP_DeInit();

  /* USER CODE BEGIN POST_OPENAMP_DEINIT */

  /* USER CODE END POST_OPENAMP_DEINIT */

  return 0;
}

void * metal_threadx_allocate_memory(unsigned int size)
{
  CHAR *pointer;

  if (tx_byte_allocate(tx_system_pool, (VOID **) &pointer, size, TX_NO_WAIT) != TX_SUCCESS)
  {
	return NULL;
  }

  return pointer;
}

void  metal_threadx_free_memory(void *ptr)
{
  tx_byte_release(ptr);
}

/**
  * @brief  Function implementing the ThreadOpenamp thread.
  * @param  thread_input: Not used
  * @retval None
  */
static void ThreadX_Openamp_Entry(ULONG thread_input)
{
  (void) thread_input;

  /* Libmetal Initilalization */
  if(MX_OPENAMP_Init(RPMSG_REMOTE, NULL))
  {
    Error_Handler();
  }

  if (tx_event_flags_set(tx_EventFlag, THREAD_OPENAMP_INIT_DONE_EVT, TX_OR) != TX_SUCCESS)
  {
    Error_Handler();
  }

  /* OpenAMP Initialized */
  while (1)
  {
    OPENAMP_check_for_message();
  }
}

/* USER CODE END 1 */
