/**
  ******************************************************************************
  * @file  : usbpd_ucsi_if.c
  * @brief : Source file for interfacing the usbpd_ucsi to hardware.
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
#include "usbpd_ucsi.h"
#include "ppm.h"
#include "usbpd_ucsi_if.h"

#include "app_threadx.h"
#include "main.h"
#include "usbpd_os_port.h"
#if defined(_TRACE)
#include "usbpd_trace.h"
#include "string.h"
#include "stdio.h"
#endif /* _TRACE */

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief UCSI states
  */
typedef enum
{
  UCSI_STATE_INIT,

  /* Errors */
  UCSI_ERROR_SEQ_RECEIVE,
  UCSI_ERROR_SEQ_TRANSMIT,
  UCSI_ERROR_SEQ_UNKOWN,
  UCSI_ERROR_SEQ_TXCOUNT,
} UCSI_enum;

/**
  * @brief UCSI interface handle
  */
typedef struct
{
  void (*ReceiveCommandCb)(uint8_t, uint8_t *);      /*!< function used to return the UCSI command received by OPM */
} UCSI_IF_HandleTypeDef;

/**
  * @brief UCSI user handle
  */
typedef struct
{
  UCSI_enum       Error;
  uint8_t         Direction;
  UCSI_REG_t      Register;
  UCSI_enum       State;
  uint8_t        *PtrBuffer;
  uint8_t         DataSize;
} UCSI_USER_HandleTypeDef;

/* Private define ------------------------------------------------------------*/
/******************************************************************************
   Alert IRQ
  *****************************************************************************/
#define ALERT_IRQ_NBR          (0U)         /* Virtual INTC IRQ number        */

/******************************************************************************
   I2C configuration
  *****************************************************************************/
#define I2C_ADDRESS_UCSI       (0x35U)      /* Used for UCSI commands         */
/******************************************************************************/

#if defined(_TRACE)
/* Definition of debug levels */
#define UCSI_DEBUG_NONE        (0U)
#define UCSI_DEBUG_LEVEL_0     (1U << 0)
#define UCSI_DEBUG_LEVEL_1     (1U << 1)
#define UCSI_DEBUG_LEVEL_2     (1U << 2)
#endif /* _TRACE */

#if defined(USBPD_THREADX)
#define OS_I2CTASK_PRIORITY    (2U)
#elif defined(_RTOS)
#define OS_I2CTASK_PRIORITY    (osPriorityHigh)
#endif /* USBPD_THREADX */

#define OS_I2CTASK_STACK_SIZE  (240U)

