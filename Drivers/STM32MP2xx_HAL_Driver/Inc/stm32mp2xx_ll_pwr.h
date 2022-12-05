/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_PWR_H
#define STM32MP2xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define WIO_CID_CFG_ADD_OFFSET 0x02u
#define R_CID_CFG_ADD_OFFSET   0x01u
#define WKUPCR_ADD_OFFSET      0x01u
#define REGISTER_ADD_OFFSET    0x01u




/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */
#define LL_PWR_VDDIO              ( (0U<<16) | (0U<<8) | (0U) )
#define LL_PWR_VDDIO3             ( (0U<<16) | (1U<<8) | (0U) )
#define LL_PWR_VDDIO4             ( (0U<<16) | (2U<<8) | (1U) )
#define LL_PWR_USB33              ( (0U<<16) | (2U) )
#define LL_PWR_UCPD               ( (0U<<16) | (3U) )
#define LL_PWR_ADC                ( (0U<<16) | (4U) )
#define LL_PWR_VDDIO1             ( (7U<<16) | (0U) )
#define LL_PWR_VDDIO2             ( (6U<<16) | (0U) )

#define LL_PWR_VRSEL_3V3            0x0u 
#define LL_PWR_VRSEL_1V8            PWR_CR7_VDDIO2VRSEL

#define IS_PWR_SUPPLY(XX) (((XX) == (LL_PWR_VDDIO3))         || ((XX) == (LL_PWR_VDDIO4))  || \
                           ((XX) == (LL_PWR_USB33))          || ((XX) == (LL_PWR_UCPD))    || \
                           ((XX) == (LL_PWR_ADC))            || ((XX) == (LL_PWR_VDDIO1))  || \
                           ((XX) == (LL_PWR_VDDIO))            || ((XX) == (LL_PWR_VDDIO2))     )

#define IS_PWR_SUPPLY_1V8_OPTIMIZATION_CAPABLE(XX) (((XX) == (LL_PWR_VDDIO3))         || ((XX) == (LL_PWR_VDDIO4))      || \
                                                    ((XX) == (LL_PWR_VDDIO))          || ((XX) == (LL_PWR_VDDIO1))      || \
                                                                                         ((XX) == (LL_PWR_VDDIO2))         )

#define IS_PWR_SUPPLY_VRSELRSTBY_CAPABLE(XX) (((XX) == (LL_PWR_VDDIO1))   || ((XX) == (LL_PWR_VDDIO2)))



#define LL_PWR_CPU_RESET   0x0U
#define LL_PWR_CPU_CRUN    0x1U
#define LL_PWR_CPU_CSLEEP  0x2U
#define LL_PWR_CPU_CSTOP   0x3U

#define LL_PWR_DRUN       0x0U
#define LL_PWR_DSTOP1     0x1U
#define LL_PWR_DSTOP2     0x2U
#define LL_PWR_DSTOP3     0x3U
#define LL_PWR_DSTANDBY   0x4U


#define LL_PWR_RUN        0x0U
#define LL_PWR_STOP       0x1U
#define LL_PWR_LP_STOP    0x2U
#define LL_PWR_LPLV_STOP  0x3U
#define LL_PWR_STANDY     0x4U
#define LL_PWR_VBAT       0x5U


#define LL_PWR_SRUN1      0x0U
#define LL_PWR_SRUN2      0x1U
#define LL_PWR_SRUN3      0x2U
#define LL_PWR_SSTOP1     0x3U
#define LL_PWR_SSTOP2     0x4U
#define LL_PWR_SSTANDBY   0x5U




#define LL_PWR_RETRAM_SUPPLY_DISABLE       0U /*RETRAM not powered by backup supply*/
#define LL_PWR_RETRAM_SUPPLY_STBY_VBAT     1U /*RETRAM powered by backup supply in standby and Vbat mode*/
#define LL_PWR_RETRAM_SUPPLY_STBY          2U /*RETRAM powered by backup supply in standby only*/






#define LL_PWR_WAKEUP_PIN_PIN1    0U
#define LL_PWR_WAKEUP_PIN_PIN2    1U
#define LL_PWR_WAKEUP_PIN_PIN3    2U
#define LL_PWR_WAKEUP_PIN_PIN4    3U
#define LL_PWR_WAKEUP_PIN_PIN5    4U
#define LL_PWR_WAKEUP_PIN_PIN6    5U
#define LL_PWR_WAKEUP_PIN_NB      6U


#define LL_PWR_WAKEUP_PIN_NOPULL               0U
#define LL_PWR_WAKEUP_PIN_PULLUP               1U
#define LL_PWR_WAKEUP_PIN_PULLDOWN             2U
#define LL_PWR_WAKEUP_PIN_MAX_PULL_CONFIG      3U

#define    LL_WIO1     LL_PWR_WAKEUP_PIN_PIN1
#define    LL_WIO2     LL_PWR_WAKEUP_PIN_PIN2
#define    LL_WIO3     LL_PWR_WAKEUP_PIN_PIN3
#define    LL_WIO4     LL_PWR_WAKEUP_PIN_PIN4
#define    LL_WIO5     LL_PWR_WAKEUP_PIN_PIN5
#define    LL_WIO6     LL_PWR_WAKEUP_PIN_PIN6

#define    LL_R0                   0U
#define    LL_R1                  (LL_R0 + 1U)
#define    LL_R2                  (LL_R0 + 2U)
#define    LL_R3                  (LL_R0 + 3U)
#define    LL_R4                  (LL_R0 + 4U)
#define    LL_R5                  (LL_R0 + 5U)
#define    LL_R6                  (LL_R0 + 6U)
#define    LL_NS_RESSOURCE_NB      7U

/**
  * @}
  */






/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */



/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable/disable Programable Voltage Detector
  * @rmtoll CR3    PVDEN       LL_PWR_EnablePVD
  * @param None
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_PVDEN);
}
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_PVDEN);
}

/**
  * @brief  Check if Programable Voltage Detector is enabled
  * @rmtoll CR3    PVDEN       LL_PWR_IsEnabledPVD
  * @param None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_PVDEN) == (PWR_CR3_PVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PVD_IN lower than internal REF (PVDO flag set)
  * @rmtoll CR3    PVD0       LL_PWR_IsActiveFlag_PVDO
  * @param None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_PVDO) == (PWR_CR3_PVDO)) ? 1UL : 0UL);
}





/**
  * @brief  Enable/Disable/IsEnable   Monitoring on a power supply
  * @rmtoll CR1/CR7/CR8          LL_PWR_EnableSupplyMonitoring/LL_PWR_DisableSupplyMonitoring/LL_PWR_IsSupplyMonitoringEnabled
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  *         @arg @ref LL_PWR_VDDIO3
  *         @arg @ref LL_PWR_VDDIO4
  *         @arg @ref LL_PWR_USB33
  *         @arg @ref LL_PWR_UCPD
  *         @arg @ref LL_PWR_ADC
  */
__STATIC_INLINE void LL_PWR_EnableSupplyMonitoring(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  SET_BIT(*regaddr, PWR_CR7_VDDIO2VMEN<<(SupplyID&0xFF));
}
__STATIC_INLINE void LL_PWR_DisableSupplyMonitoring(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  CLEAR_BIT(*regaddr, PWR_CR7_VDDIO2VMEN<<(SupplyID&0xFF));
}

__STATIC_INLINE uint32_t LL_PWR_IsSupplyMonitoringEnabled (uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  return ((READ_BIT(*regaddr, PWR_CR7_VDDIO2VMEN<<(SupplyID&0xFF)) == (PWR_CR7_VDDIO2VMEN<<(SupplyID&0xFF))) ? 1UL : 0UL);
}


/**
  * @brief  Check if  supply is ready i.e its voltage equal or greater than internal threshold (flag  ready set)
  * @rmtoll CR0/CR7/CR8            LL_PWR_IsSupplyReady
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  *         @arg @ref LL_PWR_VDDIO3
  *         @arg @ref LL_PWR_VDDIO4
  *         @arg @ref LL_PWR_USB33
  *         @arg @ref LL_PWR_UCPD
  *         @arg @ref LL_PWR_ADC
  * @retval Return true if supply is ready
  */
