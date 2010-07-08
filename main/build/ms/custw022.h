#ifndef CUSTSBNAALZ_H
#define CUSTSBNAALZ_H
/* ========================================================================
FILE: CUSTSBNAALZ

Copyright (c) 2001-2010 by QUALCOMM Incorporated.  All Rights Reserved.        
=========================================================================== */
#ifndef CUST_EDITION
#define CUST_EDITION
#endif

#ifdef CUST_EDITION

#define FEATURE_OEMUI_TASK
#define FEATURE_COLOR_DISPLAY
#define FEATURE_ONEMSG_USE_ONEFILE
#define FEATURE_SMS_UDH
#define FEATURE_WMS_APP
#define FEATURE_INIT_RUIM_SMSandADD_BYUIMTASK
#undef  FEATRUE_SUPPORT_G_SENSOR
#define FEATURE_CDSMS_CACHE_USELIST
#define FEATURE_RUIM_PHONEBOOK
#define FEATURE_ICARD_NO_UI_BASE
#define FEATURE_LANG_ENGLISH
#define FEATURE_LANG_INDONESIAN //add by yangdecai 2010/06/22
#undef FEATURE_LANG_CHINESE
#define FEATURE_NET_LOCK
#define FEATURE_SEAMLESS_SMS
#define FEATURE_OMH_SMS
#define FEATURE_ONEMSG_USE_ONEFILE
#define FEATURE_CDSMS_CACHE_USELIST
#define FIX_LINKITEM_INITBUG
#define FEATURE_SPN_FROM_BSMCCMNC
#endif

#ifndef TARGSB2_H
   #include "targsbw2.h"
#endif