/* Private macro -------------------------------------------------------------*/
/* Free the mutex to indicate the operation complete */
#if defined(USBPD_THREADX)
#define WAIT_OPERATION_COMPLETE()                                                                       \
  do                                                                                                    \
  {                                                                                                     \
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Wait semaphore last operation completed");             \
    /* Wait that the UCSI PPM command is complete */                                                    \
    tx_semaphore_get(&sem_ucsi_cmd_cplt, TX_WAIT_FOREVER);                                              \
  } while(0);

#define TRIG_OPERATION()                                                                                \
  do                                                                                                    \
  {                                                                                                     \
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Release semaphore sem_i2c_cplt_id");                   \
    (void)tx_semaphore_put(&sem_ucsi_i2c_cplt);                                                         \
    WAIT_OPERATION_COMPLETE();                                                                          \
  } while(0);


#elif defined(_RTOS)
#define TRIG_OPERATION()                                                                                \
  do                                                                                                    \
  {                                                                                                     \
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Release semaphore sem_i2c_cplt_id");                   \
    (void)osSemaphoreRelease(sem_i2c_cplt_id);                                                          \
  } while(0);
#else
#define TRIG_OPERATION()
#endif /* USBPD_THREADX */

/* Private variables ---------------------------------------------------------*/
#if defined(_TRACE)
/* UCSI debug verbose level */
uint8_t UCSI_DebugLevel = /* UCSI_DEBUG_LEVEL_2 | */ UCSI_DEBUG_LEVEL_1 | UCSI_DEBUG_LEVEL_0 | UCSI_DEBUG_NONE;
#endif /* _TRACE */

/* UCSI handle used for UCSI communication*/
static UCSI_USER_HandleTypeDef UCSI_Handles;

/* Mutex definition */
#if defined(USBPD_THREADX)
TX_SEMAPHORE sem_ucsi_i2c_cplt;
TX_SEMAPHORE sem_ucsi_cmd_cplt;
#elif defined(_RTOS)
osSemaphoreDef(sem_ucsi_i2c_cplt);
osSemaphoreId sem_i2c_cplt_id;
#endif /* USBPD_THREADX */

/* ThreadX memory pool and event flags */
#if defined(USBPD_THREADX)
static TX_BYTE_POOL         *USBPD_memory_pool;
extern TX_EVENT_FLAGS_GROUP        EventFlag;
#endif /* USBPD_THREADX */

#if defined(_RTOS) || defined(USBPD_THREADX)
OS_TASK_ID I2CTaskThread;
#endif /* _RTOS || USBPD_THREADX */

/* Virt_I2C & Virt_INTC handle */
static VIRT_I2C_HandleTypeDef  hi2c;
static VIRT_INTC_HandleTypeDef hintc;

/* UCSI IF handle */
UCSI_IF_HandleTypeDef UCSI_IF_Handle;

/* Local variable to store port status */
uint8_t Register;
uint8_t I2C_Direction;
uint8_t *PtrUCSI_Data;

#if defined(_TRACE)
/* Debug trace */
#define UCSI_IF_PPM_DEBUG_TRACE(_LEVEL_, ...)                                                             \
  do                                                                                                      \
  {                                                                                                       \
    if ((UCSI_DebugLevel & (_LEVEL_)) != 0U)                                                              \
    {                                                                                                     \
      char _str[70U];                                                                                     \
      (void)snprintf(_str, 70U, __VA_ARGS__);                                                             \
        USBPD_TRACE_Add(USBPD_TRACE_DEBUG, USBPD_PORT_0, 0U, (uint8_t*)_str, strlen(_str));               \
      }                                                                                                   \
  } while(0);

/* Simple debug trace */
#define UCSI_IF_PPM_DEBUG_TRACE_NO_ARG(_LEVEL_, __MESSAGE__)                                              \
  do                                                                                                      \
  {                                                                                                       \
    if ((UCSI_DebugLevel & (_LEVEL_)) != 0U)                                                              \
    {                                                                                                     \
      USBPD_TRACE_Add(USBPD_TRACE_DEBUG, USBPD_PORT_0, 0U, (uint8_t*)(__MESSAGE__), strlen(__MESSAGE__)); \
    }                                                                                                     \
  } while(0);

/* UCSI trace */
#define UCSI_IF_PPM_TRACE(_LEVEL_, _ADDR_, _ID_, _PTR_DATA_, _SIZE_)                                      \
  do                                                                                                      \
  {                                                                                                       \
    if ((UCSI_DebugLevel & (_LEVEL_)) != 0U)                                                              \
    {                                                                                                     \
      USBPD_TRACE_Add(USBPD_TRACE_UCSI, (uint8_t)_ADDR_, (uint8_t)_ID_, _PTR_DATA_, _SIZE_);              \
    }                                                                                                     \
  } while(0);
#else
#define UCSI_IF_PPM_DEBUG_TRACE(_LEVEL_, ...)
#define UCSI_IF_PPM_DEBUG_TRACE_NO_ARG(_LEVEL_, __MESSAGE__)
#define UCSI_IF_PPM_TRACE(_LEVEL_, _ADDR_, _ID_, _PTR_DATA_, _SIZE_)
#endif /* _TRACE */

/* Private function prototypes -----------------------------------------------*/
#if defined(USBPD_THREADX)
static USBPD_UCSI_Status_t  UCSI_I2C_Init(void (*ReceiveCommandCb)(uint8_t, uint8_t *), VOID *MemoryPtr);
#else
static USBPD_UCSI_Status_t  UCSI_I2C_Init(void (*ReceiveCommandCb)(uint8_t, uint8_t *));
#endif /* USBPD_THREADX */
static void                 UCSI_I2C_DeInit(void);
static void                 UCSI_AlertInit(void);
static void                 UCSI_AlertON(void);
static void                 UCSI_AlertOFF(void);
static USBPD_StatusTypeDef  USBPD_UCSI_PPM_ListenPort(uint8_t *pDirection, uint8_t *pRegister, uint8_t **ppData);
DEF_TASK_FUNCTION(          USBPD_UCSI_PPM_TaskListenI2C);
static uint8_t              *UCSI_GetDataSizeRegisterPtr(UCSI_REG_t reg, uint8_t *PtrDataSize);
static void                 VIRT_I2C_RxCpltCallback(VIRT_I2C_HandleTypeDef *hi2c, size_t len);

/**
  * @brief  UCSI Driver definition.
  *
  * list all the driver interfaces used by the UCSI application.
  */
const USBPD_UCSI_Driver_t USBPD_UcsiDriver =
{
  UCSI_I2C_Init,
  UCSI_AlertON,
  UCSI_AlertOFF,
};

/**
  * @brief  Disable I2C used for UCSI
  * @param  None
  * @retval None
  */
static void UCSI_I2C_DeInit(void)
{
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual I2C DeInit");
  if (VIRT_I2C_OK != VIRT_I2C_DeInit(&hi2c))
  {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_I2C_DeInit failed");
    /* Error */
    Error_Handler();
  }
}

/**
  * @brief  Initialize UCSI
  * @param  *ReceiveCommandCb Pointer of reception function callback
  * @retval UCSI status
  */
#if defined(USBPD_THREADX)
static USBPD_UCSI_Status_t UCSI_I2C_Init(void (*ReceiveCommandCb)(uint8_t, uint8_t *), VOID *MemoryPtr)
#else
static USBPD_UCSI_Status_t UCSI_I2C_Init(void (*ReceiveCommandCb)(uint8_t, uint8_t *))
#endif /* USBPD_THREADX */
{
  /* Init Alert pin */
  UCSI_AlertInit();

  /*
   * Add a delay to ensure that the interrupt controller is initialized on
   * remote side before the rpmsg i2c bus
   */
  OS_DELAY(10);

  /* Initialize VIRT I2C */
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual I2C OpenAMP-rpmsg channel creation.");
  if (VIRT_I2C_Init(&hi2c) != VIRT_I2C_OK)
  {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_I2C_Init failed.");
    Error_Handler();
  }

  /* Register callback for message reception by channels */
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual I2C OpenAMP-rpmsg callback registering.");
  if(VIRT_I2C_RegisterCallback(&hi2c, VIRT_I2C_RXCPLT_CB_ID, VIRT_I2C_RxCpltCallback) != VIRT_I2C_OK)
  {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_I2C_RegisterCallback failed.");
    Error_Handler();
  }

  /* Start the listen I2C task for UCSI*/
#if defined(USBPD_THREADX)
  if (tx_semaphore_create(&sem_ucsi_cmd_cplt, "sem_ucsi_cmd_cplt" , 0U) != TX_SUCCESS)
  {
    /* Error occurred creating a Semaphore */
    return USBPD_UCSI_ERROR;
  }

  if (tx_semaphore_create(&sem_ucsi_i2c_cplt, "sem_ucsi_i2c_cplt" , 1U) != TX_SUCCESS)
  {
    /* Error occurred creating a Semaphore */
    return USBPD_UCSI_ERROR;
  }

  /* Take the mutex_I2C_CPLT semaphores */
  tx_semaphore_get(&sem_ucsi_i2c_cplt, TX_WAIT_FOREVER);

#elif defined(_RTOS)
  sem_i2c_cplt_id = osSemaphoreCreate(osSemaphore(sem_ucsi_i2c_cplt), 1U);
  if (sem_i2c_cplt_id == 0)
  {
    /* Error occurred creating a Semaphore */
    return USBPD_UCSI_ERROR;
  }

  /* Take the mutex_I2C_CPLT semaphores */
  (void)osSemaphoreWait(sem_i2c_cplt_id, osWaitForever);

#else
#warning "NRTOS Version not implemented"
#endif /* USBPD_THREADX */

#if defined(_RTOS) || defined(USBPD_THREADX)
  /* PPM listen I2C task creation */
  OS_INIT();
  OS_DEFINE_TASK(I2CTask, USBPD_UCSI_PPM_TaskListenI2C, OS_I2CTASK_PRIORITY, OS_I2CTASK_STACK_SIZE, NULL);
  OS_CREATE_TASK(I2CTaskThread, I2CTask, USBPD_UCSI_PPM_TaskListenI2C,
                 OS_I2CTASK_PRIORITY, OS_I2CTASK_STACK_SIZE, NULL);
#else
#warning "NRTOS Version not implemented"
#endif /* _RTOS || USBPD_THREADX */

  UCSI_IF_Handle.ReceiveCommandCb = ReceiveCommandCb;

  (void)_retr; /* To avoid gcc/g++ warnings */
  return USBPD_UCSI_OK;

#if defined(_RTOS) || defined(USBPD_THREADX)
error:
  Error_Handler();
  return USBPD_UCSI_ERROR;
#endif /* _RTOS || USBPD_THREADX */
}

/**
  * @brief  ALERT ON
  * @param  None
  * @retval None
  */
static void UCSI_AlertON(void)
{
  /* Set alert signal */
  UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_1, I2C_ADDRESS_UCSI, UCSI_TRACE_ALERT_ON, NULL, 0U);
  if (VIRT_INTC_OK != VIRT_INTC_sendIRQ(&hintc, ALERT_IRQ_NBR))
  {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_1, "VIRT_INTC_sendIRQ failed");
  }
}

/**
  * @brief  ALERT OFF
  * @param  None
  * @retval None
  */
static void UCSI_AlertOFF(void)
{
  /* Reset alert signal */
  UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_1, I2C_ADDRESS_UCSI, UCSI_TRACE_ALERT_OFF, NULL, 0U);
}

