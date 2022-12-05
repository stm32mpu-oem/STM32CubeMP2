// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (C) 2021, STMicroelectronics - All Rights Reserved
 */

/*
 * DDR type: LPDDR4 (Palladium emulation platform)
 * DDR density: 1x4Gbits
 * DDR width: 1x32bits
 */

#ifndef STM32MP2XX_LPDDR4_1x4GBITS_1x32BITS_PALLADIUM_H
#define STM32MP2XX_LPDDR4_1x4GBITS_1x32BITS_PALLADIUM_H

#define DDR_MEM_NAME	"LPDDR4 1x4Gbits 1x32bits Palladium"
#define DDR_MEM_SPEED	800000
#define DDR_MEM_SIZE	0x20000000

#define DDR_MSTR 0x01080020
#define DDR_MRCTRL0 0x00000030
#define DDR_MRCTRL1 0x00000000
#define DDR_MRCTRL2 0x00000000
#define DDR_DERATEEN 0x00000101
#define DDR_DERATEINT 0x5E9C4CD4
#define DDR_DERATECTL 0x00000001
#define DDR_PWRCTL 0x00000020
#define DDR_PWRTMG 0x00502014
#define DDR_HWLPCTL 0x00A00002
#define DDR_RFSHCTL0 0x00210074
#define DDR_RFSHCTL1 0x00000000
#define DDR_RFSHCTL3 0x00000000
#define DDR_RFSHTMG 0x80C20018
#define DDR_RFSHTMG1 0x00180000
#define DDR_CRCPARCTL0 0x00000000
#define DDR_CRCPARCTL1 0x00001000
#define DDR_INIT0 0x00020002
#define DDR_INIT1 0x00010002
#define DDR_INIT2 0x00000D05
#define DDR_INIT3 0x00240012
#define DDR_INIT4 0x00130000
#define DDR_INIT5 0x00100004
#define DDR_INIT6 0x0040004D
#define DDR_INIT7 0x001C004D
#define DDR_DIMMCTL 0x00000000
#define DDR_RANKCTL 0x0000066F
#define DDR_DRAMTMG0 0x12100211
#define DDR_DRAMTMG1 0x00030418
#define DDR_DRAMTMG2 0x04070B0E
#define DDR_DRAMTMG3 0x0060600C
#define DDR_DRAMTMG4 0x08040408
#define DDR_DRAMTMG5 0x01030606
#define DDR_DRAMTMG6 0x02020005
#define DDR_DRAMTMG7 0x00000301
#define DDR_DRAMTMG8 0x03034405
#define DDR_DRAMTMG9 0x0004040D
#define DDR_DRAMTMG10 0x001C180A
#define DDR_DRAMTMG11 0x440C021C
#define DDR_DRAMTMG12 0x00010010
#define DDR_DRAMTMG13 0x0A200002
#define DDR_DRAMTMG14 0x00000037
#define DDR_DRAMTMG15 0x00000000
#define DDR_ZQCTL0 0x018D000C
#define DDR_ZQCTL1 0x01400027
#define DDR_ZQCTL2 0x00000000
#define DDR_DFITMG0 0x038B8206
#define DDR_DFITMG1 0x000A0303
#define DDR_DFILPCFG0 0x0700a011
#define DDR_DFILPCFG1 0x00000000
#define DDR_DFIUPD0 0xC018000C
#define DDR_DFIUPD1 0x005700B4
#define DDR_DFIUPD2 0x80000000
#define DDR_DFIMISC 0x00000041
#define DDR_DFITMG2 0x00000B06
#define DDR_DFITMG3 0x00000000
#define DDR_DBICTL 0x00000001
#define DDR_DFIPHYMSTR 0x00000001
#define DDR_ADDRMAP0 0x0000001F
#define DDR_ADDRMAP1 0x00080808
#define DDR_ADDRMAP2 0x00000000
#define DDR_ADDRMAP3 0x00000000
#define DDR_ADDRMAP4 0x00001F1F
#define DDR_ADDRMAP5 0x070F0707
#define DDR_ADDRMAP6 0x0F0F0707
#define DDR_ADDRMAP7 0x00000F0F
#define DDR_ADDRMAP8 0x00003F3F
#define DDR_ADDRMAP9 0x07070707
#define DDR_ADDRMAP10 0x07070707
#define DDR_ADDRMAP11 0x00000007
#define DDR_ODTCFG 0x04000400
#define DDR_ODTMAP 0x00002211
#define DDR_SCHED 0x00000F05
#define DDR_SCHED1 0x000000FF
#define DDR_PERFHPR1 0x0F000001
#define DDR_PERFLPR1 0x0F00007F
#define DDR_PERFWR1 0x0F00007F
#define DDR_DBG0 0x00000000
#define DDR_DBG1 0x00000000
#define DDR_DBGCMD 0x00000000
#define DDR_SWCTL 0x00000001
#define DDR_POISONCFG 0x00000000
#define DDR_PCCFG 0x00000000
#define DDR_PCFGR_0 0x00000000
#define DDR_PCFGW_0 0x00004000
#define DDR_PCTRL_0 0x00000000
#define DDR_PCFGQOS0_0 0x00000000
#define DDR_PCFGQOS1_0 0x00000000
#define DDR_PCFGWQOS0_0 0x00000E03
#define DDR_PCFGWQOS1_0 0x00000000
#define DDR_PCFGR_1 0x00000000
#define DDR_PCFGW_1 0x00004000
#define DDR_PCTRL_1 0x00000000
#define DDR_PCFGQOS0_1 0x00100003
#define DDR_PCFGQOS1_1 0x01000400
#define DDR_PCFGWQOS0_1 0x01100B03
#define DDR_PCFGWQOS1_1 0x02000200