__STATIC_INLINE uint32_t LL_PWR_IsSupplyReady(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  return ((READ_BIT(*regaddr, PWR_CR7_VDDIO2RDY<<(SupplyID&0xFF)) == (PWR_CR7_VDDIO2RDY<<(SupplyID&0xFF))) ? 1UL : 0UL);
}



/**
  * @brief  Enable/Disable/IsEnable   Validation on a power supply
  * @rmtoll CR1/CR7/CR8          LL_PWR_EnableSupplyValidation/LL_PWR_DisableSupplyValidation/LL_PWR_IsSupplyValidationEnabled
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  *         @arg @ref LL_PWR_VDDIO3
  *         @arg @ref LL_PWR_VDDIO4
  *         @arg @ref LL_PWR_USB33
  *         @arg @ref LL_PWR_UCPD
  *         @arg @ref LL_PWR_ADC
  */
__STATIC_INLINE void LL_PWR_EnableSupplyValidation(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  SET_BIT(*regaddr, PWR_CR7_VDDIO2SV<<(SupplyID&0xFF));
}
__STATIC_INLINE void LL_PWR_DisableSupplyValidation(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  CLEAR_BIT(*regaddr, PWR_CR7_VDDIO2SV<<(SupplyID&0xFF));
}

__STATIC_INLINE uint32_t LL_PWR_IsSupplyValidationEnabled (uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  return ((READ_BIT(*regaddr, PWR_CR7_VDDIO2SV<<(SupplyID&0xFF)) == (PWR_CR7_VDDIO2SV<<(SupplyID&0xFF))) ? 1UL : 0UL);
}


/**
  * @brief  Set   a voltage range selection for a supply
  *         Warning selection of 1V8 is not possible if SoC does not allow it (see fuse-map, HSLV_VDDIOx)
  * @rmtoll CR1/CR7/CR8          LL_PWR_SetVRSEL
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  *         @arg @ref LL_PWR_VDDIO3
  *         @arg @ref LL_PWR_VDDIO4
  * @param  Vrsel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VRSEL_3V3
  *         @arg @ref LL_PWR_VRSEL_1V8
  */
__STATIC_INLINE void LL_PWR_SetVRSEL(uint32_t SupplyID, uint32_t Vrsel)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY_1V8_OPTIMIZATION_CAPABLE(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*((SupplyID>>16)&0xFF));
  MODIFY_REG(*regaddr, PWR_CR7_VDDIO2VRSEL<<((SupplyID>>8)&0xFF), Vrsel<<((SupplyID>>8)&0xFF));

}

/**
  * @brief  get  a voltage range selection for a supply
  * @rmtoll CR1/CR7/CR8          LL_PWR_GetVRSEL
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  *         @arg @ref LL_PWR_VDDIO3
  *         @arg @ref LL_PWR_VDDIO4
  * @retval Supply Range Selection, this output can be one of the following values:
  *         @arg @ref LL_PWR_VRSEL_3V3
  *         @arg @ref LL_PWR_VRSEL_1V8
  */
__STATIC_INLINE uint32_t LL_PWR_GetVRSEL(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY_1V8_OPTIMIZATION_CAPABLE(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*((SupplyID>>16)&0xFF));
  return ( (READ_REG(*regaddr) >> (PWR_CR7_VDDIO2VRSEL_Msk + ( (SupplyID >> 8) & 0xFF))) & 0xFF);

}



/**
  * @brief  Enable/Disable/IsEnableStandbyRangeSelection, request 1.8 voltage in standby and standby exit  on a power supply, when disable voltage is 3.3 in standby or exit standby
  * @rmtoll CR1/CR7/CR8          LL_PWR_EnableVRSELRSTBY/LL_PWR_DisableVRSELRSTBY
  * @param  SupplyID This parameter can be one of the following values:
  *         @arg @ref LL_PWR_VDDIO1
  *         @arg @ref LL_PWR_VDDIO2
  */
__STATIC_INLINE void LL_PWR_EnableVRSELRSTBY(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY_VRSELRSTBY_CAPABLE(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  SET_BIT(*regaddr, PWR_CR7_VDDIO2VRSEL<<(SupplyID&0xFF));
}
__STATIC_INLINE void LL_PWR_DisableVRSELRSTBY(uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY_VRSELRSTBY_CAPABLE(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  CLEAR_BIT(*regaddr, PWR_CR7_VDDIO2VRSEL<<(SupplyID&0xFF));
}

__STATIC_INLINE uint32_t LL_PWR_IsVRSELRSTBYEnabled (uint32_t SupplyID)
{
  __IO uint32_t *regaddr;
  /* Check the parameters */
  assert_param(IS_PWR_SUPPLY_VRSELRSTBY_CAPABLE(SupplyID));

  regaddr = &PWR->CR1 + (REGISTER_ADD_OFFSET*(SupplyID>>16));
  return ((READ_BIT(*regaddr, PWR_CR7_VDDIO2VRSEL<<(SupplyID&0xFF)) == (PWR_CR7_VDDIO2VRSEL<<(SupplyID&0xFF))) ? 1UL : 0UL);
}








/**
  * @brief  Enable/Disable powering of backupRam thru backup regulation during VBat or standby mode
  * @rmtoll CR9    PWR_CR9_BKPRBSEN       LL_PWR_EnableBkUpRamBkUpRegulator/LL_PWR_DisableBkUpRamBkUpRegulator
  * @param None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpRamBkUpRegulator(void)
{
  SET_BIT(PWR->CR9, PWR_CR9_BKPRBSEN);
}
__STATIC_INLINE void LL_PWR_DisableBkUpRamBkUpRegulator(void)
{
  CLEAR_BIT(PWR->CR9, PWR_CR9_BKPRBSEN);
}

/**
  * @brief  return true if  backupRam is powered during VBat or standby mode
  * @rmtoll CR9    PWR_CR9_BKPRBSEN       LL_PWR_IsEnabledBkUpRamBkUpRegulator
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRamBkUpRegulator(void)
{
  return ((READ_BIT(PWR->CR9, PWR_CR9_BKPRBSEN) == (PWR_CR9_BKPRBSEN)) ? 1UL : 0UL);
}


/**
  * @brief  Enable/Disable powering of retram thru backup regulation during VBat and/or standby mode
  * @rmtoll CR10      PWR_CR10_RETRBSEN     LL_PWR_SetRetRamBkUpRegulator/LL_PWR_GetRetRamBkUpRegulator
  * @param  RetentionRamPowerSupplyMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RETRAM_STBY_VBAT i.e RETRAM powered by backup supply in standby and Vbat mode
  *         @arg @ref LL_PWR_RETRAM_STBY      i.e RETRAM powered by backup supply in standby only
  */
__STATIC_INLINE void LL_PWR_SetRetRamBkUpRegulator(uint32_t RetentionRamPowerSupplyMode)
{
  MODIFY_REG(PWR->CR10, PWR_CR10_RETRBSEN, RetentionRamPowerSupplyMode);
}
__STATIC_INLINE uint32_t LL_PWR_GetRetRamBkUpRegulator(void)
{
  return ( (READ_REG(PWR->CR10) & PWR_CR10_RETRBSEN) >> PWR_CR10_RETRBSEN_Pos );
}




/**
  * @brief  Enable/Disable powering of lpsRam1 thru backup regulation during VBat or standby mode
  * @param None
  * @rmtoll CR9    PWR_CR9_LPR1BSEN       LL_PWR_EnableLpsram1BkUpRegulator/LL_PWR_DisableLpsram1BkUpRegulator
  */
__STATIC_INLINE void LL_PWR_EnableLpsram1BkUpRegulator(void)
{
  SET_BIT(PWR->CR9, PWR_CR9_LPR1BSEN);
}
__STATIC_INLINE void LL_PWR_DisableLpsram1BkUpRegulator(void)
{
  CLEAR_BIT(PWR->CR9, PWR_CR9_LPR1BSEN);
}
/**
  * @brief  return true if  lpsRam1 is powered during VBat or standby mode
  * @param None
  * @rmtoll CR9    PWR_CR9_LPR1BSEN       LL_PWR_IsEnabledLpsram1BkUpRegulator
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLpsram1BkUpRegulator(void)
{
  return ((READ_BIT(PWR->CR9, PWR_CR9_LPR1BSEN) == (PWR_CR9_LPR1BSEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable/Disable monitoring of Vbat and temperature
  * @rmtoll CR2    PWR_CR2_MONEN       LL_PWREx_EnableVbatTempMonitoring/LL_PWREx_DisableVbatTempMonitoring
  * @param None
  */
__STATIC_INLINE void LL_PWREx_EnableVbatTempMonitoring(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_MONEN);
}
__STATIC_INLINE void LL_PWREx_DisableVbatTempMonitoring(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_MONEN);
}
/**
  * @brief  return true if  Vbat/Temperature monitoring is enabled
  * @rmtoll CR2    PWR_CR2_MONEN       LL_PWREx_IsEnabledVbatTempMonitoring
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWREx_IsEnabledVbatTempMonitoring(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_MONEN) == (PWR_CR2_MONEN)) ? 1UL : 0UL);
}

/**
  * @brief  return true if temperature level is equal or below low threshold (flag TEMPL set)
  * @rmtoll CR2   TEMPL       LL_PWR_IsActiveFlag_TEMPL
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPL) == (PWR_CR2_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  return true if temperature level is equal or above high threshold (flag TEMPH set)
  * @rmtoll CR2   TEMPH       LL_PWR_IsActiveFlag_TEMPH
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPH) == (PWR_CR2_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  return true if Vbat level is equal or below low threshold (flag VBATL set)
  * @param None
  * @rmtoll CR2   PWR_CR2_VBATL           LL_PWR_IsActiveFlag_VBATL
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATL) == (PWR_CR2_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  return true if Vbat level is equal or above high threshold (flag VBATH set)
  * @rmtoll CR2   PWR_CR2_VBATH       LL_PWR_IsActiveFlag_VBATH
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATH) == (PWR_CR2_VBATH)) ? 1UL : 0UL);
}



/**
  * @brief  Enable/Disable monitoring of VDDcore
  * @rmtoll CR5    PWR_CR5_VCOREMONEN       LL_PWREx_EnableVDDcoreMonitoring/LL_PWREx_DisableVDDcoreMonitoring
  * @param None
  */