DEF_TASK_FUNCTION(USBPD_UCSI_PPM_TaskListenI2C)
{
  while (1)
  {
    if (USBPD_OK != USBPD_UCSI_PPM_ListenPort(&I2C_Direction, &Register, &PtrUCSI_Data))
    {
      /* Error to handle */
    }
    else
    {
      if (I2C_DIRECTION_TRANSMIT == I2C_Direction)
      {
        UCSI_IF_Handle.ReceiveCommandCb(Register, PtrUCSI_Data);
      }
    }
    tx_semaphore_put(&sem_ucsi_cmd_cplt);
  }
}

/**
  * @brief  UCSI Get the register id
  * @param  *pDirection
  * @param  *pRegister
  * @param  **ppData
  * @retval USBPD status
  */
static USBPD_StatusTypeDef USBPD_UCSI_PPM_ListenPort(uint8_t *pDirection, uint8_t *pRegister, uint8_t **ppData)
{
  USBPD_StatusTypeDef _retr = USBPD_OK;
  UCSI_USER_HandleTypeDef *ptr_port = NULL;


  /* Wait and check the I2C operation complete */
#if defined(USBPD_THREADX)
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Wait for semaphore sem_i2c_cplt_id");
  if (tx_semaphore_get(&sem_ucsi_i2c_cplt, TX_WAIT_FOREVER) != TX_SUCCESS)
#elif defined(_RTOS)
  if (osSemaphoreWait(sem_i2c_cplt_id, osWaitForever) != 0)
#else
#warning "NRTOS Version not implemented"
#endif /* USBPD_THREADX */
  {
    UCSI_IF_PPM_DEBUG_TRACE_NO_ARG(UCSI_DEBUG_LEVEL_2, "tx_semaphore_get failed");
    _retr = USBPD_FAIL;
  }

  if (USBPD_FAIL != _retr)
  {
    ptr_port = &UCSI_Handles;

    if (ptr_port->Error == UCSI_ERROR_SEQ_TRANSMIT)
    {
      /* Error occurred during transmission, reinitialize I2C */
      UCSI_IF_PPM_DEBUG_TRACE_NO_ARG(UCSI_DEBUG_LEVEL_1, "State UCSI_ERROR_SEQ_TRANSMIT: re-init Virt I2C");
      UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_0, I2C_ADDRESS_UCSI, UCSI_TRACE_LISTEN_PORT, NULL, 0U);
      _retr = USBPD_ERROR;
      UCSI_I2C_DeInit();
      if (VIRT_I2C_Init(&hi2c) != VIRT_I2C_OK)
      {
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_1, "VIRT_I2C_Init failed");
        Error_Handler();
      }
      ptr_port->Error = UCSI_STATE_INIT;
    }
    else
    {
      /* No error occurred during transmission */
      *pDirection    = ptr_port->Direction;
      *pRegister     = (uint8_t)ptr_port->Register;
      *ppData        = ptr_port->PtrBuffer;
    }
  }

  /* Reset UCSI handles except buffer and error */
  if (ptr_port != NULL)
  {
    UCSI_IF_PPM_DEBUG_TRACE_NO_ARG(UCSI_DEBUG_LEVEL_2, "USBPD_UCSI_PPM_ListenPort: reset UCSI handles");
    ptr_port->Direction     = 0U;
    ptr_port->Register      = UcsiRegDataStructureUnkown;
    ptr_port->State         = UCSI_STATE_INIT;
  }
  return _retr;
}

