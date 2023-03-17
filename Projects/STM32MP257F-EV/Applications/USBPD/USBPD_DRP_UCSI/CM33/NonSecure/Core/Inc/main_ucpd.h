/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2022 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* External functions --------------------------------------------------------*/
extern void initialise_monitor_handles(void);

/* Exported constants --------------------------------------------------------*/
#define DEFAULT_IRQ_PRIO      1U
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32mp2xx_hal.h"
#include "stm32mp257cxx_validx.h"
#include "openamp.h"
#include "openamp_log.h"

/* Include files of IP validation tests */
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#if defined(NO_PRINTF)
  #define loc_printf(...)
#else
  #define loc_printf(mess, ...)   printf(mess, ##__VA_ARGS__)
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Error_Handler(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