__STATIC_INLINE void LL_PWREx_EnableVDDcoreMonitoring(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_VCOREMONEN);
}
__STATIC_INLINE void LL_PWREx_DisableVDDcoreMonitoring(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_VCOREMONEN);
}
/**
  * @brief  return true if VDDcore monitoring is enabled
  * @rmtoll CR5    PWR_CR5_VCOREMONEN       LL_PWREx_IsEnabledVDDcoreMonitoring
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWREx_IsEnabledVDDcoreMonitoring(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_VCOREMONEN) == (PWR_CR5_VCOREMONEN)) ? 1UL : 0UL);
}

/**
  * @brief  return true if VDDcore level is equal or below low threshold (flag VCOREL set)
  * @rmtoll CR5   PWR_CR5_VCOREL  LL_PWR_IsActiveFlag_VCOREL
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VCOREL(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_VCOREL) == (PWR_CR5_VCOREL)) ? 1UL : 0UL);
}

/**
  * @brief  return true if VDDcore level is equal or above high threshold (flag VCOREH set)
  * @rmtoll CR6   PWR_CR5_VCOREH       LL_PWR_IsActiveFlag_VCOREH
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VCOREH(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_VCOREH) == (PWR_CR5_VCOREH)) ? 1UL : 0UL);
}


/**
  * @brief  Enable/Disable monitoring of VDDcpu
  * @rmtoll CR6    PWR_CR6_VCPUMONEN       LL_PWREx_EnableVDDcpuMonitoring/LL_PWREx_DisableVDDcpuMonitoring
  * @param None
  */
__STATIC_INLINE void LL_PWREx_EnableVDDcpuMonitoring(void)
{
  SET_BIT(PWR->CR6, PWR_CR6_VCPUMONEN);
}
__STATIC_INLINE void LL_PWREx_DisableVDDcpuMonitoring(void)
{
  CLEAR_BIT(PWR->CR6, PWR_CR6_VCPUMONEN);
}
/**
  * @brief  return true if VDDcpu monitoring is enabled
  * @rmtoll CR6    PWR_CR6_VCPUMONEN       LL_PWREx_IsEnabledVDDcpuMonitoring
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWREx_IsEnabledVDDcpuMonitoring(void)
{
  return ((READ_BIT(PWR->CR6, PWR_CR6_VCPUMONEN) == (PWR_CR6_VCPUMONEN)) ? 1UL : 0UL);
}


/**
  * @brief  Enable/Disable overdrive  VDDcpu low threshold
  * @rmtoll CR6    PWR_CR6_VCPULLS       LL_PWREx_EnableVDDcpuODriveThreshold/LL_PWREx_DisableVDDcpuODriveThreshold
  * @param None
  */
__STATIC_INLINE void LL_PWREx_EnableVDDcpuODriveThreshold(void)
{
  SET_BIT(PWR->CR6, PWR_CR6_VCPULLS);
}
__STATIC_INLINE void LL_PWREx_DisableVDDcpuODriveThreshold(void)
{
  CLEAR_BIT(PWR->CR6, PWR_CR6_VCPULLS);
}
/**
  * @brief  return true if overdrive  VDDcpu low threshold is enabled
  * @rmtoll CR6    PWR_CR6_VCPULLS       LL_PWREx_IsEnabledVDDcpuMonitoring
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWREx_IsEnabledVDDcpuODriveThreshold(void)
{
  return ((READ_BIT(PWR->CR6, PWR_CR6_VCPULLS) == (PWR_CR6_VCPULLS)) ? 1UL : 0UL);
}





/**
  * @brief  return true if VDDcpu level is equal or below low threshold (flag VCPUL set)
  * @rmtoll CR6   PWR_CR6_VCPUL  LL_PWR_IsActiveFlag_VCPUL
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VCPUL(void)
{
  return ((READ_BIT(PWR->CR6, PWR_CR6_VCPUL) == (PWR_CR6_VCPUL)) ? 1UL : 0UL);
}

/**
  * @brief  return true if VDDcpu level is equal or above high threshold (flag VCPUH set)
  * @rmtoll CR6   PWR_CR6_VCPUH       LL_PWR_IsActiveFlag_VCPUH
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VCPUH(void)
{
  return ((READ_BIT(PWR->CR6, PWR_CR6_VCPUH) == (PWR_CR6_VCPUH)) ? 1UL : 0UL);
}





/**
  * @brief  Enable/Disable monitoring of VDDgpu
  *         Warning, VDDgpu external voltage may need to be set ON before using.
  *         For instance on Valid3 board, SW shall set VDDgpu ON with GPIO-B13 (VDDgpu is ON if GPIO-B13 is high)
  * @rmtoll CR12    PWR_CR12_GPUVMEN       LL_PWR_EnableVDDgpuMonitoring/LL_PWR_DisableVDDgpuMonitoring
  * @param None
  */
__STATIC_INLINE void LL_PWR_EnableVDDgpuMonitoring(void)
{
  SET_BIT(PWR->CR12, PWR_CR12_GPUVMEN);
}
__STATIC_INLINE void LL_PWR_DisableVDDgpuMonitoring(void)
{
  CLEAR_BIT(PWR->CR12, PWR_CR12_GPUVMEN);
}
/**
  * @brief  return true if VDDgpu monitoring is enabled
  * @rmtoll CR12   PWR_CR12_GPUVMEN       LL_PWR_IsVDDgpuMonitoringEnabled
  *         Warning, VDDgpu external voltage may need to be set ON before using.
  *         For instance on Valid3 board, SW shall set VDDgpu ON with GPIO-B13 (VDDgpu is ON if GPIO-B13 is high)
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsVDDgpuMonitoringEnabled(void)
{
  return ((READ_BIT(PWR->CR12, PWR_CR12_GPUVMEN) == (PWR_CR12_GPUVMEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable/Disable  VDDgpu low threshold
  * @rmtoll CR12    PWR_CR12_GPULVTEN       LL_PWR_EnableVDDgpuLowThreshold/LL_PWR_DisableVDDgpuLowThreshold
  * @param None
  */