#define DDR_UIB_DRAMTYPE 0x00000002
#define DDR_UIB_DIMMTYPE 0x00000004
#define DDR_UIB_LP4XMODE 0x00000000
#define DDR_UIB_NUMDBYTE 0x00000004
#define DDR_UIB_NUMACTIVEDBYTEDFI0 0x00000002
#define DDR_UIB_NUMACTIVEDBYTEDFI1 0x00000002
#define DDR_UIB_NUMANIB 0x00000008
#define DDR_UIB_NUMRANK_DFI0 0x00000001
#define DDR_UIB_NUMRANK_DFI1 0x00000001
#define DDR_UIB_DRAMDATAWIDTH 0x00000010
#define DDR_UIB_NUMPSTATES 0x00000001
#define DDR_UIB_FREQUENCY_0 0x00000319
#define DDR_UIB_PLLBYPASS_0 0x00000000
#define DDR_UIB_DFIFREQRATIO_0 0x00000001
#define DDR_UIB_DFI1EXISTS 0x00000001
#define DDR_UIB_TRAIN2D 0x00000000
#define DDR_UIB_HARDMACROVER 0x00000003
#define DDR_UIB_READDBIENABLE_0 0x00000000
#define DDR_UIB_DFIMODE 0x00000000
#define DDR_UIA_LP4RXPREAMBLEMODE_0 0x00000000
#define DDR_UIA_LP4POSTAMBLEEXT_0 0x00000001
#define DDR_UIA_D4RXPREAMBLELENGTH_0 0x00000000
#define DDR_UIA_D4TXPREAMBLELENGTH_0 0x00000000
#define DDR_UIA_EXTCALRESVAL 0x00000000
#define DDR_UIA_IS2TTIMING_0 0x00000000
#define DDR_UIA_ODTIMPEDANCE_0 0x0000003C
#define DDR_UIA_TXIMPEDANCE_0 0x0000003C
#define DDR_UIA_ATXIMPEDANCE 0x00000014
#define DDR_UIA_MEMALERTEN 0x00000000
#define DDR_UIA_MEMALERTPUIMP 0x00000005
#define DDR_UIA_MEMALERTVREFLEVEL 0x00000029
#define DDR_UIA_MEMALERTSYNCBYPASS 0x00000000
#define DDR_UIA_DISDYNADRTRI_0 0x00000001
#define DDR_UIA_PHYMSTRTRAININTERVAL_0 0x0000000A
#define DDR_UIA_PHYMSTRMAXREQTOACK_0 0x00000005
#define DDR_UIA_WDQSEXT 0x00000000
#define DDR_UIA_CALINTERVAL 0x00000009
#define DDR_UIA_CALONCE 0x00000000
#define DDR_UIA_LP4RL_0 0x00000002
#define DDR_UIA_LP4WL_0 0x00000002
#define DDR_UIA_LP4WLS_0 0x00000000
#define DDR_UIA_LP4DBIRD_0 0x00000000
#define DDR_UIA_LP4DBIWR_0 0x00000000
#define DDR_UIA_LP4NWR_0 0x00000002
#define DDR_UIA_LP4LOWPOWERDRV 0x00000000
#define DDR_UIA_DRAMBYTESWAP 0x00000000
#define DDR_UIA_RXENBACKOFF 0x00000001
#define DDR_UIA_TRAINSEQUENCECTRL 0x00000000
#define DDR_UIA_SNPSUMCTLOPT 0x00000000
#define DDR_UIA_SNPSUMCTLF0RC5X_0 0x00000000
#define DDR_UIA_TXSLEWRISEDQ_0 0x0000000F
#define DDR_UIA_TXSLEWFALLDQ_0 0x0000000F
#define DDR_UIA_TXSLEWRISEAC 0x0000000F
#define DDR_UIA_TXSLEWFALLAC 0x0000000F
#define DDR_UIA_DISABLERETRAINING 0x00000000
#define DDR_UIA_DISABLEPHYUPDATE 0x00000000
#define DDR_UIA_ENABLEHIGHCLKSKEWFIX 0x00000000
#define DDR_UIA_DISABLEUNUSEDADDRLNS 0x00000000
#define DDR_UIA_PHYINITSEQUENCENUM 0x00000000
#define DDR_UIA_ENABLEDFICSPOLARITYFIX 0x00000000
#define DDR_UIA_PHYVREF 0x000000014
#define DDR_UIA_SEQUENCECTRL_0 0x00000007
#define DDR_UIM_MR0_0 0x00000000
#define DDR_UIM_MR1_0 0x00000024
#define DDR_UIM_MR2_0 0x00000012
#define DDR_UIM_MR3_0 0x00000013
#define DDR_UIM_MR4_0 0x00000000
#define DDR_UIM_MR5_0 0x00000000
#define DDR_UIM_MR6_0 0x00000000
#define DDR_UIM_MR11_0 0x00000060
#define DDR_UIM_MR12_0 0x0000004D
#define DDR_UIM_MR13_0 0x00000008
#define DDR_UIM_MR14_0 0x0000004D
#define DDR_UIM_MR22_0 0x0000001C
#define DDR_UIS_SWIZZLE_0 0x00000000
#define DDR_UIS_SWIZZLE_1 0x00000000
#define DDR_UIS_SWIZZLE_2 0x00000000
#define DDR_UIS_SWIZZLE_3 0x00000000
#define DDR_UIS_SWIZZLE_4 0x00000000
#define DDR_UIS_SWIZZLE_5 0x00000000
#define DDR_UIS_SWIZZLE_6 0x00000000
#define DDR_UIS_SWIZZLE_7 0x00000000
#define DDR_UIS_SWIZZLE_8 0x00000000
#define DDR_UIS_SWIZZLE_9 0x00000000
#define DDR_UIS_SWIZZLE_10 0x00000000
#define DDR_UIS_SWIZZLE_11 0x00000000
#define DDR_UIS_SWIZZLE_12 0x00000000
#define DDR_UIS_SWIZZLE_13 0x00000000
#define DDR_UIS_SWIZZLE_14 0x00000000
#define DDR_UIS_SWIZZLE_15 0x00000000
#define DDR_UIS_SWIZZLE_16 0x00000000
#define DDR_UIS_SWIZZLE_17 0x00000000
#define DDR_UIS_SWIZZLE_18 0x00000000
#define DDR_UIS_SWIZZLE_19 0x00000000
#define DDR_UIS_SWIZZLE_20 0x00000000
#define DDR_UIS_SWIZZLE_21 0x00000000
#define DDR_UIS_SWIZZLE_22 0x00000000
#define DDR_UIS_SWIZZLE_23 0x00000000
#define DDR_UIS_SWIZZLE_24 0x00000000
#define DDR_UIS_SWIZZLE_25 0x00000000
#define DDR_UIS_SWIZZLE_26 0x00000000
#define DDR_UIS_SWIZZLE_27 0x00000000
#define DDR_UIS_SWIZZLE_28 0x00000000
#define DDR_UIS_SWIZZLE_29 0x00000000
#define DDR_UIS_SWIZZLE_30 0x00000000
#define DDR_UIS_SWIZZLE_31 0x00000000
#define DDR_UIS_SWIZZLE_32 0x00000000
#define DDR_UIS_SWIZZLE_33 0x00000000
#define DDR_UIS_SWIZZLE_34 0x00000000
#define DDR_UIS_SWIZZLE_35 0x00000000
#define DDR_UIS_SWIZZLE_36 0x00000000
#define DDR_UIS_SWIZZLE_37 0x00000000
#define DDR_UIS_SWIZZLE_38 0x00000000
#define DDR_UIS_SWIZZLE_39 0x00000000
#define DDR_UIS_SWIZZLE_40 0x00000000
#define DDR_UIS_SWIZZLE_41 0x00000000
#define DDR_UIS_SWIZZLE_42 0x00000000
#define DDR_UIS_SWIZZLE_43 0x00000000

#endif