#define FEATURE_DATA_STRIP_ATCOP 
#define FEATURE_STD_MIDI 
#define FEATURE_DIAG_LOWMEM 
#define CUST_MOB_MODEL 22
#define FEATURE_PLL_192 
#define FEATURE_CLKREGIM_1X_MODE 
#define FEATURE_AUDIO_CONFIGURATION_MINIMAL 
//Gemsea Remove #define FEATURE_AUDIO_CONFIGURATION_LO_TIER 
//#define FEATURE_IPL_NO_CAMERA     miaoxiaoming remove
#define FEATURE_UIM_QSC1100_LOW_MEMORY 
#define CM_FEATURE_HSBASED_PLUS_DIAL_DISPLAY 
#define FEATURE_MMODE_LOW_MEM_TARGET 
#define FEATURE_LOWTIER_LOWMEM 
#define FEATURE_REX_IPC 
#define FEATURE_ASYNC_DATA_NOOP 
#define FEATURE_HS_USB_PMIC_PHY 
#define FEATURE_HS_USB_USER_EVENT_POST 
#define FEATURE_RRC_SIB_HEAP 
#define FEATURE_LOW_MEMORY_USAGE 
//#define FEATURE_FS_LOW_MEMORY_USAGE 
#define FEATURE_DSM_MINIMIZE 
#define FEATURE_MSG_LOW_MEMORY_USAGE 
#define FEATURE_SIO_NO_DEBUG_TRACE 
#define FEATURE_DIAG_SMALL_BUFFER 
#define FEATURE_IPC_SMALL_MEMORY_POOL 
#define FEATURE_APP_DIALER 
#define FEATURE_RUIM 
#define FEATURE_UIM1 
#define FEATURE_UIM_PMIC_ON_UIM1 
#define FEATURE_UIM_T_1_SUPPORT 
#define FEATURE_UIM_BLOCK_MODE_SUPPORT 
#define FEATURE_UIM_BLOCK_MODE_BITS_IN_SIM_CONFIG_REG 
//#define FEATURE_ICARD_IMODEL 
#define FEATURE_RUIM_CDMA_REFRESH 
//#define FEATURE_RTRE_DEFAULT_IS_NV 
#define FEATURE_AUTH 
#define FEATURE_AUTH_DIGITS 
#define SCL_AMSS_DATA_BASE_ADDR 0x08005000
#define T_QSC6055 
#ifdef USES_CAMERA
#define FEATURE_JPEG_DECODER 
#define FEATURE_JPEG_ARM_STANDALONE_DECODER 
#endif
#define FEATURE_VOC_4GV 
#define FEATURE_AUDIO_CONFIGURATION_STANDARD 
#define FEATURE_MDM_AHB 
#define FEATURE_NEW_SLEEP_API 
#define FEATURE_TRM_API_V2 
#define FEATURE_BREW 
#define FEATURE_BREW_PWRUP_INIT 
#define FEATURE_DIAG_FS_ACCESS_VALIDATION 
#define FEATURE_DYNAMIC_OEM_HEAP 
#define FEATURE_MEMHEAP_MT 
#define FEATURE_I2C 
#define FEATURE_I2C_SKIP_CLK_HALT 
#define FEATURE_I2C_SKIP_CLK_RESET 
#define FEATURE_CDMA1X 
#define FEATURE_IS2000_SLOTTED_TIMER 
#define FEATURE_IS2000_REV_FCH_GATING 
#define FEATURE_MULTIMODE_ARCH 
#define FEATURE_MULTIMODE_RFAPI 
#define FEATURE_EXTENDED_PRL 
#define FEATURE_MMOC_SUPPORTS_HYBRID 
#define FEATURE_MDSP_TASK 
#define FEATURE_MDSP_USES_MODULES 
#define FEATURE_ERR_FATAL_ON_MDSP_HALT 
#define FEATURE_DBM 
#define FEATURE_ERR_LCD 
#define FEATURE_AUTO_VOICE_CALL_DIALER 
#define FEATURE_SYSTEM_ARBITRATION 
#define FEATURE_SD20 
#define FEATURE_2ND_PRL 
#define FEATURE_ZZ2 
#define FEATURE_GRAPH_TASK 
#define FEATURE_EFS 
#define FEATURE_EFS2 
#define FEATURE_EFS_MPEG4_FLASH 
#define FEATURE_USE_TIME_VU 
#define FEATURE_RDEVMAP_DIAG_DEFAULT_TO_USB 
#define FEATURE_DS 
#define FEATURE_FTM_MC 
#define FEATURE_SSPR_ENHANCEMENTS 
#define FEATURE_QDSP_SET_IMAGE_HW_RESOURCES 
#define FEATURE_QDSP_SET_MODULE_HW_RESOURCES 
#define FEATURE_MANAGE_GPIOS_FOR_SLEEP 
#define FEATURE_INT_ROAMING 
#define FEATURE_MSM_LIBRARY 
#define FEATURE_REX_IPC 
//#define FEATURE_TSG_EXT 
#define FEATURE_SD_SUPPORTS_BASE_INFO 
#define FEATURE_BREW_DEV 
#define FEATURE_QDSP_USES_NATIVE_MEMCPY 
#define FEATURE_VBATT_CUT_OFF_3P2V 
//#define FEATURE_PBM_TASK 
#define FEATURE_BATT_CBF18150 
#define FEATURE_DUAL_CLK_RGM 
#define FEATURE_ENABLE_FLOATING_POINT_ERRORS 
#define FEATURE_LOOPING_EXCEPTION_HANDLER 
#define FEATURE_ENC_CONTROL_TX_ON_EN 
#define FEATURE_PMIC_USB_ID_SIGNALING_UNAVAILABLE 
#define FEATURE_NO_EXT_RINGER 
#define FEATURE_PA_ACCESS_PROBE_CONFIG 
#define PNG_USES_LIBSTD 
#define JPEG_USES_LIBSTD 
#define FEATURE_VBATT_IGNORE_RF_MODE 
#define FEATURE_ENABLE_CHARGING_GAUGING 
#define FEATURE_STACK_REDUCTION 
#define NO_DOG 
#define FEATURE_POWER_ON_CONTROL_FROM_RTC_WORKAROUND 
#define FEATURE_C2K_TIME_INFO 
#define FEATURE_KIP_A0 
#define FEATURE_PEDRO_VER_1 
#define FEATURE_GSBI0_RUIM 
#define FEATURE_GSBI1_UART 
#define FEATURE_GSBI2_AUDIO 
#define FEATURE_QPST_DLOAD_THRU_OEMSBL 
#define FEATURE_NORPRG_HAS_HEADER 
#define FEATURE_DLOAD_SECURITY 
#define FEATURE_OEMSBL_SPLASH_SCREEN 
#define FEATURE_BUILD_CDMA_TRIMODE 
#define FEATURE_TRANS_MANAGER 
#define FEATURE_PLCM_ENHANCEMENTS 
#define FEATURE_HHO_ENHANCEMENTS 
#define FEATURE_SNM_ENHANCEMENTS 
#define FEATURE_MSM6500_DEC_DYNAMIC_CLK_OFF 
#define FEATURE_SDCC_VOTE_AGAINST_SLEEP 
#define FEATURE_DYNAMIC_CLOCK_FREQUENCY_CHANGING 
#define FEATURE_CLKREGIM_DYNAMIC_MDSP_SPEED 
#define FEATURE_CLKREGIM_DYNAMIC_VOLTAGE 
#define FEATURE_CLKREGIM_DEVMAN 
#define CLKRGM_FREQ_STEP 
#define CLKRGM_USE_IRAM 
#define FEATURE_MEID_SUPPORT 
#define FEATURE_QDSP_MODULE_RESOURCE_MGMT 
#define FEATURE_PBM_USE_EFS_PB 
#define FEATURE_OEMSBL_USB_BATT_CHG 
#define FEATURE_SC2X_SWAP_UART_DM_WITH_UART2 
#define FEATURE_SC2X_SW_PORT 
#define FEATURE_SC2X_SW_SBI_NOT_PORT 
#define FEATURE_SC2X_SW_BOOT_NOT_PORT 
#define FEATURE_SC2X_SW_DEM1X_NOT_PORT 
#define FEATURE_SC2X_TRAMP_NOT_PORT 
#define FEATURE_SC2X_BUS_NOT_PORT 
#define FEATURE_DONT_LET_LOW_PRIORITY_TASK_BLOCK_ISR 
#define CACHE_POLICY_WRITE_BACK 
#define FEATURE_SHARED_SEGMENT 
#define FEATURE_BUILD_CDMA_CELL_PCS 
#define FEATURE_ENHANCED_BAND_CLASS 
#define BSP_RF_H "bsp_rf_ezrf6500.h"
#define FEATURE_RF_ZIF 
#define FEATURE_AUX_SBI 
//#define FEATURE_OSBL_USB_BATT_CHG 
//#define FEATURE_OSBL_CHG_SCREEN 
#define FEATURE_BOOT_SPLASH_SCREEN 
#define FEATURE_HS_USB_ON_MODEM_PROC 
#define FEATURE_HSU_1_2_BYTE_HW_CRC_ERROR_WORKAROUND 
#define FEATURE_HS_USB 
#define FEATURE_USB_CDC_ACM 
#define FEATURE_USB_DIAG 
#define FEATURE_HS_USB_SHARED_SEG 
#define FEATURE_HS_USB_MEM_OPTIMIZATION 
#define FEATURE_HS_USB_SMALL_HEAP 
#define FEATURE_HS_USB_PMIC_PHY 
#define HS_USB_MS_MAX_NUM_LUNS 1
#define FEATURE_CHG_TASK 
#define FEATURE_HS_USB_CHG_REMOTE_API 
#define FEATURE_HS_USB_FS_ONLY 
#define FEATURE_BRINGUP_DISABLE 
#define FEATURE_MEM_REDUCE_PRL 
#define FEATURE_CP_MEM_REDUCTION 
#define FEATURE_QHSUSB 
#define FEATURE_QHSUSB_DEAD_BATTERY_CHARGING 
#define FEATURE_XO 