__STATIC_INLINE void LL_PWR_EnableVDDgpuLowThreshold(void)
{
  SET_BIT(PWR->CR12, PWR_CR12_GPULVTEN);
}
__STATIC_INLINE void LL_PWR_DisableVDDgpuLowThreshold(void)
{
  CLEAR_BIT(PWR->CR12, PWR_CR12_GPULVTEN);
}
/**
  * @brief  return true if VDDgpu low Threshold is enabled
  * @rmtoll CR12   PWR_CR12_GPULVTEN       LL_PWR_IsEnabledVDDgpuThreshold
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledVDDgpuLowThreshold(void)
{
  return ((READ_BIT(PWR->CR12, PWR_CR12_GPULVTEN) == (PWR_CR12_GPULVTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable/Disable  VDDgpu independant supply valid (present)
  * @rmtoll PWR_CR12   UCPDR    LL_PWR_EnableVDDgpuSupplyValidation/LL_PWR_DisableVDDgpuSupplyValidation
  * @param None
  */
__STATIC_INLINE void LL_PWR_EnableVDDgpuValidation(void)
{
  SET_BIT(PWR->CR12, PWR_CR12_GPUSV);
}
__STATIC_INLINE void LL_PWR_DisableVDDgpuValidation(void)
{
  CLEAR_BIT(PWR->CR12, PWR_CR12_GPUSV);
}
/**
  * @brief  return true if VDDgpu independant supply  valid (present) is enabled
  * @rmtoll CR12   PWR_CR12_GPUSV       LL_PWR_IsVDDgpuSupplyValidationEnabled
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsVDDgpuValidationEnabled(void)
{
  return ((READ_BIT(PWR->CR12, PWR_CR12_GPUSV) == (PWR_CR12_GPUSV)) ? 1UL : 0UL);
}

/**
  * @brief  return true if VDDgpu is equal or below threshold (flag VDDGPURDY set)
  * @note   irrelevant if no threshold enabled
  * @rmtoll CR12   PWR_CR12_VDDGPURDY       LL_PWR_IsVDDgpuSupplyReady
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsVDDgpuReady(void)
{
  return ((READ_BIT(PWR->CR12, PWR_CR12_VDDGPURDY) == (PWR_CR12_VDDGPURDY)) ? 1UL : 0UL);
}


/**
  * @brief  Enable/Disable USB type C  dead battery pull down behavior on UCPDx_CC1/UCPDx_CC2
  * @rmtoll UCPDR    LL_PWR_IsEnabledDeadBattPullD       LL_PWR_EnableDeadBattPullD/LL_PWR_DisableDeadBattPullD
  * @param None
  */
__STATIC_INLINE void LL_PWR_EnableDeadBattPullD(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_DBDIS);
}
__STATIC_INLINE void LL_PWR_DisableDeadBattPullD(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_DBDIS);
}
/**
  * @brief  return true if USB type C  dead battery pull down behavior on UCPDx_CC1/UCPDx_CC2 is enabled
  * @rmtoll UCPDR   LL_PWR_IsEnabledDeadBattPullD       LL_PWR_IsEnabledDeadBattPullD
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledDeadBattPullD(void)
{
  return ((READ_BIT(PWR->UCPDR, PWR_UCPDR_DBDIS) == (PWR_UCPDR_DBDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set/Get  memorization of configuration of UCPD dead battery pull down behavio when in standby
  * @rmtoll UCPDR           LL_PWR_SetUcpdConfigMemorization/LL_PWR_GetUcpdConfigMemorization
  * @param  configuration : 1 memorize UCPD configuration in standby / 0 lost UCPD configuration in standby
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetUcpdConfigMemorization(uint32_t configuration)
{
  MODIFY_REG(PWR->UCPDR, PWR_UCPDR_STBY, configuration << PWR_UCPDR_STBY_Pos);
}
__STATIC_INLINE uint32_t LL_PWR_GetUcpdConfigMemorization(void)
{
  return ( (READ_REG(PWR->UCPDR) & PWR_UCPDR_STBY) >> PWR_UCPDR_STBY_Pos );
}


#if !defined(CORE_CM0PLUS)
/**
  * @brief  Enable/Disable W access to D3 and backup  ressources
  * @rmtoll BDCR1          LL_PWR_EnableBkUpD3Access/LL_PWR_DisableBkUpD3Access
  * @param  none
  */
__STATIC_INLINE void LL_PWR_EnableBkUpD3Access(void)
{
  SET_BIT(PWR->BDCR1, PWR_BDCR1_DBD3P);
}
__STATIC_INLINE void LL_PWR_DisableBkUpD3Access(void)
{
  CLEAR_BIT(PWR->BDCR1, PWR_BDCR1_DBD3P);
}

/**
  * @brief  return true if W access to D3 and backup domain is enabled
  * @rmtoll BDCR1          LL_PWR_IsEnabledBkUpD3Access
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpD3Access(void)
{
  return ((READ_BIT(PWR->BDCR1, PWR_BDCR1_DBD3P) == (PWR_BDCR1_DBD3P)) ? 1UL : 0UL);
}
#endif /*!defined(CORE_CM0PLUS)*/


#if defined(CORE_CM0PLUS)
/**
  * @brief  Enable/Disable W access to backup  ressources
  * @rmtoll BDCR2          LL_PWR_EnableBkUpAccess/LL_PWR_DisableBkUpAccess
  * @param  none
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->BDCR2, PWR_BDCR2_DBP);
}
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->BDCR2, PWR_BDCR2_DBP);
}

/**
  * @brief  return true if W access to backup domain is enabled
  * @rmtoll BDCR2          LL_PWR_IsEnabledBkUpAccess
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->BDCR2, PWR_BDCR2_DBP) == (PWR_BDCR2_DBP)) ? 1UL : 0UL);
}
#endif /*!defined(CORE_CM0PLUS)*/



#if !defined(CORE_CM0PLUS)
/**
  * @brief  Set/Get minimun guarantee duration of PWR_CPU_ON low pulse in DStandby
  * @rmtoll D1CR          LL_PWR_SetPwrCpuOnLowPulseDuration/LL_PWR_GetPwrCpuOnLowPulseDuration
  * @param  duration
  * @arg @ref 00000 no duration guarantee
  * @arg @ref 00001 1*32LSI-cycle duration guaranteed
  * @arg @ref 00010 2*32LSI-cycle duration guaranteed
  * @arg @ref ..... duration guaranteed
  * @arg @ref 11111 31*32LSI-cycle duration guaranteed

  */