/*************************************************************************/
/* VIRT I2C callback implementation                                      */
/*************************************************************************/
static void VIRT_I2C_RxCpltCallback(VIRT_I2C_HandleTypeDef *hi2c, size_t len)
{
  UCSI_USER_HandleTypeDef *ptr_port = &UCSI_Handles;
  uint8_t addr;

  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual I2C request");

  addr = VIRT_I2C_addrFromMsg(hi2c);

  /* If the message was for the right address */
  if (addr == I2C_ADDRESS_UCSI)
  {
    /* Save the transfer direction */
    ptr_port->Direction = (hi2c->msg->addr & I2C_MASTER_READ);

    /* MASTER TO SLAVE --> Slave is reading */
    if (I2C_DIRECTION_TRANSMIT ==  ptr_port->Direction)
    {
      UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Direction MASTER TO SLAVE");

      if (hi2c->msg->len == 0U)
      {
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "ERROR %s: len is null", __func__);
        TRIG_OPERATION();
        return;
      };

      /* Read/copy first received byte */
      UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Copying buf[0] = %#x to ptr_port->Register", hi2c->msg->buf[0])
      ptr_port->Register = hi2c->msg->buf[0];

      /* Get information about how many data to send from first received byte */
      ptr_port->PtrBuffer = UCSI_GetDataSizeRegisterPtr(ptr_port->Register, &ptr_port->DataSize);

      if (ptr_port->PtrBuffer != NULL)
      {
        /* Copy the rest of the payload to the desired register if there is something left to copy */
        if ((hi2c->msg->len - 1U) != 0U)
        {
          UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "memcpy size = %ld", (hi2c->msg->len - 1U));

          memcpy(ptr_port->PtrBuffer, &hi2c->msg->buf[1], (hi2c->msg->len - 1U));

          TRIG_OPERATION();
          /* Acknowledge the received message */
          UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT I2C ACK");
          if (VIRT_I2C_OK != VIRT_I2C_sendACK(hi2c, VIRT_I2C_ACK))
          {
            UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_1, "VIRT I2C ACK failed");
          }
        }
        else
        {
          /* Acknowledge the received message */
          UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT I2C ACK");
          if (VIRT_I2C_OK != VIRT_I2C_sendACK(hi2c, VIRT_I2C_ACK))
          {
            UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_1, "VIRT I2C ACK failed");
          }
        }
      }
      else
      {
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Error ptr_port->PtrBuffer is NULL");

        /* NACK the unknown request */
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT I2C NACK");

        /* Error detected */
        ptr_port->Error = UCSI_ERROR_SEQ_TRANSMIT;
        TRIG_OPERATION();
        if (VIRT_I2C_OK != VIRT_I2C_sendACK(hi2c, VIRT_I2C_NACK))
        {
          UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_1, "VIRT I2C NACK failed");
        }
      }

    }
    /* SLAVE TO MASTER --> Slave is sending */
    else
    {
      UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Direction SLAVE TO MASTER");

      /* Avoid sending more data than asked by the master */
      ptr_port->DataSize = MIN(ptr_port->DataSize, len);

      /* Get information about how many data to send */
      if (ptr_port->PtrBuffer != NULL)
      {
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Sending %d bytes: buff[0..1]=%#x %#x", ptr_port->DataSize, ptr_port->PtrBuffer[0], ptr_port->PtrBuffer[1]);

        if (VIRT_I2C_OK != VIRT_I2C_sendToMaster(hi2c, ptr_port->PtrBuffer, ptr_port->DataSize))
        {
          /* Error detected */
          UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_0, I2C_ADDRESS_UCSI, UCSI_TRACE_ADDRCB_ERROR_TX, NULL, 0U);
          ptr_port->Error = UCSI_ERROR_SEQ_TRANSMIT;
          UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_I2C_sendToMaster failed. datasize=%d", ptr_port->DataSize);
          TRIG_OPERATION();
        }
        /* Transfer complete, no error */
        else
        {
          if (ptr_port->Register < UcsiRegDataStructureUnkown)
          {
            UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_1, I2C_ADDRESS_UCSI, UCSI_TRACE_TX_CPLT_COMMAND,
                              (uint8_t* )&ptr_port->Register, 1U);
            UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_I2C_sendToMaster completed");
            TRIG_OPERATION();
          }
          else
          {
            UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_1, I2C_ADDRESS_UCSI, UCSI_TRACE_TX_CPLT_ERROR,
                              (uint8_t* )&ptr_port->Register, 1U);
            TRIG_OPERATION();
          }
        }
      }
      else
      {
        /* Error detected */
        UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Error: Ptr is NULL");
        UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_0, I2C_ADDRESS_UCSI, UCSI_TRACE_ADDRCB_ERROR_TX, NULL, 0U);
        ptr_port->Error = UCSI_ERROR_SEQ_TRANSMIT;
        TRIG_OPERATION();
      }
    }
  }
  else
  {
    /* Message not for our address, NAK the message */
    TRIG_OPERATION();
    VIRT_I2C_sendACK(hi2c, VIRT_I2C_NACK);
  }
}