#ifdef CUST_EDITION
#define FEATURE_DISP_128X128
#define FEATURE_DUAL_UIMCARD
#define FEATRUE_AUTO_SET_NEED_NV_VALUE
#define FEATURE_FM_RADIO
#define FEATURE_FM_OEM
#define FEATURE_PROJECT_W022
#define FEATURE_TORCH_SUPPORT		//�ֵ�Ͳ
#define FEATURE_AUDIO_CAMERA_CONCURRENCY
#define FEATURE_DRV_SDCC
#define FEATURE_SDCC_CLK_CONFIG
#define FEATURE_HS_USB_MS_FD
#endif

#include "custuim.h"
#include "custcmx.h"
#include "custavs.h"
#include "custsio.h"
#include "custmmode.h"
#include "custcdma.h"
#include "custrf.h"
#include "custcdma2000.h"
#include "custdebug.h"
#include "custdmss.h"
#include "custdata.h"
#include "custdiag.h"
#include "custwms.h"
#include "custsrch.h"
#include "custui.h"
#include "custmcs.h"
#include "custpmic3.h"
#include "custefs.h"
//#include "custfmrds.h"
#include "custnvm.h"
#include "custrex.h"
#include "custbmp.h"
#include "custsurf.h"
#ifdef FEATURE_DRV_SDCC
#include "Custsdcc.h"
#endif
#ifdef USES_CAMERA
#include "custcamera.h"
#include "custjpeg.h"
#endif

#ifdef FEATURE_DS_MOBILE_IP
   #undef FEATURE_DS_MOBILE_IP
#endif
#ifdef FEATURE_DS_MOBILE_IP_PERF
   #undef FEATURE_DS_MOBILE_IP_PERF
#endif
#ifdef FEATURE_MEDIAPLAYER_TEST_AUTOMATION
   #undef FEATURE_MEDIAPLAYER_TEST_AUTOMATION