__STATIC_INLINE void LL_PWR_SetPwrCpuOnLowPulseDuration(uint32_t duration)
{
  MODIFY_REG(PWR->D1CR, PWR_D1CR_POPL_D1, duration << PWR_D1CR_POPL_D1_Pos);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPwrCpuOnLowPulseDuration(void)
{
  return ( (READ_REG(PWR->D1CR) & (PWR_D1CR_POPL_D1)) >> PWR_D1CR_POPL_D1_Pos) ;
}


/**
  * @brief  Set/Get PWR_CPU_ON configuration
  * @rmtoll D1CR          LL_PWR_SetPwrCpuOnConfig/LL_PWR_GetPwrCpuOnConfig
  * @param  configuration
  * @arg @ref 0 PWR_CPU_ON is low only in DStandby
  * @arg @ref 1 PWR_CPU_ON is low only in DStandby and DStop2/3

  */
__STATIC_INLINE void LL_PWR_SetPwrCpuOnConfig(uint32_t configuration)
{
  MODIFY_REG(PWR->D1CR, PWR_D1CR_LPCFG_D1, configuration);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPwrCpuOnConfig(void)
{
  return ( (READ_REG(PWR->D1CR) & (PWR_D1CR_LPCFG_D1)) );
}



/**
  * @brief  Set/Get  the delay to maintain  PWR_ON High when entering  in DStandby
  * @rmtoll D2CR          LL_PWR_SetPwrOnHighDelay/LL_PWR_GetPwrOnHighDelay
  * @param  delay
  * @arg @ref 00000 no delay  observed
  * @arg @ref 00001 1*32LSI-cycle delay  observed
  * @arg @ref 00010 2*32LSI-cycle delay  observed
  * @arg @ref ..... delay  observed
  * @arg @ref 11111 31*32LSI-cycle delay  observed

  */
__STATIC_INLINE void LL_PWR_SetPwrOnHighDelay(uint32_t delay)
{
  MODIFY_REG(PWR->D2CR, PWR_D2CR_PODH_D2, delay << PWR_D2CR_PODH_D2_Pos);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPwrOnHighDelay(void)
{
  return ( (READ_REG(PWR->D2CR) & (PWR_D2CR_PODH_D2)) >> PWR_D2CR_PODH_D2_Pos) ;
}

/**
  * @brief  Set/Get  the minimun delay to be observed before activation of PLLs after one of the LPLV system Stop
  * @rmtoll D2CR          LL_PWR_SetPllLpLvStopDelay/LL_PWR_GetPllLpLvStopDelay
  * @param  delay
  * @arg @ref 00000 no delay  observed
  * @arg @ref 00001 1*6LSI-cycle delay  observed
  * @arg @ref 00010 2*6LSI-cycle delay  observed
  * @arg @ref ..... delay  observed
  * @arg @ref 11111 31*6LSI-cycle delay  observed

  */
__STATIC_INLINE void LL_PWR_SetPllLpLvStopDelay(uint32_t delay)
{
  MODIFY_REG(PWR->D2CR, PWR_D2CR_LPLVDLY_D2, delay << PWR_D2CR_LPLVDLY_D2_Pos);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPllLpLvStopDelay(void)
{
  return ( (READ_REG(PWR->D2CR) & (PWR_D2CR_LPLVDLY_D2)) >> PWR_D2CR_LPLVDLY_D2_Pos) ;
}

/**
  * @brief  Set/Get minimun guarantee duration of PWR_ON low pulse in DStandby
  * @rmtoll D2CR          LL_PWR_SetPwrOnLowPulseDuration/LL_PWR_GetPwrOnLowPulseDuration
  * @param  duration
  * @arg @ref 00000 no duration guarantee
  * @arg @ref 00001 1*32LSI-cycle duration guaranteed
  * @arg @ref 00010 2*32LSI-cycle duration guaranteed
  * @arg @ref ..... duration guaranteed
  * @arg @ref 11111 31*32LSI-cycle duration guaranteed

  */
__STATIC_INLINE void LL_PWR_SetPwrOnLowPulseDuration(uint32_t duration)
{
  MODIFY_REG(PWR->D2CR, PWR_D2CR_POPL_D2, duration << PWR_D2CR_POPL_D2_Pos);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPwrOnLowPulseDuration(void)
{
  return ( (READ_REG(PWR->D2CR) & (PWR_D2CR_POPL_D2)) >> PWR_D2CR_POPL_D2_Pos) ;
}


/**
  * @brief  Set/Get PWR_ON configuration
  * @rmtoll D2CR          LL_PWR_SetPwrOnConfig/LL_PWR_GetPwrOnConfig
  * @param  configuration
  * @arg @ref 0 PWR_ON is low only in Standby1/2
  * @arg @ref 1 PWR_ON is low only in Standby1/2 and LPLV-Stop1/2 and Stop1/2

  */
__STATIC_INLINE void LL_PWR_SetPwrOnConfig(uint32_t configuration)
{
  MODIFY_REG(PWR->D2CR, PWR_D2CR_LPCFG_D2, configuration);
}
__STATIC_INLINE uint32_t  LL_PWR_GetPwrOnConfig(void)
{
  return  ((READ_REG(PWR->D2CR)) & (PWR_D2CR_LPCFG_D2)) ;
}
#endif /*!defined(CORE_CM0PLUS)*/




/**
  * @}
  */



/** @defgroup PWR_LL_EF_PwrState PwrState
  * @{
  */



/**
  * @brief  Allow/Deny D1 domain to enter standby when CPU1 enters Cstop
  * @rmtoll CPU1CR           LL_PWR_CPU1_AllowD1standby/LL_PWR_CPU1_DenyD1standby
  * @param None
  */
__STATIC_INLINE void LL_PWR_CPU1_AllowD1standby(void)
{
  SET_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D1);
}
__STATIC_INLINE void LL_PWR_CPU1_DenyD1standby(void)
{
  CLEAR_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D1);
}

/**
  * @brief  return true if CPU1 allows D1 standby when entering in Cstop
  * @rmtoll CPU1CR          LL_PWR_IsAllowedCPU1D1standby
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsAllowedCPU1D1standby(void)
{
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D1) == (PWR_CPU1CR_PDDS_D1)) ? 1UL : 0UL);
}

/**
  * @brief  Allow/Deny D2 domain to enter standby when CPU1 enters Cstop
  * @rmtoll CPU1CR           LL_PWR_CPU1_AllowD2standby/LL_PWR_CPU1_DenyD2standby
  * @param None
  */
__STATIC_INLINE void LL_PWR_CPU1_AllowD2standby(void)
{
  SET_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D2);
}
__STATIC_INLINE void LL_PWR_CPU1_DenyD2standby(void)
{
  CLEAR_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D2);
}

/**
  * @brief  return true if CPU1 allows D2 standby when entering in Cstop
  * @rmtoll CPU1CR          LL_PWR_IsAllowedCPU1D2standby
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsAllowedCPU1D2standby(void)
{
  return (READ_BIT(PWR->CPU1CR, PWR_CPU1CR_PDDS_D2) == (PWR_CPU1CR_PDDS_D2) ? 1UL : 0UL);
}



/**
  * @brief  Allow/Deny D2 domain to enter standby when CPU2 enters Cstop
  * @rmtoll CPU2CR           LL_PWR_CPU2_AllowD2standby/LL_PWR_CPU2_DenyD2standby
  * @param None
  */
__STATIC_INLINE void LL_PWR_CPU2_AllowD2standby(void)
{
  SET_BIT(PWR->CPU2CR, PWR_CPU1CR_PDDS_D2);
}
__STATIC_INLINE void LL_PWR_CPU2_DenyD2standby(void)
{
  CLEAR_BIT(PWR->CPU2CR, PWR_CPU1CR_PDDS_D2);
}


/**
  * @brief  return true if CPU2 allows D2 standby when entering in Cstop
  * @rmtoll CPU2CR          LL_PWR_IsAllowedCPU2D2standby
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsAllowedCPU2D2standby(void)
{
  return (READ_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D2) == (PWR_CPU2CR_PDDS_D2) ? 1UL : 0UL);
}


/**
  * @brief  Allow/Deny D3 domain to enter standby when system  enters standby
  * @rmtoll CPU2CR           LL_PWR_AllowD3standby/LL_PWR_DenyD3standby
  * @param None
  */
__STATIC_INLINE void LL_PWR_AllowD3standby(void)
{
  SET_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3);
}
__STATIC_INLINE void LL_PWR_DenyD3standby(void)
{
  CLEAR_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3);
}

/**
  * @brief  return true if D3 standby allowed
  * @rmtoll D3CR          LL_PWR_IsAllowedD3standby
  * @param None
  * @retval boolean
  */
__STATIC_INLINE uint32_t LL_PWR_IsAllowedD3standby(void)
{
  return (READ_BIT(PWR->D3CR, PWR_D3CR_PDDS_D3) == (PWR_D3CR_PDDS_D3) ? 1UL : 0UL);
}

/**
  * @brief  Check if D3 supply is ready
  * @rmtoll D3CR            LL_PWR_IsActiveFlag_D3RDY
  * @param None
  * @retval Return true if D3 supply is ready
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_D3RDY(void)
{
  return ((READ_BIT(PWR->D3CR, PWR_D3CR_D3RDY) == PWR_D3CR_D3RDY) ? 1UL : 0UL);
}

/**
  * @brief  return true if CPU#i is in CRUn or CSleep state
  * @rmtoll CPU1CR/CPU2CR/CPU3CR           LL_PWR_Is_CPU1_Active/LL_PWR_Is_CPU2_Active/LL_PWR_Is_CPU3_Active
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_Is_CPU1_Active(void)
{
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_STANDBYWFIL2) == (PWR_CPU1CR_STANDBYWFIL2)) ? 0UL : 1UL);
}
__STATIC_INLINE uint32_t LL_PWR_Is_CPU2_Active(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_DEEPSLEEP) == (PWR_CPU2CR_DEEPSLEEP)) ? 0UL : 1UL);
}
__STATIC_INLINE uint32_t LL_PWR_Is_CPU3_Active(void)
{
  return ((READ_BIT(PWR->CPU3CR, PWR_CPU3CR_DEEPSLEEP) == (PWR_CPU3CR_DEEPSLEEP)) ? 0UL : 1UL);
}

/**
  * @brief  return  CPU#i state
  * @param None
  * @note  CPU state can be one of the following values:
  *   LL_PWR_CPU_RESET
  *   LL_PWR_CPU_CRUN
  *   LL_PWR_CPU_CSLEEP
  *   LL_PWR_CPU_CSTOP
  * @rmtoll CPU1D1SR/CPU2D2SR/CPU3D3SR           LL_PWR_CPU1State/LL_PWR_CPU2State/LL_PWR_CPU3State
  */
