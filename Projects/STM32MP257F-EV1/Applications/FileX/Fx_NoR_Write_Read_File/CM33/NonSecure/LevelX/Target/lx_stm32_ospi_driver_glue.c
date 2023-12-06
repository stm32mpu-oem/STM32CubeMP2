/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/
#include "lx_stm32_ospi_driver.h"

/* HAL DMA API implementation for OctoSPI component MX25LM51245G
 * The present implementation assumes the following settings are set:

  Instance              = OCTOSPI1
  FifoThreshold         = 4
  DualQuad              = disabled
  MemoryType            = Macronix
  DeviceSize            = 26
  ChipSelectHighTime    = 2
  FreeRunningClock      = disabled
  ClockMode             = low
  ClockPrescaler        = 4
  SampleShifting        = none
  DelayHoldQuarterCycle = enabled
  ChipSelectBoundary    = 0
  DelayBlockBypass      = used
 */

extern OSPI_HandleTypeDef hospi2;

#if (LX_STM32_OSPI_INIT == 1)
extern void MX_OCTOSPI1_Init(void);
#endif

static uint8_t ospi_memory_reset            (OSPI_HandleTypeDef *hospi);
static uint8_t ospi_set_write_enable        (OSPI_HandleTypeDef *hospi);
static uint8_t ospi_auto_polling_ready      (OSPI_HandleTypeDef *hospi, uint32_t timeout);
static uint8_t ospi_set_qpi_mode(OSPI_HandleTypeDef *hospi);
static uint8_t ospi_read_device_id(OSPI_HandleTypeDef *hospi);

/* USER CODE BEGIN SECTOR_BUFFER */
ULONG ospi_sector_buffer[LX_STM32_OSPI_SECTOR_SIZE / sizeof(ULONG)];
/* USER CODE END SECTOR_BUFFER */

TX_SEMAPHORE ospi_rx_semaphore;
TX_SEMAPHORE ospi_tx_semaphore;

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
* @brief system init for octospi levelx driver
* @param UINT instance OSPI instance to initialize
* @retval 0 on success error value otherwise
*/
INT lx_stm32_ospi_lowlevel_init(UINT instance)
{
  INT status = 0;

  /* USER CODE BEGIN PRE_OSPI_INIT */

  /* USER CODE END PRE_OSPI_INIT */

  /* Call the DeInit function to reset the driver */
#if (LX_STM32_OSPI_INIT == 1)
  /* Init the OSPI */
  MX_OCTOSPI2_Init();
#endif

  /* OSPI memory reset */
  if (ospi_memory_reset(&hospi2) != 0)
  {
    return 1;
  }

  /* Enable octal mode */
  if (ospi_set_qpi_mode(&hospi2) != 0)
  {
    return 1;
  }

  if (ospi_read_device_id(&hospi2) != 0)
  {
	  return 1;
  }

  /* USER CODE BEGIN POST_OSPI_INIT */

  /* USER CODE END POST_OSPI_INIT */

  return status;
}

/**
* @brief deinit octospi levelx driver, could be called by the fx_media_close()
* @param UINT instance OSPI instance to deinitialize
* @retval 0 on success error value otherwise
*/
INT lx_stm32_ospi_lowlevel_deinit(UINT instance)
{
  INT status = 0;

  /* Delete semaphore objects */
  tx_semaphore_delete(&ospi_tx_semaphore);
  tx_semaphore_delete(&ospi_rx_semaphore);

  /* Call the DeInit function to reset the driver */
  if (HAL_OSPI_DeInit(&hospi2) != HAL_OK)
  {
    return 1;
  }

  /* USER CODE BEGIN PRE_OSPI_DEINIT */

  /* USER CODE END PRE_OSPI_DEINIT */

  return status;
}

