/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   This file contains the Application exemple to manage the USB PD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32mp257cxx_validx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* I2C device address */
#define UCSI_DEV_ADDR       0x35

/* IRQ line ID */
#define UCSI_INTC_IRQ		0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef COM_Init;
IPCC_HandleTypeDef hipcc;

/* USER CODE BEGIN PV */
VIRT_I2C_HandleTypeDef hi2c;
VIRT_INTC_HandleTypeDef hintc;

/* flagstatus to inform about an I2C request */
__IO FlagStatus VirtI2CRequest = RESET;

rpmsg_i2c_msg *message;

/* Exported variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void MX_IPCC_Init(void);
static void MX_VIRT_I2C_Init(void);
static void MX_VIRT_INTC_Init(void);

static void VIRT_I2C_RxCpltCallback(VIRT_I2C_HandleTypeDef *hi2c, size_t len);
static void VIRT_I2C_EV_Handler(VIRT_I2C_HandleTypeDef *hi2c);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  unsigned int counter = 0;

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Initialize Display destination */
#if defined(__VALID_OUTPUT_TERMINAL_IO__) && defined (__GNUC__)
  initialise_monitor_handles();
#else
  COM_Init.BaudRate                = 115200;
  COM_Init.WordLength              = UART_WORDLENGTH_8B;
  COM_Init.StopBits                = UART_STOPBITS_1;
  COM_Init.Parity                  = UART_PARITY_NONE;
  COM_Init.HwFlowCtl               = UART_HWCONTROL_NONE;
  /* Initialize and select COM1 which is the COM port associated with current Core */
  BSP_COM_Init(COM_VCP_CM33, &COM_Init);
  BSP_COM_SelectLogPort(COM_VCP_CM33);
#endif

  /* Initialize GREEN led */
  BSP_LED_Init(LED2);
  BSP_LED_On(LED2);

  loc_printf("\n\n Starting UCSI project(%s: %s) \r\n", __DATE__, __TIME__);

  /* IPCC initialisation */
  MX_IPCC_Init();

#if defined (RPMSG_LATE_ATTACH)
  /*
   * To enable only if the firmware is loaded by U-Boot
   * Do some works waiting Kick for the Host processor
   */
  while (OPENAMP_check_for_message())
  {
    BSP_LED_Toggle(LED2);
    HAL_Delay(1000);
  }
#endif /* RPMSG_LATE_ATTACH */

#if defined (CORE_CA35) || defined (CORE_CM33)
  /* Update System clock variable SystemCoreClock for debug */
  SystemCoreClockUpdate();
#endif /* CORE_CA35 || CORE_CM33 */

  /* OpenAmp initialisation ---------------------------------*/
  MX_OPENAMP_Init(RPMSG_REMOTE, NULL);

  MX_VIRT_INTC_Init();
  MX_VIRT_I2C_Init();

   /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* routine to check for new Remoteproc message (RPMsg)*/
  OPENAMP_check_for_message();

    /* LED blinking */
  if(counter++ == 200000) {
    BSP_LED_Toggle(LED2);
    counter = 0;
  }
    /* UCSI CODE BEGIN */

  /* Treat virtual I2C event */
  if (VirtI2CRequest) {
    VirtI2CRequest = RESET;
    VIRT_I2C_EV_Handler(&hi2c);
  }

  }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}

/**
  * @brief IPPC Initialization Function
  * @param None
  * @retval None
  */
static void MX_IPCC_Init(void)
{

  hipcc.Instance = IPCC1;
  if (HAL_IPCC_Init(&hipcc) != HAL_OK)
  {
     Error_Handler();
  }
}

static void MX_VIRT_I2C_Init(void)
{
  log_info("Virtual I2C OpenAMP-rpmsg channel creation\r\n");
  if (VIRT_I2C_Init(&hi2c) != VIRT_I2C_OK) {
    log_err("VIRT_I2C_Init failed.\r\n");
    Error_Handler();
  }

  /*Need to register callback for message reception by channels*/
  if(VIRT_I2C_RegisterCallback(&hi2c, VIRT_I2C_RXCPLT_CB_ID,
             VIRT_I2C_RxCpltCallback) != VIRT_I2C_OK) {
    Error_Handler();
  }
}

static void MX_VIRT_INTC_Init(void)
{
  log_info("Virtual INTC OpenAMP-rpmsg channel creation\r\n");
  if (VIRT_INTC_Init(&hintc, 32) != VIRT_INTC_OK) {
    log_err("VIRT_INTC_Init failed.\r\n");
    Error_Handler();
  }
  /*Need to register callback for message reception by channels*/
  if(VIRT_INTC_RegisterCallback(&hintc, VIRT_INTC_RXCPLT_CB_ID, NULL) != VIRT_INTC_OK)
  {
    Error_Handler();
  }
}

static void i2c_rpmsg_slave_write(VIRT_I2C_HandleTypeDef *hi2c)
{
  rpmsg_i2c_msg *msg = hi2c->msg;
  uint32_t len = msg->len;
  uint8_t *buf = msg->buf;

  /* UCSI CODE BEGIN */
  /* UCSI CODE END */

  log_dbg("%s: ack\n\r", __func__);
  VIRT_I2C_sendACK(hi2c, VIRT_I2C_ACK);
  return;

err:
  log_dbg("%s: Nack\n\r", __func__);
  VIRT_I2C_sendACK(hi2c, VIRT_I2C_NACK);
}

static void i2c_rpmsg_slave_read(VIRT_I2C_HandleTypeDef *hi2c)
{
  rpmsg_i2c_msg *msg = hi2c->msg;
  uint32_t len = msg->len;
  uint8_t *buf = msg->buf;

  if (!len)
    goto err;

  /* UCSI CODE BEGIN */
  /* UCSI CODE END */

  log_info("%s: ack\n\r", __func__);
  VIRT_I2C_sendToMaster(hi2c, msg->buf, msg->len);
  return;
err:
  log_err("%s: Nack\n\r", __func__);
  VIRT_I2C_sendACK(hi2c, VIRT_I2C_NACK);
}

static void VIRT_I2C_EV_Handler(VIRT_I2C_HandleTypeDef *hi2c)
{
  uint8_t addr;

  addr = VIRT_I2C_addrFromMsg(hi2c);
  if (addr != UCSI_DEV_ADDR) {
    VIRT_I2C_sendACK(hi2c, VIRT_I2C_NACK);
    return;
  }

  log_dbg("Msg on VIRTUAL I2C (addr:%#x data count:%ld)\n\r",
          addr, hi2c->msg->len);

  if (hi2c->msg->addr & I2C_MASTER_READ) {
    i2c_rpmsg_slave_read(hi2c);
  } else {
    i2c_rpmsg_slave_write(hi2c);
  }
}


static void VIRT_I2C_RxCpltCallback(VIRT_I2C_HandleTypeDef *hi2c, size_t len)
{
  log_dbg("%s: virt i2c request\n\r", __func__);
  /* set a variable to treat event in the main while loop*/
  VirtI2CRequest = SET;
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while(1)
  {
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