#endif
//Gemsea Remove #ifdef FEATURE_MP3
//Gemsea Remove   #undef FEATURE_MP3
//Gemsea Remove #endif
#ifdef FEATURE_MDP_LAYER1_PRIMARY
   #undef FEATURE_MDP_LAYER1_PRIMARY
#endif
#ifdef FEATURE_OVERLAY2
   #undef FEATURE_OVERLAY2
#endif
#ifdef FEATURE_SCH_TRIAGE
   #undef FEATURE_SCH_TRIAGE
#endif
#ifdef FEATURE_IS2000_R_SCH
   #undef FEATURE_IS2000_R_SCH
#endif
#ifdef FEATURE_PNG_ENCODER
   #undef FEATURE_PNG_ENCODER
#endif
#ifdef FEATURE_IS2000_SCH_STATS
   #undef FEATURE_IS2000_SCH_STATS
#endif
#ifdef FEATURE_AUDFMT_EVB
   #undef FEATURE_AUDFMT_EVB
#endif
#ifdef FEATURE_MMOVERLAY
   #undef FEATURE_MMOVERLAY
#endif
#ifdef FEATURE_SAF
   #undef FEATURE_SAF
#endif
//Gemsea Remove #ifdef FEATURE_QTUNES
//Gemsea Remove   #undef FEATURE_QTUNES
//Gemsea Remove #endif
#ifdef FEATURE_IS2000_F_SCH
   #undef FEATURE_IS2000_F_SCH
#endif
#ifdef FEATURE_DISP_TASK
   #undef FEATURE_DISP_TASK
#endif
#ifdef FEATURE_MDP
   #undef FEATURE_MDP
#endif
#ifdef FEATURE_PNG_DECODER
   #undef FEATURE_PNG_DECODER
#endif
#ifdef FEATURE_IS2000_SCH
   #undef FEATURE_IS2000_SCH
#endif
#ifdef FEATURE_AAC
   #undef FEATURE_AAC
#endif
#ifdef CLKRGM_FREQ_STEP
   #undef CLKRGM_FREQ_STEP
#endif
#ifdef FEATURE_HS_DISPLAY_CAPTURE
   #undef FEATURE_HS_DISPLAY_CAPTURE
#endif
#ifdef CLKRGM_TEST
   #undef CLKRGM_TEST
#endif
#ifdef FEATURE_DATA_PS_MEM_DEBUG
   #undef FEATURE_DATA_PS_MEM_DEBUG
#endif
#ifdef FEATURE_APP_QTCAM
   #undef FEATURE_APP_QTCAM
#endif
#ifdef FEATURE_CAMIF_INTERNAL_TEST
   #undef FEATURE_CAMIF_INTERNAL_TEST
#endif
#ifdef FEATURE_APP_TEST_AUTOMATION
   #undef FEATURE_APP_TEST_AUTOMATION
#endif
#ifdef FEATURE_PBM_USE_EFS_PB
   #undef FEATURE_PBM_USE_EFS_PB
#endif
#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
   #undef FEATURE_AVS_INCALL_MIXER_ADEC_PB
#endif
#ifdef FEATURE_DMOV
   #undef FEATURE_DMOV
#endif
#ifdef FEATURE_PMIC_MANAGED_LDO
   #undef FEATURE_PMIC_MANAGED_LDO
#endif
#ifdef FEATURE_DIAG_HW_ADDR_CHECK
   #undef FEATURE_DIAG_HW_ADDR_CHECK
#endif
#ifdef FEATURE_BRINGUP_WRITETHROUGH
   #undef FEATURE_BRINGUP_WRITETHROUGH
#endif
#ifdef FEATURE_DISPLAY_POWER_DEBUG
   #undef FEATURE_DISPLAY_POWER_DEBUG
#endif
#ifdef FEATURE_PMEM
   #undef FEATURE_PMEM
#endif
#ifdef FEATURE_SECOND_UART
   #undef FEATURE_SECOND_UART
#endif
#ifdef FEATURE_UNIFORM_SCAN_OOS_HDR_ENH
   #undef FEATURE_UNIFORM_SCAN_OOS_HDR_ENH
#endif
#ifdef FEATURE_SC2X_HAS_UART1
   #undef FEATURE_SC2X_HAS_UART1
#endif
#ifdef FLASH_USES_DM
   #undef FLASH_USES_DM
#endif
#ifdef FEATURE_UNIFORM_SCAN_OOS
   #undef FEATURE_UNIFORM_SCAN_OOS
#endif



#endif /* CUSTSB2_H */