/**
* @brief Get the status of the OSPI instance
* @param UINT instance OSPI instance
* @retval 0 if the OSPI is ready 1 otherwise
*/
INT lx_stm32_ospi_get_status(UINT instance)
{
  /* USER CODE BEGIN POST_OSPI_GET_STATUS */
  INT status = 0;
  OSPI_RegularCmdTypeDef s_command;
  uint8_t reg[2];

  /* Initialize the read status register command */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_READ_STATUS_REG_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.NbData                = 1;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	return 1;
  }

  /* Reception of the data */
  if (HAL_OSPI_Receive(&hospi2, reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* Check the value of the register */
  if ((reg[0] & LX_STM32_OSPI_SR_WIP) != 0)
  {
    return 1;
  }

  /* USER CODE END POST_OSPI_GET_STATUS */

  return status;
}

/**
* @brief Get size info of the flash memory
* @param UINT instance OSPI instance
* @param ULONG * block_size pointer to be filled with Flash block size
* @param ULONG * total_blocks pointer to be filled with Flash total number of blocks
* @retval 0 on Success and block_size and total_blocks are correctly filled
          1 on Failure, block_size = 0, total_blocks = 0
*/
INT lx_stm32_ospi_get_info(UINT instance, ULONG *block_size, ULONG *total_blocks)
{
  INT status = 0;

  /* USER CODE BEGIN PRE_OSPI_GET_INFO */

  /* USER CODE END PRE_OSPI_GET_INFO */

  *block_size = LX_STM32_OSPI_SECTOR_SIZE;

  *total_blocks = (LX_STM32_OSPI_FLASH_SIZE / LX_STM32_OSPI_SECTOR_SIZE);

  /* USER CODE BEGIN POST_OSPI_GET_INFO */

  /* USER CODE END POST_OSPI_GET_INFO */
  return status;
}

/**
* @brief Read data from the OSPI memory into a buffer
* @param UINT instance OSPI instance
* @param ULONG * address the start address to read from
* @param ULONG * buffer the destination buffer
* @param ULONG words the total number of words to be read
* @retval 0 on Success 1 on Failure
*/
INT lx_stm32_ospi_read(UINT instance, ULONG *address, ULONG *buffer, ULONG words)
{
  INT status = 0;

  OSPI_RegularCmdTypeDef s_command = {0};

  /* USER CODE BEGIN PRE_OSPI_READ */

  /* USER CODE END PRE_OSPI_READ */

  /* Initialize the read command */
  s_command.Instruction           = LX_STM32_OSPI_QUAD_READ_CMD;
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.Address               = (uint32_t)address;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_4_LINES;
  s_command.AddressSize           = HAL_OSPI_ADDRESS_24_BITS;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE;
  s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
  s_command.NbData                = words * sizeof(ULONG);
  s_command.DummyCycles           = LX_STM32_OSPI_DUMMY_CYCLES_CR_CFG;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressDtrMode        = HAL_OSPI_ADDRESS_DTR_DISABLE;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;

  /* USER CODE BEGIN OSPI_READ_CMD */

  /* USER CODE END OSPI_READ_CMD */

  /* Configure the command */
  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* Reception of the data */
  if (HAL_OSPI_Receive_DMA(&hospi2, (uint8_t*)buffer) != HAL_OK)
  {
    return 1;
  }

  /* USER CODE BEGIN POST_OSPI_READ */

  /* USER CODE END POST_OSPI_READ */

  return status;
}

/**
* @brief write a data buffer into the OSPI memory
* @param UINT instance OSPI instance
* @param ULONG * address the start address to write into
* @param ULONG * buffer the data source buffer
* @param ULONG words the total number of words to be written
* @retval 0 on Success 1 on Failure
*/
INT lx_stm32_ospi_write(UINT instance, ULONG *address, ULONG *buffer, ULONG words)
{
  INT status = 0;
  OSPI_RegularCmdTypeDef s_command = {0};
  uint32_t end_addr;
  uint32_t current_addr;
  uint32_t current_size;
  uint32_t data_buffer;

  /* USER CODE BEGIN PRE_OSPI_WRITE */

  /* USER CODE END PRE_OSPI_WRITE */

  /* Calculation of the size between the write address and the end of the page */
  current_size = LX_STM32_OSPI_PAGE_SIZE - ((uint32_t)address % LX_STM32_OSPI_PAGE_SIZE);

  /* Check if the size of the data is less than the remaining place in the page */
  if (current_size > (((uint32_t) words) * sizeof(ULONG)))
  {
    current_size = ((uint32_t) words) * sizeof(ULONG);
  }

  /* Initialize the address variables */
  current_addr = (uint32_t) address;
  end_addr = ((uint32_t) address) + ((uint32_t) words) * sizeof(ULONG);
  data_buffer= (uint32_t)buffer;

  /* USER CODE BEGIN OSPI_WRITE_CMD */

  /* USER CODE END OSPI_WRITE_CMD */

  /* Perform the write page by page */
  do
  {
    /* Enable write operations */
    if (ospi_set_write_enable(&hospi2) != 0)
    {
      return 1;
    }

	s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
	s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
	s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
	s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
	s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
	s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
	s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
	s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
	s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;
	s_command.Instruction           = LX_STM32_OSPI_QUAD_PAGE_PROG_CMD;
    s_command.AddressMode           = HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressSize           = HAL_OSPI_ADDRESS_24_BITS;
    s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
    s_command.DummyCycles           = 0;
    s_command.Address               = current_addr;
    s_command.NbData                = current_size;

    /* Configure the command */
    if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
    	return 1;
    }

    /* Transmission of the data */
    if (HAL_OSPI_Transmit_DMA(&hospi2, (uint8_t*)data_buffer) != HAL_OK)
    {
    	return 1;
    }


    /* Check success of the transmission of the data */
    if(tx_semaphore_get(&ospi_tx_semaphore, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != TX_SUCCESS)
    {
     return 1;
    }

    /* Configure automatic polling mode to wait for end of program */
    if (ospi_auto_polling_ready(&hospi2, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != 0)
    {
      return 1;
    }

    /* Update the address and data variables for next page programming */
    current_addr += current_size;
    data_buffer += current_size;

    current_size = ((current_addr + LX_STM32_OSPI_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : LX_STM32_OSPI_PAGE_SIZE;
  } while (current_addr < end_addr);

  /* Release ospi_transfer_semaphore in case of writing success */
  tx_semaphore_put(&ospi_tx_semaphore);

  /* USER CODE BEGIN POST_OSPI_WRITE */

  /* USER CODE END POST_OSPI_WRITE */

  return status;
}

/**
* @brief Erase the whole flash or a single block
* @param UINT instance OSPI instance
* @param ULONG  block the block to be erased
* @param ULONG  erase_count the number of times the block was erased
* @param UINT full_chip_erase if set to 0 a single block is erased otherwise the whole flash is erased
* @retval 0 on Success 1 on Failure
*/
INT lx_stm32_ospi_erase(UINT instance, ULONG block, ULONG erase_count, UINT full_chip_erase)
{
  INT status = 0;

  OSPI_RegularCmdTypeDef s_command;

  /* USER CODE BEGIN PRE_OSPI_ERASE */

  /* USER CODE END PRE_OSPI_ERASE */

  /* Initialize the erase command */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.NbData                = 0;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;
  s_command.DataMode              = HAL_OSPI_DATA_NONE;
  s_command.DummyCycles           = 0;
  s_command.AddressDtrMode        = HAL_OSPI_ADDRESS_DTR_DISABLE;
  if(full_chip_erase)
  {
    s_command.Instruction         = LX_STM32_OSPI_QUAD_BULK_ERASE_CMD;
    s_command.AddressMode         = HAL_OSPI_ADDRESS_NONE;
  }
  else
  {
	s_command.Instruction         = LX_STM32_OSPI_QUAD_SECTOR_ERASE_CMD;
	s_command.AddressMode         = HAL_OSPI_ADDRESS_4_LINES;
	s_command.AddressSize         = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address             = (block * LX_STM32_OSPI_SECTOR_SIZE);
  }

  /* USER CODE BEGIN OSPI_ERASE_CMD */

  /* USER CODE END OSPI_ERASE_CMD */

  /* Enable write operations */
  if (ospi_set_write_enable(&hospi2) != 0)
  {
    return 1;
  }

  /* Send the command */
  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
  	return 1;
  }

  /* Configure automatic polling mode to wait for end of erase */
  if (ospi_auto_polling_ready(&hospi2, LX_STM32_OSPI_BULK_ERASE_MAX_TIME) != 0)
  {
    return 1;
  }

  /* USER CODE BEGIN POST_OSPI_ERASE */

  /* USER CODE END POST_OSPI_ERASE */

  return status;
}

/**
* @brief Check that a block was actually erased
* @param UINT instance OSPI instance
* @param ULONG  block the block to be checked
* @retval 0 on Success 1 on Failure
*/
INT lx_stm32_ospi_is_block_erased(UINT instance, ULONG block)
{
  INT status = 0;

  /* USER CODE BEGIN OSPI_BLOCK_ERASED */

  /* USER CODE END OSPI_BLOCK_ERASED */

  return status;
}

/**
* @brief Handle levelx system errors
* @param UINT error_code Code of the concerned error.
* @retval UINT error code.
*/

UINT  lx_ospi_driver_system_error(UINT error_code)
{
  UINT status = LX_ERROR;

  /* USER CODE BEGIN OSPI_SYSTEM_ERROR */

  /* USER CODE END OSPI_SYSTEM_ERROR */

  return status;
}

/**
  * @brief  Reset the OSPI memory.
  * @param  hospi: OSPI handle pointer
  * @retval O on success 1 on Failure.
  */
static uint8_t ospi_memory_reset(OSPI_HandleTypeDef *hospi)
{
  uint8_t status = 0;

  OSPI_RegularCmdTypeDef s_command;
  OSPI_AutoPollingTypeDef s_config;

  /* Initialize the reset enable command */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_RESET_ENABLE_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_1_LINE;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_NONE;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;

  /* Send the command */
  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* Send the reset memory command */
  s_command.Instruction = LX_STM32_OSPI_RESET_MEMORY_CMD;
  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* Configure automatic polling mode to wait the memory is ready */
  s_command.Instruction  = LX_STM32_OSPI_READ_STATUS_REG_CMD;
  s_command.DataMode     = HAL_OSPI_DATA_1_LINE;
  s_command.NbData       = 1;
  s_command.DataDtrMode  = HAL_OSPI_DATA_DTR_DISABLE;

  s_config.Match         = 0;
  s_config.Mask          = LX_STM32_OSPI_SR_WIP;
  s_config.MatchMode     = HAL_OSPI_MATCH_MODE_AND;
  s_config.Interval      = 0x10;
  s_config.AutomaticStop = HAL_OSPI_AUTOMATIC_STOP_ENABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  if (HAL_OSPI_AutoPolling(&hospi2, &s_config, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* USER CODE BEGIN OSPI_MEMORY_RESET_CMD */

  /* USER CODE END OSPI_MEMORY_RESET_CMD */

  return status;
}

/**
  * @brief  Send a Write Enable command and wait its effective.
  * @param  hospi: OSPI handle pointer
  * @retval O on success 1 on Failure.
  */
static uint8_t ospi_set_write_enable(OSPI_HandleTypeDef *hospi)
{
  uint8_t status = 0;

  OSPI_RegularCmdTypeDef  s_command;
  OSPI_AutoPollingTypeDef s_config;

  /* Enable write operations */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_WRITE_ENABLE_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_NONE;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;

  /* DTR mode is disabled */
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  /* Initialize the read status register command */
	s_command.Instruction           = LX_STM32_OSPI_READ_STATUS_REG_CMD;
	s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
	s_command.NbData                = 2;

	if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return 1;
	}

	/* Configure automatic polling mode to wait for WEL enabling */
	s_config.MatchMode     		  = HAL_OSPI_MATCH_MODE_AND;
	s_config.Interval      	      = 0x10;
	s_config.AutomaticStop        = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
	s_config.Match 		          = LX_STM32_OSPI_SR_WEL;
	s_config.Mask  		          = LX_STM32_OSPI_SR_WEL;

	if (HAL_OSPI_AutoPolling(&hospi2, &s_config, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return 1;
	}

 /* USER CODE BEGIN OSPI_WRITE_ENABLE_CMD */

 /* USER CODE END OSPI_WRITE_ENABLE_CMD */

  return status;
}

/**
  * @brief  Read the SR of the memory and wait the EOP.
  * @param  hospi: OSPI handle pointer
  * @param  timeout: timeout value before returning an error
  * @retval O on success 1 on Failure.
  */
static uint8_t ospi_auto_polling_ready(OSPI_HandleTypeDef *hospi, uint32_t timeout)
{
  uint8_t status = 0;

  OSPI_RegularCmdTypeDef  s_command;
  OSPI_AutoPollingTypeDef s_config;
  uint8_t reg[2];
  uint32_t start = LX_STM32_OSPI_CURRENT_TIME();

  /* Configure automatic polling mode to wait for memory ready */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_READ_STATUS_REG_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.Address               = 0;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
  s_command.NbData                = 2;
  s_command.DummyCycles           = 0x00;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressDtrMode        = HAL_OSPI_ADDRESS_DTR_DISABLE;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;

  s_config.Match                  = 0;
  s_config.Mask                   = LX_STM32_OSPI_SR_WIP;

  while( LX_STM32_OSPI_CURRENT_TIME() - start < timeout)
  {
     if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      status = 1;
      break;
    }

    if (HAL_OSPI_Receive(&hospi2, reg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
      status = 1;
      break;
    }
    /* the Memory is ready, break from the loop */
    if ((reg[0] & s_config.Mask ) == s_config.Match)
    {
      break;
    }
  }

  /* USER CODE BEGIN OSPI_AUTO_POLLING_READY */

  /* USER CODE END OSPI_AUTO_POLLING_READY */
  return status;
}

static uint8_t ospi_read_device_id(OSPI_HandleTypeDef *hospi)
{
  uint8_t status = 0;
  OSPI_RegularCmdTypeDef s_command;
  uint8_t test_buffer[4] = { 0 };

  /* Read the status register command */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_READ_QPIID_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_4_LINES;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_4_LINES;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.NbData                = 3;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	return 1;
  }

  if (HAL_OSPI_Receive(&hospi2, test_buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	  return 1;
  }
  return status;
}

/**
  * @brief  This function enables the qpi mode of the memory.
  * @param  hospi: OSPI handle
  * @retval 0 on success 1 on Failure.
  */
static uint8_t ospi_set_qpi_mode(OSPI_HandleTypeDef *hospi)
{
  uint8_t status = 0;
  OSPI_RegularCmdTypeDef s_command;
  OSPI_AutoPollingTypeDef s_config;

  /* Read the status register command */
  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_ENABLE_QPI_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_1_LINE;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_NONE;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.NbData                = 0;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
	return 1;
  }

  /* Configure automatic polling mode to wait for QPI enabling */
  s_config.MatchMode     		  = HAL_OSPI_MATCH_MODE_AND;
  s_config.Interval      	      = 0x10;
  s_config.AutomaticStop          = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
  s_config.Match 		          = LX_STM32_OSPI_SR_QPI;
  s_config.Mask  		          = LX_STM32_OSPI_SR_QPI;

  s_command.OperationType         = HAL_OSPI_OPTYPE_COMMON_CFG;
  s_command.FlashId               = HAL_OSPI_FLASH_ID_1;
  s_command.Instruction           = LX_STM32_OSPI_READ_STATUS_REG_CMD;
  s_command.InstructionMode       = HAL_OSPI_INSTRUCTION_1_LINE;
  s_command.InstructionSize       = HAL_OSPI_INSTRUCTION_8_BITS;
  s_command.InstructionDtrMode    = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  s_command.AddressMode           = HAL_OSPI_ADDRESS_NONE;
  s_command.AlternateBytesMode    = HAL_OSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode              = HAL_OSPI_DATA_1_LINE;
  s_command.DummyCycles           = 0;
  s_command.DQSMode               = HAL_OSPI_DQS_DISABLE;
  s_command.SIOOMode              = HAL_OSPI_SIOO_INST_EVERY_CMD;
  s_command.NbData                = 1;
  s_command.DataDtrMode           = HAL_OSPI_DATA_DTR_DISABLE;

  if (HAL_OSPI_Command(&hospi2, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  if (HAL_OSPI_AutoPolling(&hospi2, &s_config, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return 1;
  }

  return status;
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  hospi OSPI handle
  * @retval None
  */
void HAL_OSPI_RxCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* USER CODE BEGIN PRE_RX_CMPLT */

  /* USER CODE END PRE_RX_CMPLT */

  tx_semaphore_put(&ospi_rx_semaphore);

  /* USER CODE BEGIN POST_RX_CMPLT */

  /* USER CODE END POST_RX_CMPLT */
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hospi OSPI handle
  * @retval None
  */
void HAL_OSPI_TxCpltCallback(OSPI_HandleTypeDef *hospi)
{
  /* USER CODE BEGIN PRE_TX_CMPLT */

  /* USER CODE END PRE_TX_CMPLT */

  tx_semaphore_put(&ospi_tx_semaphore);

  /* USER CODE BEGIN POST_TX_CMPLT */

  /* USER CODE END POST_TX_CMPLT */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
