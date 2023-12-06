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

#ifndef LX_STM32_OSPI_DRIVER_H
#define LX_STM32_OSPI_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lx_api.h"
#include "stm32mp2xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* The following semaphore is being to notify about RX/TX completion. It needs to be released in the transfer callbacks */
extern TX_SEMAPHORE ospi_rx_semaphore;
extern TX_SEMAPHORE ospi_tx_semaphore;

/* Exported constants --------------------------------------------------------*/

/* the OctoSPI instance, default value set to 0 */
#define LX_STM32_OSPI_INSTANCE                           0

#define LX_STM32_OSPI_DEFAULT_TIMEOUT                    10 * TX_TIMER_TICKS_PER_SECOND

#define LX_STM32_DEFAULT_SECTOR_SIZE                     LX_STM32_OSPI_SECTOR_SIZE
#define LX_STM32_OSPI_DMA_API                            1

/* when set to 1 LevelX is initializing the OctoSPI memory,
 * otherwise it is the up to the application to perform it.
 */
#define LX_STM32_OSPI_INIT                               1

/* allow the driver to fully erase the OctoSPI chip. This should be used carefully.
 * the call is blocking and takes a while. by default it is set to 0.
 */
#define LX_STM32_OSPI_ERASE                              0

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

#define LX_STM32_OSPI_CURRENT_TIME                              tx_time_get

/* Macro called after initializing the OSPI driver
 * e.g. create a semaphore used for transfer notification */
 /* USER CODE BEGIN LX_STM32_OSPI_POST_INIT */

#define LX_STM32_OSPI_POST_INIT()                        do { \
                                                         if (tx_semaphore_create(&ospi_rx_semaphore, "ospi rx transfer semaphore", 0) != TX_SUCCESS) \
                                                         { \
                                                           return LX_ERROR; \
                                                         } \
                                                         if (tx_semaphore_create(&ospi_tx_semaphore, "ospi tx transfer semaphore", 0) != TX_SUCCESS) \
                                                         { \
                                                           return LX_ERROR; \
                                                         } \
                                                        } while(0)
/* USER CODE END LX_STM32_OSPI_POST_INIT */

/* Macro called before performing read operation */

/* USER CODE BEGIN LX_STM32_OSPI_PRE_READ_TRANSFER */

#define LX_STM32_OSPI_PRE_READ_TRANSFER(__status__)

/* USER CODE END LX_STM32_OSPI_PRE_READ_TRANSFER */

/* Define how to notify about Read completion operation */

/* USER CODE BEGIN LX_STM32_OSPI_READ_CPLT_NOTIFY */

#define LX_STM32_OSPI_READ_CPLT_NOTIFY(__status__)      do { \
                                                          if(tx_semaphore_get(&ospi_rx_semaphore, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != TX_SUCCESS) \
                                                          { \
                                                            __status__ = LX_ERROR; \
                                                          } \
                                                        } while(0)

/* USER CODE END LX_STM32_OSPI_READ_CPLT_NOTIFY */

/* Macro called after performing read operation */

/* USER CODE BEGIN LX_STM32_OSPI_POST_READ_TRANSFER */

#define LX_STM32_OSPI_POST_READ_TRANSFER(__status__)

/* USER CODE END LX_STM32_OSPI_POST_READ_TRANSFER */

/* Macro for read error handling */
/* USER CODE BEGIN LX_STM32_OSPI_READ_TRANSFER_ERROR */

#define LX_STM32_OSPI_READ_TRANSFER_ERROR(__status__)

/* USER CODE END LX_STM32_OSPI_READ_TRANSFER_ERROR */

/* Macro called before performing write operation */

/* USER CODE BEGIN LX_STM32_OSPI_PRE_WRITE_TRANSFER */

#define LX_STM32_OSPI_PRE_WRITE_TRANSFER(__status__)

/* USER CODE END LX_STM32_OSPI_PRE_WRITE_TRANSFER */

/* Define how to notify about write completion operation */

/* USER CODE BEGIN LX_STM32_OSPI_WRITE_CPLT_NOTIFY */

#define LX_STM32_OSPI_WRITE_CPLT_NOTIFY(__status__)     do { \
                                                          if(tx_semaphore_get(&ospi_tx_semaphore, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != TX_SUCCESS) \
                                                          { \
                                                            __status__ = LX_ERROR; \
                                                          } \
                                                        } while(0)

/* USER CODE END LX_STM32_OSPI_WRITE_CPLT_NOTIFY */

/* Macro called after performing write operation */

/* USER CODE BEGIN LX_STM32_OSPI_POST_WRITE_TRANSFER */

#define LX_STM32_OSPI_POST_WRITE_TRANSFER(__status__)

