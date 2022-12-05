/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_cryp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of CRYP HAL Extension module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_CRYP_EX_H
#define STM32MP2xx_HAL_CRYP_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */
#if (defined (CRYP1) || defined (CRYP2))
/** @addtogroup CRYPEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Types CRYPEx Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Variables CRYPEx Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Constants CRYPEx Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Macros CRYPEx Private Macros
  * @{
  */

/**
  * @}
 */

/* Private functions ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Functions CRYPEx Private Functions
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CRYPEx_Exported_Functions CRYPEx Exported Functions
  * @{
  */

/** @addtogroup CRYPEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_CRYPEx_AESGCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, uint32_t *AuthTag, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_AESCCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, uint32_t *AuthTag, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_EncryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *Key, uint32_t *Output, uint32_t ID,
                                              uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_DecryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *Key, uint32_t ID, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_UnwrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_WrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *Input, uint32_t *Output, uint32_t Timeout);

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
#endif /* (defined (CRYP1) || defined (CRYP2)) */
/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_CRYP_EX_H */