__STATIC_INLINE uint32_t LL_PWR_CPU1State(void)
{
  return ( (READ_REG(PWR->CPU1D1SR) & PWR_CPU1D1SR_CSTATE) >> PWR_CPU1D1SR_CSTATE_Pos );
}
__STATIC_INLINE uint32_t LL_PWR_CPU2State(void)
{
  return ( (READ_REG(PWR->CPU2D2SR) & PWR_CPU2D2SR_CSTATE) >> PWR_CPU2D2SR_CSTATE_Pos );
}
__STATIC_INLINE uint32_t LL_PWR_CPU3State(void)
{
  return ( (READ_REG(PWR->CPU3D3SR) & PWR_CPU3D3SR_CSTATE) >> PWR_CPU3D3SR_CSTATE_Pos );
}

/**
  * @brief  return  D1 state
  * @param None
  * @note  D1 state can be one of the following values:
  * LL_PWR_DRUN
  * LL_PWR_DSTOP1
  * LL_PWR_DSTOP2
  * LL_PWR_DSTOP3
  * LL_PWR_DSTANDBY
  * @rmtoll CPU1D1SR           LL_PWR_D1State
  */
__STATIC_INLINE uint32_t LL_PWR_D1State(void)
{
  return ( (READ_REG(PWR->CPU1D1SR) & PWR_CPU1D1SR_DSTATE) >> PWR_CPU1D1SR_DSTATE_Pos );
}

/**
  * @brief  return  D2 state
  * @param None
  * @note  D2 state can be one of the following values:
  * LL_PWR_RUN
  * LL_PWR_STOP
  * LL_PWR_LP_STOP
  * LL_PWR_LPLV_STOP
  * LL_PWR_STANDBY
  * LL_PWR_VBAT
  * @rmtoll CPU2D2SR           LL_PWR_D2State
  */
__STATIC_INLINE uint32_t LL_PWR_D2State(void)
{
  return ( (READ_REG(PWR->CPU2D2SR) & PWR_CPU2D2SR_DSTATE) >> PWR_CPU2D2SR_DSTATE_Pos );
}

/**
  * @brief  return  D3 state
  * @param None
  * @note  D3 state can be one of the following values:
  * LL_PWR_SRUN1
  * LL_PWR_SRUN2
  * LL_PWR_SRUN3
  * LL_PWR_SSTOP1
  * LL_PWR_SSTOP2
  * LL_PWR_SSTANDBY
  * @rmtoll CPU3D3SR           LL_PWR_D3State
  */
__STATIC_INLINE uint32_t LL_PWR_D3State(void)
{
  return ( (READ_REG(PWR->CPU3D3SR) & PWR_CPU3D3SR_DSTATE) >> PWR_CPU3D3SR_DSTATE_Pos );
}



/**
  * @brief  return  true when domain D#i has been is standby
  * @param None
  * @note  shall be cleared by SW before D#i re-enters standby (note done by HW)
  * @rmtoll CPU1CR/CPU2CR/CPU3CR           LL_PWR_HasD1BeenInStandby/LL_PWR_HasD2BeenInStandby/LL_PWR_HasD3BeenInStandby
  */
__STATIC_INLINE uint32_t LL_PWR_HasD1BeenInStandby(void)
{
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_SBF_D1) == (PWR_CPU1CR_SBF_D1)) ? 1UL : 0UL);
}
__STATIC_INLINE uint32_t LL_PWR_HasD2BeenInStandby(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF_D2) == (PWR_CPU2CR_SBF_D2)) ? 1UL : 0UL);
}
__STATIC_INLINE uint32_t LL_PWR_HasD3BeenInStandby(void)
{
#if defined(CORE_CA35)
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_SBF_D3) == (PWR_CPU1CR_SBF_D3)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM33)
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF_D3) == (PWR_CPU2CR_SBF_D3)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM0PLUS)
  return ((READ_BIT(PWR->CPU3CR, PWR_CPU3CR_SBF_D3) == (PWR_CPU3CR_SBF_D3)) ? 1UL : 0UL);
#endif
}


#if defined(CORE_CM33)||defined(CORE_CA35)
/**
  * @brief  return  true when system has been is stop
  * @note  shall be cleared by SW before system re-enters stop (note done by HW)
  * @rmtoll CPU1CR/CPU2CR          LL_PWR_HasSystemBeenInStandby
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_HasSystemBeenInStop(void)
{
#if defined(CORE_CA35)
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_STOPF) == (PWR_CPU1CR_STOPF)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM33)
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_STOPF) == (PWR_CPU2CR_STOPF)) ? 1UL : 0UL);
#endif

}

/**
  * @brief  return  true when system has been is standby
  * @note  shall be cleared by SW before system re-enters standby (note done by HW)
  * @rmtoll CPU1CR/CPU2CR          LL_PWR_HasSystemBeenInStandby
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_HasSystemBeenInStandby(void)
{
#if defined(CORE_CA35)
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_SBF) == (PWR_CPU1CR_SBF)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM33)
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF) == (PWR_CPU2CR_SBF)) ? 1UL : 0UL);
#endif
}
#endif /*defined(CORE_CM33)||defined(CORE_CA35)*/

/**
  * @brief  return  true when system has been is vbat
  * @note  shall be cleared by SW before system re-enters vbat (note done by HW)
  * @rmtoll CPU1CR/CPU2CR/CPU3CR           LL_PWR_HasSystemBeenInVBAT
  * @param None
  */
__STATIC_INLINE uint32_t LL_PWR_HasSystemBeenInVBAT(void)
{
#if defined(CORE_CA35)
  return ((READ_BIT(PWR->CPU1CR, PWR_CPU1CR_VBF) == (PWR_CPU1CR_VBF)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM33)
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_VBF) == (PWR_CPU2CR_VBF)) ? 1UL : 0UL);
#endif
#if defined(CORE_CM0PLUS)
  return ((READ_BIT(PWR->CPU3CR, PWR_CPU3CR_VBF) == (PWR_CPU3CR_VBF)) ? 1UL : 0UL);
#endif
}

/**
  * @}
  */



/** @defgroup PWR_LL_EF_LpWkUp LpWkUp
  * @{
  */


/**
  * @brief  Enable/Disable CPU1/CPU2 power wakeup line
  * @rmtoll WKUPCRx          LL_PWR_EnableCPU1WakeUpPin/LL_PWR_DisableCPU1WakeUpPin/LL_PWR_EnableCPU2WakeUpPin/LL_PWR_DisableCPU2WakeUpPin
  * @param  WakeUpPinx This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN6
  */
__STATIC_INLINE void LL_PWR_EnableCPU1WakeUpPin(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  SET_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU1);                                      /* Enable  WKUP pinx interruption  CPU1 */
}
__STATIC_INLINE void LL_PWR_DisableCPU1WakeUpPin(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  CLEAR_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU1);                                    /* Disable  WKUP pinx interruption  CPU1 */
}
__STATIC_INLINE void LL_PWR_EnableCPU2WakeUpPin(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  SET_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU2);                                      /* Enable  WKUP pinx interruption  CPU2 */
}
__STATIC_INLINE void LL_PWR_DisableCPU2WakeUpPin(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  CLEAR_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU2);                                    /* Disable  WKUP pinx interruption  CPU2 */
}