/* USER CODE END LX_STM32_OSPI_POST_WRITE_TRANSFER */

/* Macro for write error handling */

/* USER CODE BEGIN LX_STM32_OSPI_WRITE_TRANSFER_ERROR */

#define LX_STM32_OSPI_WRITE_TRANSFER_ERROR(__status__)

/* USER CODE END LX_STM32_OSPI_WRITE_TRANSFER_ERROR */

/* Exported functions prototypes ---------------------------------------------*/
INT lx_stm32_ospi_lowlevel_init(UINT instance);
INT lx_stm32_ospi_lowlevel_deinit(UINT instance);

INT lx_stm32_ospi_get_status(UINT instance);
INT lx_stm32_ospi_get_info(UINT instance, ULONG *block_size, ULONG *total_blocks);

INT lx_stm32_ospi_read(UINT instance, ULONG *address, ULONG *buffer, ULONG words);
INT lx_stm32_ospi_write(UINT instance, ULONG *address, ULONG *buffer, ULONG words);

INT lx_stm32_ospi_erase(UINT instance, ULONG block, ULONG erase_count, UINT full_chip_erase);
INT lx_stm32_ospi_is_block_erased(UINT instance, ULONG block);

UINT lx_ospi_driver_system_error(UINT error_code);

UINT lx_stm32_ospi_initialize(LX_NOR_FLASH *nor_flash);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

#define LX_STM32_OSPI_DUMMY_CYCLES_READ_OCTAL     20
#define LX_STM32_OSPI_DUMMY_CYCLES_CR_CFG         6
//
#define LX_STM32_OSPI_SECTOR_SIZE                 (uint32_t) (64 * 1024)        /*!< 256 blocks of 64KBytes */
#define LX_STM32_OSPI_FLASH_SIZE                  (uint32_t) (512*1024*1024/8)  /*!< 512 MBits => 64MBytes */
#define LX_STM32_OSPI_PAGE_SIZE                   (uint32_t) 256                /*!< 262144 pages of 256 Bytes */
//
#define LX_STM32_OSPI_BULK_ERASE_MAX_TIME         600000U

#define LX_STM32_OSPI_QUAD_BULK_ERASE_CMD         0x60   /*!< CE, Chip Erase 0 Byte Address; SPI/QPI 1-0-0/4-0-0               */
#define LX_STM32_OSPI_QUAD_SECTOR_ERASE_CMD       0x20   /*!< SE, Sector Erase 4KB 3/4 Byte Address; SPI/QPI 1-1-0/4-4-0       */
//
#define LX_STM32_OSPI_WRITE_ENABLE_CMD            0x06   /*!< WREN, Write Enable; SPI/QPI                        */

#define LX_STM32_OSPI_READ_ID_CMD				  0x9F   /*!< RDID, Read IDentification; SPI                         */
#define LX_STM32_OSPI_READ_QPIID_CMD			  0xAF   /*!< QPIID, QPI ID Read; QPI                                */
#define LX_STM32_OSPI_ENABLE_QPI_CMD			  0x35   /*!< EQIO, Enable QPI; Enter QPI; SPI */
#define LX_STM32_OSPI_READ_STATUS_REG_CMD         0x05   /*!< RDSR, Read Status Register; SPI/QPI                */
#define LX_STM32_OSPI_WRITE_STATUS_REG_CMD        0x01   /*!< WRSR, Write Status/Configuration Register; SPI/QPI */
#define LX_STM32_OSPI_READ_CFG_REG_CMD            0x15   /*!< RDCR, Read Configuration Register; SPI/QPI         */

#define LX_STM32_OSPI_QUAD_READ_CMD               0xEB   /*!< 4READ, 4 I/O Read 3/4 Byte Address; SPI/QPI 1-1-1/4-4-4          */

#define LX_STM32_OSPI_RESET_ENABLE_CMD            0x66   /*!< RSETEN, Reset Enable; SPI/QPI  */
#define LX_STM32_OSPI_RESET_MEMORY_CMD            0x99   /*!< RST, Reset Memory; SPI/QPI     */

#define LX_STM32_OSPI_QUAD_PAGE_PROG_CMD		  0x02   /*!< PP, Page Program 3/4 Byte Address; SPI/QPI 1-1-1/4-4-4           */

#define LX_STM32_OSPI_SR_WEL                      ((uint8_t)0x02)    /*!< Write enable latch */
#define LX_STM32_OSPI_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define LX_STM32_OSPI_SR_QPI                      ((uint8_t)0x40)    /*!< QE bit; Quad IO mode enabled if =1 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* LX_STM32_OSPI_DRIVER_H */