/**
  * @brief  Initialize UCSI Alert
  * @param  None
  * @retval None
  */
static void UCSI_AlertInit(void)
{
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual INTC OpenAMP-rpmsg channel creation.");
  if (VIRT_INTC_Init(&hintc, 32) != VIRT_INTC_OK) {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_INTC_Init failed.");
    Error_Handler();
  }

  /* Register callback for message reception by channels */
  UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "Virtual INTC OpenAMP-rpmsg callback registering.");
  if(VIRT_INTC_RegisterCallback(&hintc, VIRT_INTC_RXCPLT_CB_ID, NULL) != VIRT_INTC_OK)
  {
    UCSI_IF_PPM_DEBUG_TRACE(UCSI_DEBUG_LEVEL_2, "VIRT_INTC_RegisterCallback failed.");
    Error_Handler();
  }
}

/**
  * @brief  Return the datasize/pointer @ for a register used only for read operation
  * @param  reg          UCSI command
  * @param  PtrDataSize  Pointer on the size of the UCSI command
  * @retval Pointer on the register
  */
static uint8_t *UCSI_GetDataSizeRegisterPtr(UCSI_REG_t reg, uint8_t *PtrDataSize)
{
  switch (reg)
  {
    case UcsiRegDataStructureVersion:
      *PtrDataSize = (uint8_t)sizeof(UCSI_VERSION_t);
      break;
    case UcsiRegDataStructureCci:
      *PtrDataSize = (uint8_t)sizeof(UCSI_CCI_t);
      break;
    case UcsiRegDataStructureControl:
      *PtrDataSize = (uint8_t)sizeof(UCSI_CONTROL_t);
      break;
    case UcsiRegDataStructureMessageIn:
      *PtrDataSize = (uint8_t)sizeof(UCSI_MESSAGE_IN_t);
      break;
    case UcsiRegDataStructureMessageOut:
      *PtrDataSize = (uint8_t)sizeof(UCSI_MESSAGE_OUT_t);
      break;
    case UcsiRegDataStructureUnkown:
    case UcsiRegDataStructureReserved:
    default:
      /* Should not happen */
      *PtrDataSize = 0U;
      UCSI_IF_PPM_TRACE(UCSI_DEBUG_LEVEL_0, I2C_ADDRESS_UCSI, UCSI_TRACE_UCSI_GET, NULL, 0U);
      break;
  }
  return USBPD_PPM_GetDataPointer(reg);
}