/**
  * @brief  return  true when a pwr wake-up line is configured to wake-up CPU1 or CPU2
  * @note  shall be cleared by SW before system re-enters stop (note done by HW)
  * @rmtoll WKUPCRx          LL_PWR_IsCPU1WakeUpCapable/LL_PWR_IsCPU2WakeUpCapable
  * @param  WakeUpPinx This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN6
  */
__STATIC_INLINE uint32_t LL_PWR_IsCPU1WakeUpCapable(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  return ((READ_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU1) == (PWR_WKUPCR1_WKUPENCPU1)) ? 1UL : 0UL);
}
__STATIC_INLINE uint32_t LL_PWR_IsCPU2WakeUpCapable(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  return ((READ_BIT(*regaddr, PWR_WKUPCR1_WKUPENCPU2) == (PWR_WKUPCR1_WKUPENCPU2)) ? 1UL : 0UL);
}


/**
  * @brief  Set/Get  polarity of a wakeup pin
  * @rmtoll WKUPCRx          LL_PWR_SetWakeUpPinPolarityLow/LL_PWR_SetWakeUpPinPolarityHigh/LL_PWR_IsEnabledWakeUpPinPolarityLow
  * @param  WakeUpPinx This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN_PIN6
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  SET_BIT(*regaddr, PWR_WKUPCR1_WKUPP);
}
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  CLEAR_BIT(*regaddr, PWR_WKUPCR1_WKUPP);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPinPolarityLow(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  return ((READ_BIT(*regaddr, PWR_WKUPCR1_WKUPP) == PWR_WKUPCR1_WKUPP) ? 1UL : 0UL);
}

/**
  * @brief  Set/Get  pull configuration of a wakeup pin
  * @rmtoll WKUPCRx          LL_PWR_SetWakeUpPinPullConfig/LL_PWR_GetWakeUpPinPullConfig
  * @param  WakeUpPinx This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_NOPULL
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLUP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLDOWN

  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullConfig(uint32_t WakeUpPinx, uint32_t PullConfig)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  MODIFY_REG(*regaddr, PWR_WKUPCR1_WKUPPUPD, PullConfig << PWR_WKUPCR1_WKUPPUPD_Pos);
}


__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPullConfig(uint32_t WakeUpPinx)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WKUPCR1 + (WKUPCR_ADD_OFFSET*WakeUpPinx);                       /* Selected register corresponding to input wakeup line*/
  return ( (READ_REG(*regaddr) & (PWR_WKUPCR1_WKUPPUPD)) >> PWR_WKUPCR1_WKUPPUPD_Pos) ;
}


#if !defined(CORE_CM0PLUS)
/**
  * @brief  Enable/Disable  D3 wake-up from VBat thru external TAMPER
  * @rmtoll D3WKUPENR          LL_PWR_EnableD3WkUpTamper/LL_PWR_DisableD3WkUpTamper
  * @param  none
  */
__STATIC_INLINE void LL_PWR_EnableD3WkUpTamper(void)
{
  SET_BIT(PWR->D3WKUPENR, PWR_D3WKUPENR_TAMP_WKUPEN_D3);
}
__STATIC_INLINE void LL_PWR_DisableD3WkUpTamper(void)
{
  CLEAR_BIT(PWR->D3WKUPENR, PWR_D3WKUPENR_TAMP_WKUPEN_D3);
}

/**
  * @brief  Check if D3 wake-up from VBat thru external TAMPER is set
  * @rmtoll D3WKUPENR          LL_PWR_IsEnabledD3WkUpTamper
  * @param  none
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledD3WkUpTamper(void)
{
  return  (READ_BIT(PWR->D3WKUPENR, PWR_D3WKUPENR_TAMP_WKUPEN_D3) == PWR_D3WKUPENR_TAMP_WKUPEN_D3) ;
}

#endif /*!defined(CORE_CM0PLUS)*/


/**
  * @}
  */



/** @defgroup PWR_LL_EF_Rif Rif
  * @{
  */


/*                           non sharable  ressource   RIF management                   */


/**
  * @brief  Set/Get secure attribute  to access  a or several non sharable ressource(s)
  * @rmtoll RSECCFGR          LL_PWR_ConfigSecureNSharable/LL_PWR_GetConfigSecureNSharable
  * @param  SecureConfig : bit map of non sharable ressource  : bit_k set if configuration applies on non sharable ressource k , k  in LL_R0 .. LL_R6
  */
__STATIC_INLINE void LL_PWR_ConfigSecureNSharable(uint32_t SecureConfig)
{
  WRITE_REG(PWR->RSECCFGR, SecureConfig);
}
__STATIC_INLINE uint32_t LL_PWR_GetConfigSecureNSharable(void)
{
  return (READ_REG(PWR->RSECCFGR));
}


/**
  * @brief  Set/Get privilege attribute  to access  a or several non sharable ressource(s)
  * @rmtoll RPRIVCFGR          LL_PWR_ConfigPrivilegeNSharable/LL_PWR_GetConfigPrivilegeNSharable
  * @param  PrivilegeConfig : bit map of non sharable ressource  : bit_k set if configuration applies on non sharable ressource k , k  in LL_R0 .. LL_R6
  */
__STATIC_INLINE void LL_PWR_ConfigPrivilegeNSharable(uint32_t PrivilegeConfig)
{
  WRITE_REG(PWR->RPRIVCFGR, PrivilegeConfig);
}
__STATIC_INLINE uint32_t LL_PWR_GetConfigPrivilegeNSharable(void)
{
  return (READ_REG(PWR->RPRIVCFGR));
}


/**
  * @brief  Set  authorised  CID for  accessing a non sharable ressource
  * @note relevant only in case of  CID filtering active on input ressource
  * @rmtoll RxCIDCFGR          LL_PWR_setAuthorisedCidNSharable
  * @param  nsRessource : R ressource number  LL_R0 .. LL_R7
  * @param  cid : authorised cid value   0 .. 7
  */
__STATIC_INLINE void LL_PWR_SetAuthorisedCidNSharable(uint16_t nsRessource, uint16_t cid)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET*nsRessource);
  MODIFY_REG(*regaddr, PWR_R0CIDCFGR_CID, cid << PWR_R0CIDCFGR_CID_Pos);
}


/**
  * @brief  Get  authorised  CID for  accessing a non sharable ressource
  * @note relevant only in case of  CID filtering active on input ressource
  * @rmtoll RxCIDCFGR          LL_PWR_getAuthorisedCidNSharable
  * @param  nsRessource : R ressource number  LL_R0 .. LL_R7
  * @retval cid  0 .. 7
  */
__STATIC_INLINE uint32_t LL_PWR_GetAuthorisedCidNSharable(uint16_t nsRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET*nsRessource);
  return ( (READ_REG(*regaddr) & (PWR_R0CIDCFGR_CID)) >> PWR_R0CIDCFGR_CID_Pos) ;
}


/**
  * @brief  Enable/Disable  CID filtering  to  control non sharable ressource access
  * @rmtoll RxCIDCFGR          LL_PWR_EnableCidFilteringNsRessource/LL_PWR_DisableCidFilteringNsRessource
  * @param  nsRessource : R ressource number  LL_R0 .. LL_R7
  */
__STATIC_INLINE void LL_PWR_EnableCidFilteringNSharable(uint16_t nsRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET*nsRessource);
  SET_BIT(*regaddr, PWR_R0CIDCFGR_CFEN);
}
__STATIC_INLINE void LL_PWR_DisableCidFilteringNSharable(uint16_t nsRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET*nsRessource);
  CLEAR_BIT(*regaddr, PWR_R0CIDCFGR_CFEN);
}

/**
  * @brief  Check if CID filtering  to  control non sharable ressource access is enabled.
  * @rmtoll RxCIDCFGR              LL_PWR_IsCidFilteringNSharableEnabled
  * @param  nsRessource : R ressource number  LL_R0 .. LL_R7
  * @retval true is semaphore enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsCidFilteringNSharableEnabled(uint16_t nsRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->RxCIDCFGR[0] + (R_CID_CFG_ADD_OFFSET*nsRessource);
  return ((READ_BIT(*regaddr, PWR_R0CIDCFGR_CFEN) == PWR_R0CIDCFGR_CFEN) ? 1UL : 0UL);
}

/*                           WAKE-UP ressource   RIF management   */

