/**
  ******************************************************************************
  * @file    stm32mp257f_eval_stpmic.h
  * @author  MCD Application Team
  * @brief   stpmu driver functions used for ST internal validation
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP257F_EVAL_STPMIC_H
#define STM32MP257F_EVAL_STPMIC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"
#include "stpmic2.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32MP257F_EVAL_STPMU
  * @{
  */

/** @defgroup STM32MP257F_EVAL_STPMU_Exported_Types Exported Types
  * @{
  */
 typedef enum
 {
   VDDCPU=0,
   VDDCORE,
   VDDGPU,
   VDDIO_PMIC,
   VDDA1V8_AON,
   V1V8,
   VDD3V3_USB,
   VDD_DDR,
   VREF_DDR,
   VTT_DDR,
   VPP_DDR,
   VDD_SDCARD,
   VDDIO_SDCARD,
   V3V3
 }board_regul_t;

 typedef struct {
   char                 boardRegulName[15]; /* board regulator name */
   board_regul_t        boardRegulId;  /* board regulator Id */
   PMIC_RegulId_TypeDef pmicRegul;  /* pmic regulator */
   uint8_t              control_reg1;
   uint8_t              control_reg2;
   uint32_t             regulMin; /* regulator-min-mvolt */
   uint32_t             regulMax; /* regulator-max-mvolt */
 } board_regul_struct;

/* Exported types ------------------------------------------------------------*/
/**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_STPMU_Exported_Constants Exported Constants
  * @{
  */
 /* Board Configuration ------------------------------------------------------------*/
 /* Definition of PMIC <=> stm32mp2 Signals */
 #define PMIC_INTn_PIN               GPIO_PIN_8
 #define PMIC_INTn_PORT              GPIOF
 #define PMIC_INTn_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
 #define PMIC_INTn_CLK_DISABLE()     __HAL_RCC_GPIOF_CLK_DISABLE()
 #define PMIC_INTn_EXTI_IRQ          EXTI8_IRQn
 #define BSP_PMIC_INTn_IRQHandler    EXTI8_IRQHandler

 #define BSP_PMIC_PWRCTRL_PIN_Assert()   HAL_GPIO_WritePin(PMIC_PWRCTRL_PORT, PMIC_PWRCTRL_PIN, GPIO_PIN_RESET);
 #define BSP_PMIC_PWRCTRL_PIN_Pull()     HAL_GPIO_WritePin(PMIC_PWRCTRL_PORT, PMIC_PWRCTRL_PIN, GPIO_PIN_SET);

 /**
   * @brief  STPMIC2 product ID
   */
 #define  STPMIC2_ID           0x20U /* Default PMIC product ID: 0x2X (X depends on PMIC variant) */


 /**
   * @}
   */

  /** @defgroup STM32MP257F_EVAL_STPMU_Private_Defines Private Defines
   * @{
   */
 /* Private typedef -----------------------------------------------------------*/


 /* Private define ------------------------------------------------------------*/
 #define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

  /**
   * @}
   */

 /** @defgroup STM32MP257F_EVAL_STPMU_Private_Variables Private Variables
   * @{
   */

/* Exported constants --------------------------------------------------------*/

/**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_STPMU_Exported_Functions Exported Functions
  * @{
  */

/* Exported functions --------------------------------------------------------*/
uint32_t BSP_PMIC_Init(void);
uint32_t BSP_PMIC_DeInit(void);
uint32_t BSP_PMIC_Is_Device_Ready(void);
uint32_t BSP_PMIC_DDR_Power_Init();
uint32_t BSP_PMIC_DumpRegs (void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32MP257F_EVAL_STPMIC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
