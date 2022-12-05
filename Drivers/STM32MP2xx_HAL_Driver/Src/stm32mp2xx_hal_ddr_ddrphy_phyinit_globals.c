/*
 * Copyright (C) 2021-2022, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "stm32mp2xx_hal_ddr_ddrphy_phyinit.h"

/* Global struct defines */
runtime_config_t runtimeconfig;
user_input_basic_t userinputbasic;
user_input_advanced_t userinputadvanced;
user_input_mode_register_t userinputmoderegister;
user_input_swizzle_t userinputswizzle;

/* Firmware 1D Message Block structures */
pmu_smb_ddr_1d_t mb_ddr_1d[NB_PS];
/* Shadow of 1D message block. Used by PhyInit to track user changes to the data structure */
pmu_smb_ddr_1d_t shdw_ddr_1d[NB_PS];

/* PHY Identifier when using multiple PHY's */
int currentphyinst;

/*
 * Represent the value stored in Step C into the register with the same name.
 * Defined as a global variable so that implementation of ddrphy_phyinit_progcsrskiptrain()
 * function does not require a PHY read register implementation.
 */
int ardptrinitval[NB_PS];