/**
  * @brief  Set/Get secure attribute  to access  a or several Wakeup ressource(s)
  * @rmtoll WIOSECCFGR          LL_PWR_ConfigSecureWakeUp/LL_PWR_GetConfigSecureWakeUpvoid
  * @param  SecureConfig : bit map of wakeup ressource  : bit_k set if configuration applies on wakeup ressource k+1 , k  in LL_WIO1 .. LL_WIO6
  */
__STATIC_INLINE void LL_PWR_ConfigSecureWakeUp(uint32_t SecureConfig)
{
  WRITE_REG(PWR->WIOSECCFGR, SecureConfig);
}
__STATIC_INLINE uint32_t LL_PWR_GetConfigSecureWakeUp(void)
{
  return (READ_REG(PWR->WIOSECCFGR));
}



/**
  * @brief  Set/Get privilege attribute filtering to access  a or several Wakeup ressource(s)
  * @rmtoll WIOPRIVCFGR          LL_PWR_ConfigPrivilegeWakeUp/LL_PWR_GetConfigPrivilegeWakeUp
  * @param  PrivilegeConfig : bit map of wakeup ressource  : bit_k set if configuration applies on wakeup ressource k+1 , k  in LL_WIO1 .. LL_WIO6
  */
 __STATIC_INLINE void LL_PWR_ConfigPrivilegeWakeUp(uint32_t PrivilegeConfig)
{
  WRITE_REG(PWR->WIOPRIVCFGR, PrivilegeConfig);
}
__STATIC_INLINE uint32_t LL_PWR_GetConfigPrivilegeWakeUp(void)
{
  return (READ_REG(PWR->WIOPRIVCFGR));
}


/**
  * @brief  Set  authorised static CID for  accessing a Wakeup ressource
  * @note relevant only in case of  CID filtering active on input ressource and no semaphore enabled on it
  * @rmtoll WIOxCIDCFGR          LL_PWR_SetAuthorisedStaticCidWakeUp
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @param  cid : authorised cid value   0 .. 7
  */
__STATIC_INLINE void LL_PWR_SetAuthorisedStaticCidWakeUp(uint16_t wkRessource, uint16_t cid)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  MODIFY_REG(*regaddr, PWR_WIO1CIDCFGR_SCID, cid << PWR_WIO1CIDCFGR_SCID_Pos);
}


/**
  * @brief  Get  authorised  static CID for  accessing a Wakeup ressource
  * @note relevant only in case of  CID filtering active on input ressource and no semaphore enabled on it
  * @rmtoll WIOxCIDCFGR          LL_PWR_GetAuthorisedStaticCidWakeUp
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @retval cid  0 .. 7
  */
__STATIC_INLINE uint32_t LL_PWR_GetAuthorisedStaticCidWakeUp(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  return ( (READ_REG(*regaddr) & (PWR_WIO1CIDCFGR_SCID)) >> PWR_WIO1CIDCFGR_SCID_Pos) ;
}


/**
  * @brief  Set/Get   CID(s) enable to update semaphore  of a wake-up ressource
  * @note  this function is unrelevant when no semaphore enable or CID filtering disable on input shared resource param
  * @rmtoll WIOxCIDCFGR          LL_PWR_ConfigSemaphore/LL_PWR_GetConfigSemaphore
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @param  cidConfig : bit map of cid : bit_k set if cid k is authorized to acquire semaphore, k  in 0 .. 7

  */
__STATIC_INLINE void LL_PWR_ConfigSemaphore(uint16_t wkRessource, uint16_t cidConfig)
{
  #define PWR_WIO1CIDCFGR_SEMWLC (PWR_WIO1CIDCFGR_SEMWLC0 | PWR_WIO1CIDCFGR_SEMWLC1 | PWR_WIO1CIDCFGR_SEMWLC2 | PWR_WIO1CIDCFGR_SEMWLC3 | \
                                  PWR_WIO1CIDCFGR_SEMWLC4 | PWR_WIO1CIDCFGR_SEMWLC5 | PWR_WIO1CIDCFGR_SEMWLC6 | PWR_WIO1CIDCFGR_SEMWLC7 )

  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  MODIFY_REG(*regaddr, PWR_WIO1CIDCFGR_SEMWLC, cidConfig << PWR_WIO1CIDCFGR_SEMWLC0_Pos);
}
__STATIC_INLINE uint32_t LL_PWR_GetConfigSemaphore(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  return (READ_REG(*regaddr) >> PWR_WIO1CIDCFGR_SEMWLC0_Pos);
}



/**
  * @brief  Enable/Disable  semaphore mechanism  to  control wakeup ressource access
  * @rmtoll WIOxCIDCFGR          LL_PWR_EnableSemaphore/LL_PWR_ReleaseSemaphore
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  */
__STATIC_INLINE void LL_PWR_EnableSemaphore(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  SET_BIT(*regaddr, PWR_WIO1CIDCFGR_SEM_EN);
}
__STATIC_INLINE void LL_PWR_DisableSemaphore(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  CLEAR_BIT(*regaddr, PWR_WIO1CIDCFGR_SEM_EN);
}

/**
  * @brief  Check if semaphore  for a wakeup ressource is enabled.
  * @rmtoll WIOxCIDCFGR              LL_PWR_IsSemaphoreEnabled
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @retval true is semaphore enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsSemaphoreEnabled(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  return ((READ_BIT(*regaddr, PWR_WIO1CIDCFGR_SEM_EN) == PWR_WIO1CIDCFGR_SEM_EN) ? 1UL : 0UL);
}

/**
  * @brief  Enable/Disable  CID filtering  to  control wakeup ressource access
  * @rmtoll WIOxCIDCFGR          LL_PWR_EnableCidFilteringWakeUp/LL_PWR_DisableCidFilteringWakeUp
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  */
__STATIC_INLINE void LL_PWR_EnableCidFilteringWakeUp(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  SET_BIT(*regaddr, PWR_WIO1CIDCFGR_CFEN);
}
__STATIC_INLINE void LL_PWR_DisableCidFilteringWakeUp(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  CLEAR_BIT(*regaddr, PWR_WIO1CIDCFGR_CFEN);
}

/**
  * @brief  Check if CID filtering  to  control wake-upressource access is enabled.
  * @rmtoll WIOxCIDCFGR              LL_PWR_IsCidFilteringWakeUpEnabled
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @retval true is semaphore enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsCidFilteringWakeUpEnabled(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1CIDCFGR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  return ((READ_BIT(*regaddr, PWR_WIO1CIDCFGR_CFEN) == PWR_WIO1CIDCFGR_CFEN) ? 1UL : 0UL);
}

/**
  * @brief  take/release  semaphore of a wake-up ressource
  * @rmtoll WIOxSEMCR          LL_PWR_TakeSemaphore/LL_PWR_ReleaseSemaphore
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  */
__STATIC_INLINE void LL_PWR_TakeSemaphore(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1SEMCR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  SET_BIT(*regaddr, PWR_WIO1SEMCR_SEM_MUTEX);
}
__STATIC_INLINE void LL_PWR_ReleaseSemaphore(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1SEMCR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  CLEAR_BIT(*regaddr, PWR_WIO1SEMCR_SEM_MUTEX);
}



/**
  * @brief  get CID of laster master which acquires  semaphore of a wake-up ressource
  * @note returned value is relevant ONLY if semaphore is enable with CID filtering on input shared ressource

  * @rmtoll WIOxSEMCR          LL_PWR_GetLastSuccessfullCid
  * @param  wkRessource : WIO ressource number  LL_WIO1 .. LL_WIO6
  * @retval cid  range in  0 .. 7
  */
__STATIC_INLINE uint32_t LL_PWR_GetLastSuccessfullCid(uint16_t wkRessource)
{
  __IO uint32_t *regaddr;

  regaddr = &PWR->WIO1SEMCR + (WIO_CID_CFG_ADD_OFFSET*wkRessource);
  return (READ_REG(*regaddr) >> PWR_WIO1SEMCR_SEMCID_Pos);
}


/**
  * @}
  */

/**
  * @}
  */


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */


/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_LL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
