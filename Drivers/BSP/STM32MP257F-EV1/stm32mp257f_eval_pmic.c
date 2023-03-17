/**
  ******************************************************************************
  * @file    stm32mp257f_eval_stpmic.c
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

/* Includes ----------------------------------------------------------------------*/
#include "stm32mp257f_eval.h"
#include "stm32mp257f_eval_bus.h"
#include "stm32mp257f_eval_pmic.h"
#include <string.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32MP257F_EVAL_STPMU
  * @{
  */


/** @defgroup STM32MP257F_EVAL_STPMU_Private_Constants Private Constants
  * @{
  */
/* Driver for PMIC ---------------------------------------------------------------*/

/* Board Configuration ------------------------------------------------------------*/
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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;
extern I2C_HandleTypeDef hI2c7;

static STPMIC2_Drv_t *Stpmic2Drv = NULL;
static void         *CompObj = NULL;


/*
  Table of EVAL board regulators
*/

board_regul_struct board_regulators_table[] = {
  {"VDDCPU",      VDDCPU,      STPMIC_BUCK1,  BUCK1_MAIN_CR1,  BUCK1_MAIN_CR2,  800,  910},
  {"VDDCORE",     VDDCORE,     STPMIC_BUCK2,  BUCK2_MAIN_CR1,  BUCK2_MAIN_CR2,  820,  820},
  {"VDDGPU",      VDDGPU,      STPMIC_BUCK3,  BUCK3_MAIN_CR1,  BUCK3_MAIN_CR2,  800,  900},
  {"VDDIO_PMIC",  VDDIO_PMIC,  STPMIC_BUCK4,  BUCK4_MAIN_CR1,  BUCK4_MAIN_CR2,  3300, 3300},
  {"VDDA1V8_AON", VDDA1V8_AON, STPMIC_LDO1,   LDO1_MAIN_CR,    LDO1_MAIN_CR,    1800, 1800},
  {"V1V8",        V1V8,        STPMIC_BUCK5,  BUCK5_MAIN_CR1,  BUCK5_MAIN_CR2,  1800, 1800},
  {"VDD3V3_USB",  VDD3V3_USB,  STPMIC_LDO4,   LDO4_MAIN_CR,    LDO4_MAIN_CR,    3300, 3300},
  {"VDD_DDR",     VDD_DDR,     STPMIC_BUCK6,  BUCK6_MAIN_CR1,  BUCK6_MAIN_CR2,  1200, 1200},
  {"VREF_DDR",    VREF_DDR,    STPMIC_REFDDR, REFDDR_MAIN_CR,  REFDDR_MAIN_CR,  0000, 0000},
  {"VTT_DDR",     VTT_DDR,     STPMIC_LDO3,   LDO3_MAIN_CR,    LDO3_MAIN_CR,    0000, 0000},
  {"VPP_DDR",     VPP_DDR,     STPMIC_LDO5,   LDO5_MAIN_CR,    LDO5_MAIN_CR,    2500, 2500},
  {"VDD_SDCARD",  VDD_SDCARD,  STPMIC_LDO7,   LDO7_MAIN_CR,    LDO7_MAIN_CR,    1800, 3300},
  {"VDDIO_SDCARD",VDDIO_SDCARD,STPMIC_LDO8,   LDO8_MAIN_CR,    LDO8_MAIN_CR,    3300, 3300},
  {"V3V3",        V3V3,        STPMIC_BUCK7,  BUCK7_MAIN_CR1,  BUCK7_MAIN_CR2,  3300, 3300},
};


 /**
  * @}
  */

/** @defgroup STM32MP257F_EVAL_STPMU_Private_Functions Private Functionss
  * @{
  */

/* Private function prototypes -----------------------------------------------*/

STPMIC2_Object_t   STPMIC2Obj = { 0 };
static int32_t STPMIC_Probe();

/* Private functions ---------------------------------------------------------*/


static int32_t STPMIC_Probe()
{
  int32_t ret;
  STPMIC2_IO_t              IOCtx;
  uint8_t                  id;

  /* Only perform the init if the object already exist */
  if (!CompObj)
  {
    /* Configure the I2C driver */
    IOCtx.Address     = STPMIC_I2C_ADDRESS;
    IOCtx.Init        = BSP_I2C7_Init;
    IOCtx.DeInit      = BSP_I2C7_DeInit;
    IOCtx.ReadReg     = BSP_I2C7_ReadReg;
    IOCtx.WriteReg    = BSP_I2C7_WriteReg;
    IOCtx.GetTick     = BSP_GetTick;

    ret = STPMIC2_RegisterBusIO (&STPMIC2Obj, &IOCtx);
    if (ret != STPMIC2_OK)
    {
      return BSP_ERROR_COMPONENT_FAILURE;
    }

    ret = STPMIC2_ReadID(&STPMIC2Obj, &id);
    if (ret != STPMIC2_OK)
    {
      return BSP_ERROR_COMPONENT_FAILURE;
    }

    if((id & 0xF0) != STPMIC2_ID )
    {
      return BSP_ERROR_UNKNOWN_COMPONENT;
    }

    Stpmic2Drv = (STPMIC2_Drv_t *) &STPMIC2_Driver;
    CompObj = &STPMIC2Obj;
  }

  ret = Stpmic2Drv->Init(CompObj);
  if (ret != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }

  return BSP_ERROR_NONE;
}

uint32_t BSP_PMIC_Init(void)
{
  int32_t status = BSP_ERROR_NONE;

  status = STPMIC_Probe();
  if ( status != BSP_ERROR_NONE )
  {
    return status;
  }

  return BSP_ERROR_NONE;
}

uint32_t BSP_PMIC_DeInit(void)
{
  uint32_t  status = BSP_ERROR_NONE;

  status = Stpmic2Drv->DeInit(CompObj);
  if (status != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return status;
}

uint32_t BSP_PMIC_ReadReg(uint8_t reg, uint8_t *pdata)
{
  int32_t  status = BSP_ERROR_NONE;

  status = Stpmic2Drv->ReadReg(CompObj, reg, pdata);
  if (status != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return status;
}

uint32_t BSP_PMIC_WriteReg(uint8_t reg, uint8_t data)
{
  int32_t  status = BSP_ERROR_NONE;

  status = Stpmic2Drv->WriteReg(CompObj, reg, data);
  if (status != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return status;
}

uint32_t BSP_PMIC_UpdateReg(uint8_t reg, uint8_t mask)
{
  int32_t  status = BSP_ERROR_NONE;

  status = Stpmic2Drv->UpdateReg(CompObj, reg, mask);
  if (status != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return status;
}

/*
 *
 * PMIC registers dump
 *
 */
/* following are configurations */
uint32_t BSP_PMIC_DumpRegs (void)
{
  uint32_t  status = BSP_ERROR_NONE;

  status = Stpmic2Drv->DumpRegs(CompObj);
  if (status != STPMIC2_OK)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }

  return status;
}

/*
 *
 * following are configurations for this board
 * same configuration than linux
 *
 *  BSP_PMIC_DDR_Power_Init initialize DDR power
 *
 * DDR power on sequence is:
 * enable VPP_DDR
 * wait 2ms
 * enable VREF_DDR, VTT_DDR, VPP_DDR
 *
 *
 */
/* following are configurations */
uint32_t BSP_PMIC_DDR_Power_Init()
{
  uint32_t  status = BSP_ERROR_NONE;

  /* vpp_ddr ==> LDO5 ==> 2500mV */
  if (BSP_PMIC_WriteReg(board_regulators_table[VPP_DDR].control_reg1, 0x1E) != BSP_ERROR_NONE)
	  return status;

  /* vdd_ddr ==> BUCK6 ==> 1200mV */
  if (BSP_PMIC_WriteReg(board_regulators_table[VDD_DDR].control_reg1, 0x46) != BSP_ERROR_NONE)
	  return status;

  /* vtt_ddr ==> enable flag SINK_SOURCE ==> LDO3 ==> 900mV */
  if (BSP_PMIC_UpdateReg(board_regulators_table[VTT_DDR].control_reg1, 0x80) != BSP_ERROR_NONE)
	  return status;

  /* enable vpp_ddr */
  if (BSP_PMIC_UpdateReg(board_regulators_table[VPP_DDR].control_reg1, 0x1) != BSP_ERROR_NONE)
	  return status;

  HAL_Delay(2);

  /* enable vdd_ddr */
  if (BSP_PMIC_UpdateReg(board_regulators_table[VDD_DDR].control_reg2, 0x1 != BSP_ERROR_NONE))
	  return status;

  /* enable vref_ddr */
  if (BSP_PMIC_UpdateReg(board_regulators_table[VREF_DDR].control_reg1, 0x1 != BSP_ERROR_NONE))
	  return status;

  /* enable vtt_ddr */
  if (BSP_PMIC_UpdateReg(board_regulators_table[VTT_DDR].control_reg1, 0x1) != BSP_ERROR_NONE)
	  return status;

  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
