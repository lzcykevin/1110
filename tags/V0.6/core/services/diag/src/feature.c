/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

             F E A T U R E   M A S K   D E F I N I T T I O N S


GENERAL DESCRIPTION
  This file contains the definition for the bit mask that supports the 
  feature query diag interface.
  
EXTERNALIZED FUNCTIONS
  None.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

Copyright (c) 1998-2005 by QUALCOMM, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

 $Header: //depot/asic/msmshared/services/diag/MSMSHARED_DIAG_1.2/feature.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/31/05   as      Fixed lint errors.
01/26/01   ych     Merged T-53/JCDMA features for SK.
09/11/98   grl     Created.

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "feature.h"
#include "comdef.h"
#include "customer.h"


/*===========================================================================

                DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains definitions for constants, macros, types, variables
and other items needed by this module.

===========================================================================*/

/*
 *  To add features simply add an entry to the end of feature_query_enum_type
 *  in feature.h and add to the end of diag_feature_mask.  Surround your
 *  bit addition with the feature that you are associating it with.
 *  Make sure to place a comma and a 0 after every 8 entries. 
 *  The appropriate mask is generated at compile time 
 *  automatically based on which features are defined.
 */
/*lint -save -e641 */
byte diag_feature_mask[FEATURE_MASK_LENGTH] = {
  0
  #ifdef FEATURE_ACP
#error code not present
  #endif /* FEATURE_ACP */
  #ifdef FEATURE_CDMA_800
  | ADD_BIT_TO_FEATURE_MASK(F_CDMA_800_BIT)
  #endif /* FEATURE_CDMA_800 */
  #ifdef FEATURE_AUTH
  | ADD_BIT_TO_FEATURE_MASK(F_AUTH_BIT)
  #endif /* FEATURE_AUTH */
  #ifdef FEATURE_DS_CDMA
#error code not present
  #endif /* FEATURE_DS_CDMA */
  #ifdef FEATURE_DS_AMPS
#error code not present
  #endif /* FEATURE_DS_AMPS */
  #ifdef FEATURE_DS_SLIM
#error code not present
  #endif /* FEATURE_DS_SLIM */
  #ifdef FEATURE_JSTD008
  | ADD_BIT_TO_FEATURE_MASK(F_JSTD008_BIT)
  #endif /* FEATURE_JSTD008 */
  #ifdef FEATURE_CLASS_1_IMSI
  | ADD_BIT_TO_FEATURE_MASK(F_CLASS_1_IMSI_BIT)
  #endif /* FEATURE_CLASS_1_IMSI */
  , 0
  #ifdef FEATURE_OTASP
  | ADD_BIT_TO_FEATURE_MASK(F_OTASP_BIT)
  #endif /* FEATURE_OTASP */
  #ifdef FEATURE_PREFERRED_ROAMING
  | ADD_BIT_TO_FEATURE_MASK(F_PREFERRED_ROAMING_BIT)
  #endif /* FEATURE_PREFERRED_ROAMING */
  #ifdef FEATURE_PRL_DLOAD
  | ADD_BIT_TO_FEATURE_MASK(F_PRL_DLOAD_BIT)
  #endif /* FEATURE_PRL_DLOAD */
  #ifdef FEATURE_DIAG_ORIG_CALL
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_ORIG_CALL_BIT)
  #endif /* FEATURE_DIAG_ORIG_CALL */
  #ifdef FEATURE_SMS
  | ADD_BIT_TO_FEATURE_MASK(F_SMS_BIT)
  #endif /* FEATURE_SMS */
  #ifdef FEATURE_POWER_CLASS_III
  | ADD_BIT_TO_FEATURE_MASK(F_POWER_CLASS_III_BIT)
  #endif /* FEATURE_POWER_CLASS_III */
  #ifdef FEATURE_BTU
#error code not present
  #endif /* FEATURE_BTU */
  #ifdef FEATURE_NV_DIALING_PLAN
#error code not present
  #endif /* FEATURE_NV_DIALING_PLAN */
  , 0
  #ifdef FEATURE_BRAZIL_WLL
#error code not present
  #endif /* FEATURE_BRAZIL_WLL */
  #ifdef FEATURE_INDIA_WLL
#error code not present
  #endif /* FEATURE_INDIA_WLL */
  #ifdef FEATURE_US_WLL
#error code not present
  #endif /* FEATURE_US_WLL */
  #ifdef FEATURE_RUSSIA_WLL
#error code not present
  #endif /* FEATURE_RUSSIA_WLL */
  #ifdef FEATURE_MOSCOW_WLL
#error code not present
  #endif /* FEATURE_MOSCOW_WLL */
  #ifdef FEATURE_MYANMAR_WLL
#error code not present
  #endif /* FEATURE_MYANMAR_WLL */
  #ifdef FEATURE_STD_WLL
#error code not present
  #endif /* FEATURE_STD_WLL */
  #ifdef FEATURE_CALL_RESTRICTION
#error code not present
  #endif /* FEATURE_CALL_RESTRICTION */
  , 0
  #ifdef FEATURE_PWD_SPEED_DIALS
#error code not present
  #endif /* FEATURE_PWD_SPEED_DIALS */
  #ifdef FEATURE_ALARMS
#error code not present
  #endif /* FEATURE_ALARMS */
  #ifdef FEATURE_HOTLINE
#error code not present
  #endif /* FEATURE_HOTLINE */
  #ifdef FEATURE_SPEED_DIALS
#error code not present
  #endif /* FEATURE_SPEED_DIALS */
  #ifdef FEATURE_WLL_POUND919
#error code not present
  #endif /* FEATURE_WLL_POUND919 */
  #ifdef FEATURE_LCD_I2
#error code not present
  #endif /* FEATURE_LCD_I2 */
  #ifdef FEATURE_UI_SMS
  | ADD_BIT_TO_FEATURE_MASK(F_UI_SMS_BIT)
  #endif /* FEATURE_UI_SMS */
  #ifdef FEATURE_CAR_KIT_DTMF
  | ADD_BIT_TO_FEATURE_MASK(F_CAR_KIT_DTMF_BIT)
  #endif /* FEATURE_CAR_KIT_DTMF */
  , 0
  #ifdef FEATURE_UI_FORCE_MODE_SEL
  | ADD_BIT_TO_FEATURE_MASK(F_UI_FORCE_MODE_SEL_BIT)
  #endif /* FEATURE_UI_FORCE_MODE_SEL */
  #ifdef FEATURE_UI_SILENT_REDIAL
  | ADD_BIT_TO_FEATURE_MASK(F_UI_SILENT_REDIAL_BIT)
  #endif /* FEATURE_UI_SILENT_REDIAL */
  #ifdef FEATURE_OTASP_800
#error code not present
  #endif /* FEATURE_OTASP_800 */
  #ifdef FEATURE_UI_SEND_PIN
  | ADD_BIT_TO_FEATURE_MASK(F_UI_SEND_PIN_BIT)
  #endif /* FEATURE_UI_SEND_PIN */
  #ifdef FEATURE_UI_FORCE_CALL
  | ADD_BIT_TO_FEATURE_MASK(F_UI_FORCE_CALL_BIT)
  #endif /* FEATURE_UI_FORCE_CALL */
  #ifdef FEATURE_SMS_UI
  | ADD_BIT_TO_FEATURE_MASK(F_SMS_UI_BIT)
  #endif /* FEATURE_SMS_UI */
  #ifdef FEATURE_PILOT_SNIFFER
#error code not present
  #endif /* FEATURE_PILOT_SNIFFER */
  #ifdef FEATURE_UI_KEYBEEP_AT_EARPIECE
#error code not present
  #endif /* FEATURE_UI_KEYBEEP_AT_EARPIECE */
  , 0
  #ifdef FEATURE_UI_OTASP_MENU
  | ADD_BIT_TO_FEATURE_MASK(F_UI_OTASP_MENU_BIT)
  #endif /* FEATURE_UI_OTASP_MENU */
  #ifdef FEATURE_UI_OLD_MARKOV
#error code not present
  #endif /* FEATURE_UI_OLD_MARKOV */
  #ifdef FEATURE_UI_SILENT_TO_OFF
#error code not present
  #endif /* FEATURE_UI_SILENT_TO_OFF */
  #ifdef FEATURE_UI_AUTO_ANS_INDICATE
  | ADD_BIT_TO_FEATURE_MASK(F_UI_AUTO_ANS_INDICATE_BIT)
  #endif /* FEATURE_UI_AUTO_ANS_INDICATE */
  #ifdef FEATURE_UI_CASE_USE_A
#error code not present
  #endif /* FEATURE_UI_CASE_USE_A */
  #ifdef FEATURE_UI_QZ_TO_79
#error code not present
  #endif /* FEATURE_UI_QZ_TO_79 */
  #ifdef FEATURE_UI_SHOW_DROP_CALL
  | ADD_BIT_TO_FEATURE_MASK(F_UI_SHOW_DROP_CALL_BIT)
  #endif /* FEATURE_UI_SHOW_DROP_CALL */
  #ifdef FEATURE_UI_TIME_YES
#error code not present
  #endif /* FEATURE_UI_TIME_YES */
  , 0
  #ifdef FEATURE_UI_PWR_KEY_ALT
  | ADD_BIT_TO_FEATURE_MASK(F_UI_PWR_KEY_ALT_BIT)
  #endif /* FEATURE_UI_PWR_KEY_ALT */
  #ifdef FEATURE_UI_ENTER_NAME_PROMPT
#error code not present
  #endif /* FEATURE_UI_ENTER_NAME_PROMPT */
  #ifdef FEATURE_UI_SAVE_REDIAL_BUFFER
#error code not present
  #endif /* FEATURE_UI_SAVE_REDIAL_BUFFER */
  #ifdef FEATURE_UI_3_8_ESN
#error code not present
  #endif /* FEATURE_UI_3_8_ESN */
  #ifdef FEATURE_VOICE_PRIVACY
#error code not present
  #endif /* FEATURE_VOICE_PRIVACY */
  #ifdef FEATURE_VOICE_PRIVACY_SWITCH
#error code not present
  #endif /* FEATURE_VOICE_PRIVACY_SWITCH */
  #ifdef FEATURE_UI_ENHANCED_PRIVACY_SET
#error code not present
  #endif /* FEATURE_UI_ENHANCED_PRIVACY_SET */
  #ifdef FEATURE_CDMA_1900
  | ADD_BIT_TO_FEATURE_MASK(F_CDMA_1900_BIT)
  #endif /* FEATURE_CDMA_1900 */
  , 0
  #ifdef FEATURE_UI_IMSI_ALL_0_OK
#error code not present
  #endif /* FEATURE_UI_IMSI_ALL_0_OK */
  #ifdef FEATURE_UI_OTKSL
#error code not present
  #endif /* FEATURE_UI_OTKSL */
  #ifdef FEATURE_NV_ONE_NAM_RL_LARGE
  | ADD_BIT_TO_FEATURE_MASK(F_NV_ONE_NAM_RL_LARGE_BIT)
  #endif /* FEATURE_NV_ONE_NAM_RL_LARGE */
  #ifdef FEATURE_MULTIPLE_LANG
#error code not present
  #endif /* FEATURE_MULTIPLE_LANG */
  #ifdef FEATURE_LANG_FRENCH
#error code not present
  #endif /* FEATURE_LANG_FRENCH */
  #ifdef FEATURE_LANG_SPANISH
#error code not present
  #endif /* FEATURE_LANG_SPANISH */
  #ifdef FEATURE_LANG_PORTUGUESE
#error code not present
  #endif /* FEATURE_LANG_PORTUGUESE */
  #ifdef FEATURE_LANG_XXX
#error code not present
  #endif /* FEATURE_LANG_XXX */
  , 0
  #ifdef FEATURE_UI_SHOW_SEARCHING
#error code not present
  #endif /* FEATURE_UI_SHOW_SEARCHING */
  #ifdef FEATURE_SYNC_FREQ_PLUTO
#error code not present
  #endif /* FEATURE_SYNC_FREQ_PLUTO */
  #ifdef FEATURE_UI_ESCALATING_RING
#error code not present
  #endif /* FEATURE_UI_ESCALATING_RING */
  #ifdef FEATURE_VIBRATOR
#error code not present
  #endif /* FEATURE_VIBRATOR */
  #ifdef FEATURE_SND_FLIP_PHONE
#error code not present
  #endif /* FEATURE_SND_FLIP_PHONE */
  #ifdef FEATURE_UI_DTMF_THRU_EARPIECE
#error code not present
  #endif /* FEATURE_UI_DTMF_THRU_EARPIECE */
  #ifdef FEATURE_UI_FLIP_PHONE
#error code not present
  #endif /* FEATURE_UI_FLIP_PHONE */
  #ifdef FEATURE_UI_OTASP_DIGIT_APPEND
#error code not present
  #endif /* FEATURE_UI_OTASP_DIGIT_APPEND */
  , 0
  #ifdef FEATURE_UI_OTASP_STAR2281X
#error code not present
  #endif /* FEATURE_UI_OTASP_STAR2281X */
  #ifdef FEATURE_UI_POUND_INFO_ORIG
#error code not present
  #endif /* FEATURE_UI_POUND_INFO_ORIG */
  #ifdef FEATURE_UI_ALT_CALL_FAIL
#error code not present
  #endif /* FEATURE_UI_ALT_CALL_FAIL */
  #ifdef FEATURE_UI_STAR228_CALL
#error code not present
  #endif /* FEATURE_UI_STAR228_CALL */
  #ifdef FEATURE_UI_ENVELOPE_VM_ICON
#error code not present
  #endif /* FEATURE_UI_ENVELOPE_VM_ICON */
  #ifdef FEATURE_UI_CHECK_BILLING
#error code not present
  #endif /* FEATURE_UI_CHECK_BILLING */
  #ifdef FEATURE_UI_ONETOUCH_VM_ACCESS
#error code not present
  #endif /* FEATURE_UI_ONETOUCH_VM_ACCESS */
  #ifdef FEATURE_UI_BOOK_TO_PH
#error code not present
  #endif /* FEATURE_UI_BOOK_TO_PH */
  , 0
  #ifdef FEATURE_UI_ENVELOPE_ICON
#error code not present
  #endif /* FEATURE_UI_ENVELOPE_ICON */
  #ifdef FEATURE_DS
  | ADD_BIT_TO_FEATURE_MASK(F_DS_BIT)
  #endif /* FEATURE_DS */
  #ifdef FEATURE_DS_DOTG
#error code not present
  #endif /* FEATURE_DS_DOTG */
  #ifdef FEATURE_DS_IS99_REFL
#error code not present
  #endif /* FEATURE_DS_IS99_REFL */
  #ifdef FEATURE_DSM_MEM_CHK
  | ADD_BIT_TO_FEATURE_MASK(F_DSM_MEM_CHK_BIT)
  #endif /* FEATURE_DSM_MEM_CHK */
  #ifdef FEATURE_DS_ATD_PACK
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ATD_PACK_BIT)
  #endif /* FEATURE_DS_ATD_PACK */
  #ifdef FEATURE_DS_UP
#error code not present
  #endif /* FEATURE_DS_UP */
  #ifdef FEATURE_DS_PSATS
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PSATS_BIT)
  #endif /* FEATURE_DS_PSATS */
  , 0
  #ifdef FEATURE_DS_RPSO
  | ADD_BIT_TO_FEATURE_MASK(F_DS_RPSO_BIT)
  #endif /* FEATURE_DS_RPSO */
  #ifdef FEATURE_DS_MTOM
  | ADD_BIT_TO_FEATURE_MASK(F_DS_MTOM_BIT)
  #endif /* FEATURE_DS_MTOM */
  #ifdef FEATURE_NV_AUTOSIZE
#error code not present
  #endif /* FEATURE_NV_AUTOSIZE */
  #ifdef FEATURE_UI_PRL_VER
  | ADD_BIT_TO_FEATURE_MASK(F_UI_PRL_VER_BIT)
  #endif /* FEATURE_UI_PRL_VER */
  #ifdef FEATURE_UI_PRIVACY_ALERT
#error code not present
  #endif /* FEATURE_UI_PRIVACY_ALERT */
  #ifdef FEATURE_HOLD_PWRKEY_TO_PWRUP
#error code not present
  #endif /* FEATURE_HOLD_PWRKEY_TO_PWRUP */
  #ifdef FEATURE_MULTIPLE_RINGER_TYPES
  | ADD_BIT_TO_FEATURE_MASK(F_MULTIPLE_RINGER_TYPES_BIT)
  #endif /* FEATURE_MULTIPLE_RINGER_TYPES */
  #ifdef FEATURE_REVERSE_UPDOWN_KEYS
#error code not present
  #endif /* FEATURE_REVERSE_UPDOWN_KEYS */
  , 0
  #ifdef FEATURE_SND_RING_SET_1
  | ADD_BIT_TO_FEATURE_MASK(F_SND_RING_SET_1_BIT)
  #endif /* FEATURE_SND_RING_SET_1 */
  #ifdef FEATURE_UI_CALLSTACK_NO_WRAP
#error code not present
  #endif /* FEATURE_UI_CALLSTACK_NO_WRAP */
  #ifdef FEATURE_UI_PWR_MUTES_ALERT
#error code not present
  #endif /* FEATURE_UI_PWR_MUTES_ALERT */
  #ifdef FEATURE_UI_CALL_ANSWER_MODE
#error code not present
  #endif /* FEATURE_UI_CALL_ANSWER_MODE */
  #ifdef FEATURE_HFK_PLUS
#error code not present
  #endif /* FEATURE_HFK_PLUS */
  #ifdef FEATURE_ENHANCED_RINGS
#error code not present
  #endif /* FEATURE_ENHANCED_RINGS */
  #ifdef FEATURE_IDS
#error code not present
  #endif /* FEATURE_IDS */
  #ifdef FEATURE_AGC_LOGGIN
  | ADD_BIT_TO_FEATURE_MASK(F_AGC_LOGGIN_BIT)
  #endif /* FEATURE_AGC_LOGGIN */
  , 0
  #ifdef FEATURE_UI_SNI
  | ADD_BIT_TO_FEATURE_MASK(F_UI_SNI_BIT)
  #endif /* FEATURE_UI_SNI */
  #ifdef FEATURE_VOC_FLIP
#error code not present
  #endif /* FEATURE_VOC_FLIP */
  #ifdef FEATURE_VOC_FLIP_PHONE
#error code not present
  #endif /* FEATURE_VOC_FLIP_PHONE */
  #ifdef FEATURE_AC_LOGGING
  | ADD_BIT_TO_FEATURE_MASK(F_AC_LOGGING_BIT)
  #endif /* FEATURE_AC_LOGGING */
  #ifdef FEATURE_AGC_LOGGING
  | ADD_BIT_TO_FEATURE_MASK(F_AGC_LOGGING_BIT)
  #endif /* FEATURE_AGC_LOGGING */
  #ifdef FEATURE_MC_TIMER_FIX
  | ADD_BIT_TO_FEATURE_MASK(F_MC_TIMER_FIX_BIT)
  #endif /* FEATURE_MC_TIMER_FIX */
  #ifdef FEATURE_SND_RING_SET_2
  | ADD_BIT_TO_FEATURE_MASK(F_SND_RING_SET_2_BIT)
  #endif /* FEATURE_SND_RING_SET_2 */
  #ifdef FEATURE_UI_STAR2_CALL
#error code not present
  #endif /* FEATURE_UI_STAR2_CALL */
  , 0
  #ifdef FEATURE_UI_QUICK_VM_DIAL
#error code not present
  #endif /* FEATURE_UI_QUICK_VM_DIAL */
  #ifdef FEATURE_UI_NON_ZERO_MWN
  | ADD_BIT_TO_FEATURE_MASK(F_UI_NON_ZERO_MWN_BIT)
  #endif /* FEATURE_UI_NON_ZERO_MWN */
  #ifdef FEATURE_UI_MORE_911_NUMBERS
#error code not present
  #endif /* FEATURE_UI_MORE_911_NUMBERS */
  #ifdef FEATURE_UI_CONNECTING_TXT
#error code not present
  #endif /* FEATURE_UI_CONNECTING_TXT */
  #ifdef FEATURE_MWI_DETECT
#error code not present
  #endif /* FEATURE_MWI_DETECT */
  #ifdef FEATURE_HANDLE_FWD_DTMF
  | ADD_BIT_TO_FEATURE_MASK(F_HANDLE_FWD_DTMF_BIT)
  #endif /* FEATURE_HANDLE_FWD_DTMF */
  #ifdef FEATURE_NO_RING_SWITCH
#error code not present
  #endif /* FEATURE_NO_RING_SWITCH */
  #ifdef FEATURE_DEC_DTMF_KEYS
#error code not present
  #endif /* FEATURE_DEC_DTMF_KEYS */
  , 0
  #ifdef FEATURE_ECFM
#error code not present
  #endif /* FEATURE_ECFM */
  #ifdef FEATURE_SINBAD
#error code not present
  #endif /* FEATURE_SINBAD */
  #ifdef FEATURE_IS95B_WLL
#error code not present
  #endif /* FEATURE_IS95B_WLL */
  #ifdef FEATURE_POL_REV
#error code not present
  #endif /* FEATURE_POL_REV */
  #ifdef FEATURE_PRIVACY_ALERT
#error code not present
  #endif /* FEATURE_PRIVACY_ALERT */
  #ifdef FEATURE_FASTPRL
  | ADD_BIT_TO_FEATURE_MASK(F_FASTPRL_BIT)
  #endif /* FEATURE_FASTPRL */
  #ifdef FEATURE_UI_RENTAL_TIMER
#error code not present
  #endif /* FEATURE_UI_RENTAL_TIMER */
  #ifdef FEATURE_NV_I2C
#error code not present
  #endif /* FEATURE_NV_I2C */
  , 0
  #ifdef FEATURE_NO_OTASP_MENU
#error code not present
  #endif /* FEATURE_NO_OTASP_MENU */
  #ifdef FEATURE_UI_SILENT_REDIAL_AMPS
#error code not present
  #endif /* FEATURE_UI_SILENT_REDIAL_AMPS */
  #ifdef FEATURE_AUXROM_MSGS
#error code not present
  #endif /* FEATURE_AUXROM_MSGS */
  #ifdef FEATURE_UI_LIMIT_CALL
#error code not present
  #endif /* FEATURE_UI_LIMIT_CALL */
  #ifdef FEATURE_UI_FORCE_MODE_AMPS_ONLY
#error code not present
  #endif /* FEATURE_UI_FORCE_MODE_AMPS_ONLY */
  #ifdef FEATURE_2700_CAP_FIX
#error code not present
  #endif /* FEATURE_2700_CAP_FIX */
  #ifdef FEATURE_ID
#error code not present
  #endif /* FEATURE_ID */
  #ifdef FEATURE_HOME_ONLY
  | ADD_BIT_TO_FEATURE_MASK(F_HOME_ONLY_BIT)
  #endif /* FEATURE_HOME_ONLY */
  , 0
  #ifdef FEATURE_UI_HOME_ONLY
#error code not present
  #endif /* FEATURE_UI_HOME_ONLY */
  #ifdef FEATURE_PRL_FORCE_MODE
  | ADD_BIT_TO_FEATURE_MASK(F_PRL_FORCE_MODE_BIT)
  #endif /* FEATURE_PRL_FORCE_MODE */
  #ifdef FEATURE_UI_PRL_FORCE_MODE_SEL
#error code not present
  #endif /* FEATURE_UI_PRL_FORCE_MODE_SEL */
  #ifdef FEATURE_UI_DTACO
#error code not present
  #endif /* FEATURE_UI_DTACO */
  #ifdef FEATURE_CHARGER
#error code not present
  #endif /* FEATURE_CHARGER */
  #ifdef FEATURE_UI_STDBY_TIMEOUT
#error code not present
  #endif /* FEATURE_UI_STDBY_TIMEOUT */
  #ifdef FEATURE_UI_SOFT_CALL_FAIL_MSG
#error code not present
  #endif /* FEATURE_UI_SOFT_CALL_FAIL_MSG */
  #ifdef FEATURE_UI_SMS_NO_BOX
#error code not present
  #endif /* FEATURE_UI_SMS_NO_BOX */
  , 0
  #ifdef FEATURE_ADDITIONAL_BACKLIGHT
#error code not present
  #endif /* FEATURE_ADDITIONAL_BACKLIGHT */
  #ifdef FEATURE_DOUBLE_SUBSIDY_LOCK
#error code not present
  #endif /* FEATURE_DOUBLE_SUBSIDY_LOCK */
  #ifdef FEATURE_UI_POWERUP_HOLD_ORIG
#error code not present
  #endif /* FEATURE_UI_POWERUP_HOLD_ORIG */
  #ifdef FEATURE_UI_QC_VERSION
#error code not present
  #endif /* FEATURE_UI_QC_VERSION */
  #ifdef FEATURE_MAX_ACCESS_FALLBACK
  | ADD_BIT_TO_FEATURE_MASK(F_MAX_ACCESS_FALLBACK_BIT)
  #endif /* FEATURE_MAX_ACCESS_FALLBACK */
  #ifdef FEATURE_QC_TGP_SMS_UI
#error code not present
  #endif /* FEATURE_QC_TGP_SMS_UI */
  #ifdef FEATURE_LPM
  | ADD_BIT_TO_FEATURE_MASK(F_LPM_BIT)
  #endif /* FEATURE_LPM */
  #ifdef FEATURE_DS_DOTG_DATA
#error code not present
  #endif /* FEATURE_DS_DOTG_DATA */
  , 0
  #ifdef FEATURE_DS_ATD_PKT
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ATD_PKT_BIT)
  #endif /* FEATURE_DS_ATD_PKT */
  #ifdef FEATURE_NV_WEB_ITEMS
#error code not present
  #endif /* FEATURE_NV_WEB_ITEMS */
  #ifdef FEATURE_DS_PSTATS
#error code not present
  #endif /* FEATURE_DS_PSTATS */
  #ifdef FEATURE_DS_DEBUG_UI
#error code not present
  #endif /* FEATURE_DS_DEBUG_UI */
  #ifdef FEATURE_DS_ORIG_XXX_SO
#error code not present
  #endif /* FEATURE_DS_ORIG_XXX_SO */
  #ifdef FEATURE_DS_CHOOSE_SO
  | ADD_BIT_TO_FEATURE_MASK(F_DS_CHOOSE_SO_BIT)
  #endif /* FEATURE_DS_CHOOSE_SO */
  #ifdef FEATURE_DS_ORIG_PRE707_SO
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ORIG_PRE707_SO_BIT)
  #endif /* FEATURE_DS_ORIG_PRE707_SO */
  #ifdef FEATURE_DS_ORIG_PROPTRY_SO
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ORIG_PROPTRY_SO_BIT)
  #endif /* FEATURE_DS_ORIG_PROPTRY_SO */
  , 0
  #ifdef FEATURE_DS_ORIG_IS707_SO
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ORIG_IS707_SO_BIT)
  #endif /* FEATURE_DS_ORIG_IS707_SO */
  #ifdef FEATURE_DS_QNC
  | ADD_BIT_TO_FEATURE_MASK(F_DS_QNC_BIT)
  #endif /* FEATURE_DS_QNC */
  #ifdef FEATURE_DS_VOICE_AS_DATA
#error code not present
  #endif /* FEATURE_DS_VOICE_AS_DATA */
  #ifdef FEATURE_DS_PCM
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PCM_BIT)
  #endif /* FEATURE_DS_PCM */
  #ifdef FEATURE_DYNAMIC_THROTTLE
  | ADD_BIT_TO_FEATURE_MASK(F_DYNAMIC_THROTTLE_BIT)
  #endif /* FEATURE_DYNAMIC_THROTTLE */
  #ifdef FEATURE_RINGER_ALERT_SETTING
#error code not present
  #endif /* FEATURE_RINGER_ALERT_SETTING */
  #ifdef FEATURE_AUXROM
  | ADD_BIT_TO_FEATURE_MASK(F_AUXROM_BIT)
  #endif /* FEATURE_AUXROM */
  #ifdef FEATURE_E911
  | ADD_BIT_TO_FEATURE_MASK(F_E911_BIT)
  #endif /* FEATURE_E911 */
  , 0
  #ifdef FEATURE_NV_TWO_NAMS_RL_MEDIUM
#error code not present
  #endif /* FEATURE_NV_TWO_NAMS_RL_MEDIUM */
  #ifdef FEATURE_UI_SPECIFY_SND_BTN_NAME
#error code not present
  #endif /* FEATURE_UI_SPECIFY_SND_BTN_NAME */
  #ifdef FEATURE_SSPR_ENHANCEMENTS
  | ADD_BIT_TO_FEATURE_MASK(F_SSPR_ENHANCEMENTS_BIT)
  #endif /* FEATURE_SSPR_ENHANCEMENTS */
  #ifdef FEATURE_IS683A_PRL
  | ADD_BIT_TO_FEATURE_MASK(F_IS683A_PRL_BIT)
  #endif /* FEATURE_IS683A_PRL */
  #ifdef FEATURE_TALK_MSG
#error code not present
  #endif /* FEATURE_TALK_MSG */
  #ifdef FEATURE_UP
#error code not present
  #endif /* FEATURE_UP */
  #ifdef FEATURE_SMS_UP
#error code not present
  #endif /* FEATURE_SMS_UP */
  #ifdef FEATURE_KPCS
  | ADD_BIT_TO_FEATURE_MASK(F_KPCS_BIT)
  #endif /* FEATURE_KPCS */
  , 0
  #ifdef FEATURE_CP_KPCS
  | ADD_BIT_TO_FEATURE_MASK(F_CP_KPCS_BIT)
  #endif /* FEATURE_CP_KPCS */
  #ifdef FEATURE_RF_KPCS
  | ADD_BIT_TO_FEATURE_MASK(F_RF_KPCS_BIT)
  #endif /* FEATURE_RF_KPCS */
  #ifdef FEATURE_DS_
  | ADD_BIT_TO_FEATURE_MASK(F_DS__BIT)
  #endif /* FEATURE_DS_ */
  #ifdef FEATURE_DS_PROPTRY_SO
#error code not present
  #endif /* FEATURE_DS_PROPTRY_SO */
  #ifdef FEATURE_UI_800_SERVICE_PROG
  | ADD_BIT_TO_FEATURE_MASK(F_UI_800_SERVICE_PROG_BIT)
  #endif /* FEATURE_UI_800_SERVICE_PROG */
  #ifdef FEATURE_DS_PAP
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PAP_BIT)
  #endif /* FEATURE_DS_PAP */
  #ifdef FEATURE_VOC_TGP_COEFF
#error code not present
  #endif /* FEATURE_VOC_TGP_COEFF */
  #ifdef FEATURE_UI_RESTRICTED_IN_LIST
#error code not present
  #endif /* FEATURE_UI_RESTRICTED_IN_LIST */
  , 0
  #ifdef FEATURE_WLL_FORCE_DOWNLOAD
#error code not present
  #endif /* FEATURE_WLL_FORCE_DOWNLOAD */
  #ifdef FEATURE_VMAIL_NOTIFICATION
#error code not present
  #endif /* FEATURE_VMAIL_NOTIFICATION */
  #ifdef FEATURE_LCD_WLL
#error code not present
  #endif /* FEATURE_LCD_WLL */
  #ifdef FEATURE_PRL_DOWNLOAD
#error code not present
  #endif /* FEATURE_PRL_DOWNLOAD */
  #ifdef FEATURE_UI_SEVEN_LEVEL_SND
#error code not present
  #endif /* FEATURE_UI_SEVEN_LEVEL_SND */
  #ifdef FEATURE_RSSI_PACKETS
#error code not present
  #endif /* FEATURE_RSSI_PACKETS */
  #ifdef FEATURE_REMOTE_RINGER
#error code not present
  #endif /* FEATURE_REMOTE_RINGER */
  #ifdef FEATURE_SMS_PACKET
  | ADD_BIT_TO_FEATURE_MASK(F_SMS_PACKET_BIT)
  #endif /* FEATURE_SMS_PACKET */
  , 0
  #ifdef FEATURE_DEACTIVATE_SCREEN
#error code not present
  #endif /* FEATURE_DEACTIVATE_SCREEN */
  #ifdef FEATURE_DEACTIVATE_HANDSET
#error code not present
  #endif /* FEATURE_DEACTIVATE_HANDSET */
  #ifdef FEATURE_NV_WRITE_ONLINE
  | ADD_BIT_TO_FEATURE_MASK(F_NV_WRITE_ONLINE_BIT)
  #endif /* FEATURE_NV_WRITE_ONLINE */
  #ifdef FEATURE_CALL_INFO_PACKET
#error code not present
  #endif /* FEATURE_CALL_INFO_PACKET */
  #ifdef FEATURE_AUDIO_CONTROL
#error code not present
  #endif /* FEATURE_AUDIO_CONTROL */
  #ifdef FEATURE_AKEY_PACKET
#error code not present
  #endif /* FEATURE_AKEY_PACKET */
  #ifdef FEATURE_BEGINNING_FLAG
#error code not present
  #endif /* FEATURE_BEGINNING_FLAG */
  #ifdef FEATURE_MOD_DO_NOT_POWER_DOWN
#error code not present
  #endif /* FEATURE_MOD_DO_NOT_POWER_DOWN */
  , 0
  #ifdef FEATURE_NV_TWO_NAMS_RL_SMALL
  | ADD_BIT_TO_FEATURE_MASK(F_NV_TWO_NAMS_RL_SMALL_BIT)
  #endif /* FEATURE_NV_TWO_NAMS_RL_SMALL */
  #ifdef FEATURE_MOD_GENERIC_PKT
#error code not present
  #endif /* FEATURE_MOD_GENERIC_PKT */
  #ifdef FEATURE_QMIP
#error code not present
  #endif /* FEATURE_QMIP */
  #ifdef FEATURE_NEW_MOD_PACKETS
#error code not present
  #endif /* FEATURE_NEW_MOD_PACKETS */
  #ifdef FEATURE_UI_IGNORE_LOW_BATT_WITH
#error code not present
  #endif /* FEATURE_UI_IGNORE_LOW_BATT_WITH */
  #ifdef FEATURE_UI_LOW_BATT_W_EXT_PWR
  | ADD_BIT_TO_FEATURE_MASK(F_UI_LOW_BATT_W_EXT_PWR_BIT)
  #endif /* FEATURE_UI_LOW_BATT_W_EXT_PWR */
  #ifdef FEATURE_ODIE_FONT
  | ADD_BIT_TO_FEATURE_MASK(F_ODIE_FONT_BIT)
  #endif /* FEATURE_ODIE_FONT */
  #ifdef FEATURE_UI_ODIE_AKEY
#error code not present
  #endif /* FEATURE_UI_ODIE_AKEY */
  , 0
  #ifdef FEATURE_UI_NO_EARPC
#error code not present
  #endif /* FEATURE_UI_NO_EARPC */
  #ifdef FEATURE_UI_5GP_MENU
#error code not present
  #endif /* FEATURE_UI_5GP_MENU */
  #ifdef FEATURE_UI_KEYGUARD
#error code not present
  #endif /* FEATURE_UI_KEYGUARD */
  #ifdef FEATURE_UI_ANIMATE_SEARCH
#error code not present
  #endif /* FEATURE_UI_ANIMATE_SEARCH */
  #ifdef FEATURE_UI_ANIMATE_CALL
#error code not present
  #endif /* FEATURE_UI_ANIMATE_CALL */
  #ifdef FEATURE_UI_RESTRICT_TO_BOOK
#error code not present
  #endif /* FEATURE_UI_RESTRICT_TO_BOOK */
  #ifdef FEATURE_ONE_TOUCH_MUTE
#error code not present
  #endif /* FEATURE_ONE_TOUCH_MUTE */
  #ifdef FEATURE_UI_BAR_PHONE
#error code not present
  #endif /* FEATURE_UI_BAR_PHONE */
  , 0
  #ifdef FEATURE_EVRC
  | ADD_BIT_TO_FEATURE_MASK(F_EVRC_BIT)
  #endif /* FEATURE_EVRC */
  #ifdef FEATURE_UI_RESTRICT_TO_PHONEBOO
#error code not present
  #endif /* FEATURE_UI_RESTRICT_TO_PHONEBOO */
  #ifdef FEATURE_UI_LANG_FRENCH
#error code not present
  #endif /* FEATURE_UI_LANG_FRENCH */
  #ifdef FEATURE_UI_LANG_SPANISH
#error code not present
  #endif /* FEATURE_UI_LANG_SPANISH */
  #ifdef FEATURE_UI_LANG_PORTUGUESE
#error code not present
  #endif /* FEATURE_UI_LANG_PORTUGUESE */
  #ifdef FEATURE_UI_MULTI_LANG
#error code not present
  #endif /* FEATURE_UI_MULTI_LANG */
  #ifdef FEATURE_UI_ENVELOPE_
#error code not present
  #endif /* FEATURE_UI_ENVELOPE_ */
  #ifdef FEATURE_UI_REVERSE_UPDOWN
#error code not present
  #endif /* FEATURE_UI_REVERSE_UPDOWN */
  , 0
  #ifdef FEATURE_TTY_TEST
  | ADD_BIT_TO_FEATURE_MASK(F_TTY_TEST_BIT)
  #endif /* FEATURE_TTY_TEST */
  #ifdef FEATURE_ANALOG_DATA
#error code not present
  #endif /* FEATURE_ANALOG_DATA */
  #ifdef FEATURE_IS95B_WLL_ONLY
#error code not present
  #endif /* FEATURE_IS95B_WLL_ONLY */
  #ifdef FEATURE_BORSCHT
#error code not present
  #endif /* FEATURE_BORSCHT */
  #ifdef FEATURE_REN
#error code not present
  #endif /* FEATURE_REN */
  #ifdef FEATURE_UI_PRIMCO_OPTCALL_MENU
#error code not present
  #endif /* FEATURE_UI_PRIMCO_OPTCALL_MENU */
  #ifdef FEATURE_UI_3RD_LINE_IDLE_TXT
#error code not present
  #endif /* FEATURE_UI_3RD_LINE_IDLE_TXT */
  #ifdef FEATURE_UI_MENU_FEATURES_TXT
#error code not present
  #endif /* FEATURE_UI_MENU_FEATURES_TXT */
  , 0
  #ifdef FEATURE_UI_TOP_LVL_SHORT_MENU
#error code not present
  #endif /* FEATURE_UI_TOP_LVL_SHORT_MENU */
  #ifdef FEATURE_SINGLE_NAM
#error code not present
  #endif /* FEATURE_SINGLE_NAM */
  #ifdef FEATURE_BILLING
#error code not present
  #endif /* FEATURE_BILLING */
  #ifdef FEATURE_VOLUME
#error code not present
  #endif /* FEATURE_VOLUME */
  #ifdef FEATURE_ONE_TOUCH_SMS
#error code not present
  #endif /* FEATURE_ONE_TOUCH_SMS */
  #ifdef FEATURE_EXTRA_ALERTS
#error code not present
  #endif /* FEATURE_EXTRA_ALERTS */
  #ifdef FEATURE_UI_CALL_LOG
#error code not present
  #endif /* FEATURE_UI_CALL_LOG */
  #ifdef FEATURE_OTASP_228
#error code not present
  #endif /* FEATURE_OTASP_228 */
  , 0
  #ifdef FEATURE_CUSTOM_FAIL_TONES
#error code not present
  #endif /* FEATURE_CUSTOM_FAIL_TONES */
  #ifdef FEATURE_CUSTOM_INFO
#error code not present
  #endif /* FEATURE_CUSTOM_INFO */
  #ifdef FEATURE_CUSTOM_PAUSES
#error code not present
  #endif /* FEATURE_CUSTOM_PAUSES */
  #ifdef FEATURE_CUSTOM_XTRA_EMERGENCY
#error code not present
  #endif /* FEATURE_CUSTOM_XTRA_EMERGENCY */
  #ifdef FEATURE_CLEAR_SMS
#error code not present
  #endif /* FEATURE_CLEAR_SMS */
  #ifdef FEATURE_PHONUMBER
#error code not present
  #endif /* FEATURE_PHONUMBER */
  #ifdef FEATURE_UI_FORCE_MODE_ALT_TXT
#error code not present
  #endif /* FEATURE_UI_FORCE_MODE_ALT_TXT */
  #ifdef FEATURE_UI_VMN_CALLBACK_DISPLAY
#error code not present
  #endif /* FEATURE_UI_VMN_CALLBACK_DISPLAY */
  , 0
  #ifdef FEATURE_UI_AMPM_DISPLAY
#error code not present
  #endif /* FEATURE_UI_AMPM_DISPLAY */
  #ifdef FEATURE_OTASP_2
#error code not present
  #endif /* FEATURE_OTASP_2 */
  #ifdef FEATURE_CUSTOM_OTASP
#error code not present
  #endif /* FEATURE_CUSTOM_OTASP */
  #ifdef FEATURE_SMS_BEEP
#error code not present
  #endif /* FEATURE_SMS_BEEP */
  #ifdef FEATURE_CONNECTING_MSG
#error code not present
  #endif /* FEATURE_CONNECTING_MSG */
  #ifdef FEATURE_NOICON_KEYGUARD
#error code not present
  #endif /* FEATURE_NOICON_KEYGUARD */
  #ifdef FEATURE_S_TYPE_ROAM_ALERT
#error code not present
  #endif /* FEATURE_S_TYPE_ROAM_ALERT */
  #ifdef FEATURE_SEND_TONE
#error code not present
  #endif /* FEATURE_SEND_TONE */
  , 0
  #ifdef FEATURE_NO_AUTO_MUTE
#error code not present
  #endif /* FEATURE_NO_AUTO_MUTE */
  #ifdef FEATURE_LOCK_PHONE_OFF
#error code not present
  #endif /* FEATURE_LOCK_PHONE_OFF */
  #ifdef FEATURE_NO_AUTO_ANSWER
#error code not present
  #endif /* FEATURE_NO_AUTO_ANSWER */
  #ifdef FEATURE_NO_ANY_KEY
#error code not present
  #endif /* FEATURE_NO_ANY_KEY */
  #ifdef FEATURE_HARDCODED_NUMBERS
#error code not present
  #endif /* FEATURE_HARDCODED_NUMBERS */
  #ifdef FEATURE_1_2_TOUCH_VOICE_MAIL
#error code not present
  #endif /* FEATURE_1_2_TOUCH_VOICE_MAIL */
  #ifdef FEATURE_2TALKS_FOR_REDIAL
#error code not present
  #endif /* FEATURE_2TALKS_FOR_REDIAL */
  #ifdef FEATURE_UI_SPRINT_BEEP_MENU
#error code not present
  #endif /* FEATURE_UI_SPRINT_BEEP_MENU */
  , 0
  #ifdef FEATURE_SIMPLE_SMS_MESSAGES
#error code not present
  #endif /* FEATURE_SIMPLE_SMS_MESSAGES */
  #ifdef FEATURE_NO_DUPLICATE_ALERT
#error code not present
  #endif /* FEATURE_NO_DUPLICATE_ALERT */
  #ifdef FEATURE_PHONE_LIST
#error code not present
  #endif /* FEATURE_PHONE_LIST */
  #ifdef FEATURE_UI_FORCE_MODE_SP_TXT
#error code not present
  #endif /* FEATURE_UI_FORCE_MODE_SP_TXT */
  #ifdef FEATURE_VOC_LYNX
#error code not present
  #endif /* FEATURE_VOC_LYNX */
  #ifdef FEATURE_TCXO_CLOCK
  | ADD_BIT_TO_FEATURE_MASK(F_TCXO_CLOCK_BIT)
  #endif /* FEATURE_TCXO_CLOCK */
  #ifdef FEATURE_UI_PWR_ANS_CALL
#error code not present
  #endif /* FEATURE_UI_PWR_ANS_CALL */
  #ifdef FEATURE_UI_ONE_TOUCH_MUTE
#error code not present
  #endif /* FEATURE_UI_ONE_TOUCH_MUTE */
  , 0
  #ifdef FEATURE_FAST_PRL
#error code not present
  #endif /* FEATURE_FAST_PRL */
  #ifdef FEATURE_UI_FULL_SYSTEM_PREF
  | ADD_BIT_TO_FEATURE_MASK(F_UI_FULL_SYSTEM_PREF_BIT)
  #endif /* FEATURE_UI_FULL_SYSTEM_PREF */
  #ifdef FEATURE_NEW_SLEEP_TIMELINE
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_SLEEP_TIMELINE_BIT)
  #endif /* FEATURE_NEW_SLEEP_TIMELINE */
  #ifdef FEATURE_DH
  | ADD_BIT_TO_FEATURE_MASK(F_DH_BIT)
  #endif /* FEATURE_DH */
  #ifdef FEATURE_REX_SIG32
  | ADD_BIT_TO_FEATURE_MASK(F_REX_SIG32_BIT)
  #endif /* FEATURE_REX_SIG32 */
  #ifdef FEATURE_SAVE_SMS
  | ADD_BIT_TO_FEATURE_MASK(F_SAVE_SMS_BIT)
  #endif /* FEATURE_SAVE_SMS */
  #ifdef FEATURE_UI_SMS_NV_RESERVATION
#error code not present
  #endif /* FEATURE_UI_SMS_NV_RESERVATION */
  #ifdef FEATURE_NV_TWO_NAMS_RL_LARGE
  | ADD_BIT_TO_FEATURE_MASK(F_NV_TWO_NAMS_RL_LARGE_BIT)
  #endif /* FEATURE_NV_TWO_NAMS_RL_LARGE */
  , 0
  #ifdef FEATURE_UI_HS_AUTO_ANSWER
#error code not present
  #endif /* FEATURE_UI_HS_AUTO_ANSWER */
  #ifdef FEATURE_UART_POWERDOWN
  | ADD_BIT_TO_FEATURE_MASK(F_UART_POWERDOWN_BIT)
  #endif /* FEATURE_UART_POWERDOWN */
  #ifdef FEATURE_ENHANCED_STANDBY
  | ADD_BIT_TO_FEATURE_MASK(F_ENHANCED_STANDBY_BIT)
  #endif /* FEATURE_ENHANCED_STANDBY */
  #ifdef FEATURE_FAST_WARMUP
  | ADD_BIT_TO_FEATURE_MASK(F_FAST_WARMUP_BIT)
  #endif /* FEATURE_FAST_WARMUP */
  #ifdef FEATURE_UI_FORCE_MODE_TEMP_AMPS
#error code not present
  #endif /* FEATURE_UI_FORCE_MODE_TEMP_AMPS */
  #ifdef FEATURE_MINIBROWSER_ITEM
#error code not present
  #endif /* FEATURE_MINIBROWSER_ITEM */
  #ifdef FEATURE_MC_SILENT_REDIAL_AMPS
  | ADD_BIT_TO_FEATURE_MASK(F_MC_SILENT_REDIAL_AMPS_BIT)
  #endif /* FEATURE_MC_SILENT_REDIAL_AMPS */
  #ifdef FEATURE_VR_HFK
  | ADD_BIT_TO_FEATURE_MASK(F_VR_HFK_BIT)
  #endif /* FEATURE_VR_HFK */
  , 0
  #ifdef FEATURE_UI_NEW_CH
#error code not present
  #endif /* FEATURE_UI_NEW_CH */
  #ifdef FEATURE_UI_NEW_PB
#error code not present
  #endif /* FEATURE_UI_NEW_PB */
  #ifdef FEATURE_UI_GENERIC_VM_DIAL
#error code not present
  #endif /* FEATURE_UI_GENERIC_VM_DIAL */
  #ifdef FEATURE_ANALOG_FAX
#error code not present
  #endif /* FEATURE_ANALOG_FAX */
  #ifdef FEATURE_METER_TONE
#error code not present
  #endif /* FEATURE_METER_TONE */
  #ifdef FEATURE_DSP_ANS_DET
#error code not present
  #endif /* FEATURE_DSP_ANS_DET */
  #ifdef FEATURE_ADSP_EVRC_AUXROM
#error code not present
  #endif /* FEATURE_ADSP_EVRC_AUXROM */
  #ifdef FEATURE_VOC_PANTHER
  | ADD_BIT_TO_FEATURE_MASK(F_VOC_PANTHER_BIT)
  #endif /* FEATURE_VOC_PANTHER */
  , 0
  #ifdef FEATURE_SBI
  | ADD_BIT_TO_FEATURE_MASK(F_SBI_BIT)
  #endif /* FEATURE_SBI */
  #ifdef FEATURE_SLEEP_32KHZ
  | ADD_BIT_TO_FEATURE_MASK(F_SLEEP_32KHZ_BIT)
  #endif /* FEATURE_SLEEP_32KHZ */
  #ifdef FEATURE_FM_SLOTTED
  | ADD_BIT_TO_FEATURE_MASK(F_FM_SLOTTED_BIT)
  #endif /* FEATURE_FM_SLOTTED */
  #ifdef FEATURE_RAN_USE_BOOTDATA_1_4
  | ADD_BIT_TO_FEATURE_MASK(F_RAN_USE_BOOTDATA_1_4_BIT)
  #endif /* FEATURE_RAN_USE_BOOTDATA_1_4 */
  #ifdef FEATURE_EFS
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_BIT)
  #endif /* FEATURE_EFS */
  #ifdef FEATURE_TCXO1920
  | ADD_BIT_TO_FEATURE_MASK(F_TCXO1920_BIT)
  #endif /* FEATURE_TCXO1920 */
  #ifdef FEATURE_SSPR_800
  | ADD_BIT_TO_FEATURE_MASK(F_SSPR_800_BIT)
  #endif /* FEATURE_SSPR_800 */
  #ifdef FEATURE_AVAIL_HOME_SIDE_PREF
  | ADD_BIT_TO_FEATURE_MASK(F_AVAIL_HOME_SIDE_PREF_BIT)
  #endif /* FEATURE_AVAIL_HOME_SIDE_PREF */
  , 0
  #ifdef FEATURE_VOC_SAT_CONTROL
  | ADD_BIT_TO_FEATURE_MASK(F_VOC_SAT_CONTROL_BIT)
  #endif /* FEATURE_VOC_SAT_CONTROL */
  #ifdef FEATURE_IS2000
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_BIT)
  #endif /* FEATURE_IS2000 */
  #ifdef FEATURE_IS95B
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_BIT)
  #endif /* FEATURE_IS95B */
  #ifdef FEATURE_TMSI
  | ADD_BIT_TO_FEATURE_MASK(F_TMSI_BIT)
  #endif /* FEATURE_TMSI */
  #ifdef FEATURE_ENHANCED_STANDBY_III
  | ADD_BIT_TO_FEATURE_MASK(F_ENHANCED_STANDBY_III_BIT)
  #endif /* FEATURE_ENHANCED_STANDBY_III */
  #ifdef FEATURE_DATA_TIMELINE_ADVANCE
  | ADD_BIT_TO_FEATURE_MASK(F_DATA_TIMELINE_ADVANCE_BIT)
  #endif /* FEATURE_DATA_TIMELINE_ADVANCE */
  #ifdef FEATURE_DIAG_RESTART_CONFIG
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_RESTART_CONFIG_BIT)
  #endif /* FEATURE_DIAG_RESTART_CONFIG */
  #ifdef FEATURE_SCH_TRIAGE
  | ADD_BIT_TO_FEATURE_MASK(F_SCH_TRIAGE_BIT)
  #endif /* FEATURE_SCH_TRIAGE */
  , 0
  #ifdef FEATURE_CS_ACTION_TIME_TRANS
  | ADD_BIT_TO_FEATURE_MASK(F_CS_ACTION_TIME_TRANS_BIT)
  #endif /* FEATURE_CS_ACTION_TIME_TRANS */
  #ifdef FEATURE_DS_MEM_CHK
  | ADD_BIT_TO_FEATURE_MASK(F_DS_MEM_CHK_BIT)
  #endif /* FEATURE_DS_MEM_CHK */
  #ifdef FEATURE_TC_8X_SEARCHER
  | ADD_BIT_TO_FEATURE_MASK(F_TC_8X_SEARCHER_BIT)
  #endif /* FEATURE_TC_8X_SEARCHER */
  #ifdef FEATURE_SRCH_DYNAMIC_BAND_CLASS
  | ADD_BIT_TO_FEATURE_MASK(F_SRCH_DYNAMIC_BAND_CLASS_BIT)
  #endif /* FEATURE_SRCH_DYNAMIC_BAND_CLASS */
  #ifdef FEATURE_IS2000_R_SCH
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_R_SCH_BIT)
  #endif /* FEATURE_IS2000_R_SCH */
  #ifdef FEATURE_DS_PPP_TERM_REQ_DROP
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PPP_TERM_REQ_DROP_BIT)
  #endif /* FEATURE_DS_PPP_TERM_REQ_DROP */
  #ifdef FEATURE_IS2000_TDSO
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_TDSO_BIT)
  #endif /* FEATURE_IS2000_TDSO */
  #ifdef FEATURE_RELATIVE_DMOD_POS
  | ADD_BIT_TO_FEATURE_MASK(F_RELATIVE_DMOD_POS_BIT)
  #endif /* FEATURE_RELATIVE_DMOD_POS */
  , 0
  #ifdef FEATURE_RDA_CORRECTION
  | ADD_BIT_TO_FEATURE_MASK(F_RDA_CORRECTION_BIT)
  #endif /* FEATURE_RDA_CORRECTION */
  #ifdef FEATURE_IS2000_QPCH
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_QPCH_BIT)
  #endif /* FEATURE_IS2000_QPCH */
  #ifdef FEATURE_IS2000_SCH_STATS
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_SCH_STATS_BIT)
  #endif /* FEATURE_IS2000_SCH_STATS */
  #ifdef FEATURE_DIAG_QCT_EXT
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_QCT_EXT_BIT)
  #endif /* FEATURE_DIAG_QCT_EXT */
  #ifdef FEATURE_DS_CHAP
  | ADD_BIT_TO_FEATURE_MASK(F_DS_CHAP_BIT)
  #endif /* FEATURE_DS_CHAP */
  #ifdef FEATURE_BROADCAST_SMS
  | ADD_BIT_TO_FEATURE_MASK(F_BROADCAST_SMS_BIT)
  #endif /* FEATURE_BROADCAST_SMS */
  #ifdef FEATURE_WCARD_SID_MGMT
  | ADD_BIT_TO_FEATURE_MASK(F_WCARD_SID_MGMT_BIT)
  #endif /* FEATURE_WCARD_SID_MGMT */
  #ifdef FEATURE_OTASP_OTAPA
  | ADD_BIT_TO_FEATURE_MASK(F_OTASP_OTAPA_BIT)
  #endif /* FEATURE_OTASP_OTAPA */
  , 0
  #ifdef FEATURE_NONSLOT_OFREQ_NSRCH
  | ADD_BIT_TO_FEATURE_MASK(F_NONSLOT_OFREQ_NSRCH_BIT)
  #endif /* FEATURE_NONSLOT_OFREQ_NSRCH */
  #ifdef FEATURE_DEFAULT_BIT_RATE_38400
#error code not present
  #endif /* FEATURE_DEFAULT_BIT_RATE_38400 */
  #ifdef FEATURE_JTAG_DEBUG
  | ADD_BIT_TO_FEATURE_MASK(F_JTAG_DEBUG_BIT)
  #endif /* FEATURE_JTAG_DEBUG */
  #ifdef FEATURE_REX_PREEMPT_INTS
  | ADD_BIT_TO_FEATURE_MASK(F_REX_PREEMPT_INTS_BIT)
  #endif /* FEATURE_REX_PREEMPT_INTS */
  #ifdef FEATURE_DIAG_V7_LOG_COMPATIBILI
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_V7_LOG_COMPATIBILI_BIT)
  #endif /* FEATURE_DIAG_V7_LOG_COMPATIBILI */
  #ifdef FEATURE_DIAG_V7_LOG_IFACE
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_V7_LOG_IFACE_BIT)
  #endif /* FEATURE_DIAG_V7_LOG_IFACE */
  #ifdef FEATURE_KEYPRESS_OPTIMIZATION
  | ADD_BIT_TO_FEATURE_MASK(F_KEYPRESS_OPTIMIZATION_BIT)
  #endif /* FEATURE_KEYPRESS_OPTIMIZATION */
  #ifdef FEATURE_DS_UI_BAUD
  | ADD_BIT_TO_FEATURE_MASK(F_DS_UI_BAUD_BIT)
  #endif /* FEATURE_DS_UI_BAUD */
  , 0
  #ifdef FEATURE_DS_DEFAULT_BITRATE_NV
  | ADD_BIT_TO_FEATURE_MASK(F_DS_DEFAULT_BITRATE_NV_BIT)
  #endif /* FEATURE_DS_DEFAULT_BITRATE_NV */
  #ifdef FEATURE_SDEVMAP_SHARE_HFK
  | ADD_BIT_TO_FEATURE_MASK(F_SDEVMAP_SHARE_HFK_BIT)
  #endif /* FEATURE_SDEVMAP_SHARE_HFK */
  #ifdef FEATURE_SDEVMAP_UI_MENU
  | ADD_BIT_TO_FEATURE_MASK(F_SDEVMAP_UI_MENU_BIT)
  #endif /* FEATURE_SDEVMAP_UI_MENU */
  #ifdef FEATURE_SDEVMAP_MENU_ITEM_NV
  | ADD_BIT_TO_FEATURE_MASK(F_SDEVMAP_MENU_ITEM_NV_BIT)
  #endif /* FEATURE_SDEVMAP_MENU_ITEM_NV */
  #ifdef FEATURE_DIAG_UI_BAUD
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_UI_BAUD_BIT)
  #endif /* FEATURE_DIAG_UI_BAUD */
  #ifdef FEATURE_DIAG_DEFAULT_BITRATE_NV
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_DEFAULT_BITRATE_NV_BIT)
  #endif /* FEATURE_DIAG_DEFAULT_BITRATE_NV */
  #ifdef FEATURE_DETECT_SUP_MUTING
  | ADD_BIT_TO_FEATURE_MASK(F_DETECT_SUP_MUTING_BIT)
  #endif /* FEATURE_DETECT_SUP_MUTING */
  #ifdef FEATURE_OTASP_HOLD_CMD_IN_COMMI
  | ADD_BIT_TO_FEATURE_MASK(F_OTASP_HOLD_CMD_IN_COMMI_BIT)
  #endif /* FEATURE_OTASP_HOLD_CMD_IN_COMMI */
  , 0
  #ifdef FEATURE_UI_8K_SUPPORT
  | ADD_BIT_TO_FEATURE_MASK(F_UI_8K_SUPPORT_BIT)
  #endif /* FEATURE_UI_8K_SUPPORT */
  #ifdef FEATURE_UI_8K_VOICE_SUPPORT
  | ADD_BIT_TO_FEATURE_MASK(F_UI_8K_VOICE_SUPPORT_BIT)
  #endif /* FEATURE_UI_8K_VOICE_SUPPORT */
  #ifdef FEATURE_UI_DEBUG_SLOTTED_MODE
#error code not present
  #endif /* FEATURE_UI_DEBUG_SLOTTED_MODE */
  #ifdef FEATURE_SEARCH2
#error code not present
  #endif /* FEATURE_SEARCH2 */
  #ifdef FEATURE_SEARCH2_ACQ
#error code not present
  #endif /* FEATURE_SEARCH2_ACQ */
  #ifdef FEATURE_SEARCH2_IDLE
#error code not present
  #endif /* FEATURE_SEARCH2_IDLE */
  #ifdef FEATURE_UART_TCXO_CLK_FREQ
  | ADD_BIT_TO_FEATURE_MASK(F_UART_TCXO_CLK_FREQ_BIT)
  #endif /* FEATURE_UART_TCXO_CLK_FREQ */
  #ifdef FEATURE_DIAG_DEFAULT_BITRATE_38
#error code not present
  #endif /* FEATURE_DIAG_DEFAULT_BITRATE_38 */
  , 0
  #ifdef FEATURE_DIAG_NON_STREAMING
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_NON_STREAMING_BIT)
  #endif /* FEATURE_DIAG_NON_STREAMING */
  #ifdef FEATURE_DIAG_NO_EVENTS
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_NO_EVENTS_BIT)
  #endif /* FEATURE_DIAG_NO_EVENTS */
  #ifdef FEATURE_RLGC
  | ADD_BIT_TO_FEATURE_MASK(F_RLGC_BIT)
  #endif /* FEATURE_RLGC */
  #ifdef FEATURE_INT_25_FIQ
  | ADD_BIT_TO_FEATURE_MASK(F_INT_25_FIQ_BIT)
  #endif /* FEATURE_INT_25_FIQ */
  #ifdef FEATURE_SPECIAL_MDR
  | ADD_BIT_TO_FEATURE_MASK(F_SPECIAL_MDR_BIT)
  #endif /* FEATURE_SPECIAL_MDR */
  #ifdef FEATURE_VIRTUAL_COMBINER
  | ADD_BIT_TO_FEATURE_MASK(F_VIRTUAL_COMBINER_BIT)
  #endif /* FEATURE_VIRTUAL_COMBINER */
  #ifdef FEATURE_SERIAL_DEVICE_MAPPER
  | ADD_BIT_TO_FEATURE_MASK(F_SERIAL_DEVICE_MAPPER_BIT)
  #endif /* FEATURE_SERIAL_DEVICE_MAPPER */
  #ifdef FEATURE_IS95B_ACC_PRB_BKOFF_DLY
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_ACC_PRB_BKOFF_DLY_BIT)
  #endif /* FEATURE_IS95B_ACC_PRB_BKOFF_DLY */
  , 0
  #ifdef FEATURE_DH_EXP
  | ADD_BIT_TO_FEATURE_MASK(F_DH_EXP_BIT)
  #endif /* FEATURE_DH_EXP */
  #ifdef FEATURE_GSRM_SVC_IND
  | ADD_BIT_TO_FEATURE_MASK(F_GSRM_SVC_IND_BIT)
  #endif /* FEATURE_GSRM_SVC_IND */
  #ifdef FEATURE_EVRC_SO_MGMT
  | ADD_BIT_TO_FEATURE_MASK(F_EVRC_SO_MGMT_BIT)
  #endif /* FEATURE_EVRC_SO_MGMT */
  #ifdef FEATURE_DSM_DIAG_ITEMS
  | ADD_BIT_TO_FEATURE_MASK(F_DSM_DIAG_ITEMS_BIT)
  #endif /* FEATURE_DSM_DIAG_ITEMS */
  #ifdef FEATURE_DS_AT_TEST_ONLY
  | ADD_BIT_TO_FEATURE_MASK(F_DS_AT_TEST_ONLY_BIT)
  #endif /* FEATURE_DS_AT_TEST_ONLY */
  #ifdef FEATURE_DS_TEST_MEM_POOL
  | ADD_BIT_TO_FEATURE_MASK(F_DS_TEST_MEM_POOL_BIT)
  #endif /* FEATURE_DS_TEST_MEM_POOL */
  #ifdef FEATURE_DS_BROWSER_INTERFACE
#error code not present
  #endif /* FEATURE_DS_BROWSER_INTERFACE */
  #ifdef FEATURE_DS_NET_MODEL
  | ADD_BIT_TO_FEATURE_MASK(F_DS_NET_MODEL_BIT)
  #endif /* FEATURE_DS_NET_MODEL */
  , 0
  #ifdef FEATURE_DS_PAP_NV
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PAP_NV_BIT)
  #endif /* FEATURE_DS_PAP_NV */
  #ifdef FEATURE_DS_PZID_RECON
  | ADD_BIT_TO_FEATURE_MASK(F_DS_PZID_RECON_BIT)
  #endif /* FEATURE_DS_PZID_RECON */
  #ifdef FEATURE_DS_CTA_DCD_ASSERT
  | ADD_BIT_TO_FEATURE_MASK(F_DS_CTA_DCD_ASSERT_BIT)
  #endif /* FEATURE_DS_CTA_DCD_ASSERT */
  #ifdef FEATURE_DS_SOCKETS
  | ADD_BIT_TO_FEATURE_MASK(F_DS_SOCKETS_BIT)
  #endif /* FEATURE_DS_SOCKETS */
  #ifdef FEATURE_DS_FADE_DORMANCY
  | ADD_BIT_TO_FEATURE_MASK(F_DS_FADE_DORMANCY_BIT)
  #endif /* FEATURE_DS_FADE_DORMANCY */
  #ifdef FEATURE_AUTOBAUD
  | ADD_BIT_TO_FEATURE_MASK(F_AUTOBAUD_BIT)
  #endif /* FEATURE_AUTOBAUD */
  #ifdef FEATURE_DS_CM
  | ADD_BIT_TO_FEATURE_MASK(F_DS_CM_BIT)
  #endif /* FEATURE_DS_CM */
  #ifdef FEATURE_CM_PWRUP_HOLD_ORIG
  | ADD_BIT_TO_FEATURE_MASK(F_CM_PWRUP_HOLD_ORIG_BIT)
  #endif /* FEATURE_CM_PWRUP_HOLD_ORIG */
  , 0
  #ifdef FEATURE_CM_PREF_SRV_HOLD_ORIG
  | ADD_BIT_TO_FEATURE_MASK(F_CM_PREF_SRV_HOLD_ORIG_BIT)
  #endif /* FEATURE_CM_PREF_SRV_HOLD_ORIG */
  #ifdef FEATURE_CM_SILENT_REDIAL
  | ADD_BIT_TO_FEATURE_MASK(F_CM_SILENT_REDIAL_BIT)
  #endif /* FEATURE_CM_SILENT_REDIAL */
  #ifdef FEATURE_UASMS
#error code not present
  #endif /* FEATURE_UASMS */
  #ifdef FEATURE_CM
  | ADD_BIT_TO_FEATURE_MASK(F_CM_BIT)
  #endif /* FEATURE_CM */
  #ifdef FEATURE_TX_ACCESS_POWER_FIX
  | ADD_BIT_TO_FEATURE_MASK(F_TX_ACCESS_POWER_FIX_BIT)
  #endif /* FEATURE_TX_ACCESS_POWER_FIX */
  #ifdef FEATURE_SLEEP_SLOW_CLOCK
  | ADD_BIT_TO_FEATURE_MASK(F_SLEEP_SLOW_CLOCK_BIT)
  #endif /* FEATURE_SLEEP_SLOW_CLOCK */
  #ifdef FEATURE_SLEEP_SLOW_CLOCK_1P92_3
  | ADD_BIT_TO_FEATURE_MASK(F_SLEEP_SLOW_CLOCK_1P92_3_BIT)
  #endif /* FEATURE_SLEEP_SLOW_CLOCK_1P92_3 */
  #ifdef FEATURE_TCXO_SHUTDOWN
#error code not present
  #endif /* FEATURE_TCXO_SHUTDOWN */
  , 0
  #ifdef FEATURE_ICE_DEBUG
  | ADD_BIT_TO_FEATURE_MASK(F_ICE_DEBUG_BIT)
  #endif /* FEATURE_ICE_DEBUG */
  #ifdef FEATURE_CPU_CLK_27MHZ
  | ADD_BIT_TO_FEATURE_MASK(F_CPU_CLK_27MHZ_BIT)
  #endif /* FEATURE_CPU_CLK_27MHZ */
  #ifdef FEATURE_CPU_CLK_DIV1
  | ADD_BIT_TO_FEATURE_MASK(F_CPU_CLK_DIV1_BIT)
  #endif /* FEATURE_CPU_CLK_DIV1 */
  #ifdef FEATURE_NEW_SIO
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_SIO_BIT)
  #endif /* FEATURE_NEW_SIO */
  #ifdef FEATURE_SECOND_UART
  | ADD_BIT_TO_FEATURE_MASK(F_SECOND_UART_BIT)
  #endif /* FEATURE_SECOND_UART */
  #ifdef FEATURE_SIO_PNP
#error code not present
  #endif /* FEATURE_SIO_PNP */
  #ifdef FEATURE_SIO_DTR_HIGH_GPIO
  | ADD_BIT_TO_FEATURE_MASK(F_SIO_DTR_HIGH_GPIO_BIT)
  #endif /* FEATURE_SIO_DTR_HIGH_GPIO */
  #ifdef FEATURE_SIO_DTR_ACTIVE_LOW
  | ADD_BIT_TO_FEATURE_MASK(F_SIO_DTR_ACTIVE_LOW_BIT)
  #endif /* FEATURE_SIO_DTR_ACTIVE_LOW */
  , 0
  #ifdef FEATURE_IS95B_TRUE_IMSI
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_TRUE_IMSI_BIT)
  #endif /* FEATURE_IS95B_TRUE_IMSI */
  #ifdef FEATURE_IS95B_OLPEC
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_OLPEC_BIT)
  #endif /* FEATURE_IS95B_OLPEC */
  #ifdef FEATURE_IS95B_SYS_RESELEC
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_SYS_RESELEC_BIT)
  #endif /* FEATURE_IS95B_SYS_RESELEC */
  #ifdef FEATURE_IS95B_SOFT_HO
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_SOFT_HO_BIT)
  #endif /* FEATURE_IS95B_SOFT_HO */
  #ifdef FEATURE_IS95B_EXT_DISP
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_EXT_DISP_BIT)
  #endif /* FEATURE_IS95B_EXT_DISP */
  #ifdef FEATURE_IS95B_ACCESS_HO
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_ACCESS_HO_BIT)
  #endif /* FEATURE_IS95B_ACCESS_HO */
  #ifdef FEATURE_IS95B_PILOT_RPT
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_PILOT_RPT_BIT)
  #endif /* FEATURE_IS95B_PILOT_RPT */
  #ifdef FEATURE_IS95B_NGHBR_SRCH_ENH
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_NGHBR_SRCH_ENH_BIT)
  #endif /* FEATURE_IS95B_NGHBR_SRCH_ENH */
  , 0
  #ifdef FEATURE_IS95B_RELEASE_ON_AC
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_RELEASE_ON_AC_BIT)
  #endif /* FEATURE_IS95B_RELEASE_ON_AC */
  #ifdef FEATURE_IS95B_PPSMM
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_PPSMM_BIT)
  #endif /* FEATURE_IS95B_PPSMM */
  #ifdef FEATURE_IS95B_NDSS
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_NDSS_BIT)
  #endif /* FEATURE_IS95B_NDSS */
  #ifdef FEATURE_IS95B_INC_CALL_FWD_ENH
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_INC_CALL_FWD_ENH_BIT)
  #endif /* FEATURE_IS95B_INC_CALL_FWD_ENH */
  #ifdef FEATURE_IS95B_ALERT_ANS_BYPASS
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_ALERT_ANS_BYPASS_BIT)
  #endif /* FEATURE_IS95B_ALERT_ANS_BYPASS */
  #ifdef FEATURE_IS95B_MAHHO
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_MAHHO_BIT)
  #endif /* FEATURE_IS95B_MAHHO */
  #ifdef FEATURE_IS95B_MDR
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_MDR_BIT)
  #endif /* FEATURE_IS95B_MDR */
  #ifdef FEATURE_IS95B_ACCESS_ENTRY_HO
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_ACCESS_ENTRY_HO_BIT)
  #endif /* FEATURE_IS95B_ACCESS_ENTRY_HO */
  , 0
  #ifdef FEATURE_IS95B_ACCESS_PROBE_HO
  | ADD_BIT_TO_FEATURE_MASK(F_IS95B_ACCESS_PROBE_HO_BIT)
  #endif /* FEATURE_IS95B_ACCESS_PROBE_HO */
  #ifdef FEATURE_MDR_DPT_MARKOV
#error code not present
  #endif /* FEATURE_MDR_DPT_MARKOV */
  #ifdef FEATURE_DS_SOCKETS_USE_LSPD
#error code not present
  #endif /* FEATURE_DS_SOCKETS_USE_LSPD */
  #ifdef FEATURE_DS_IS707A_CMUX
  | ADD_BIT_TO_FEATURE_MASK(F_DS_IS707A_CMUX_BIT)
  #endif /* FEATURE_DS_IS707A_CMUX */
  #ifdef FEATURE_PZID_CHANGE_EXAMPLE
  | ADD_BIT_TO_FEATURE_MASK(F_PZID_CHANGE_EXAMPLE_BIT)
  #endif /* FEATURE_PZID_CHANGE_EXAMPLE */
  #ifdef FEATURE_ANTIREGISTRATION_BIAS
  | ADD_BIT_TO_FEATURE_MASK(F_ANTIREGISTRATION_BIAS_BIT)
  #endif /* FEATURE_ANTIREGISTRATION_BIAS */
  #ifdef FEATURE_ENHANCED_STANDBY_II
  | ADD_BIT_TO_FEATURE_MASK(F_ENHANCED_STANDBY_II_BIT)
  #endif /* FEATURE_ENHANCED_STANDBY_II */
  #ifdef FEATURE_QUICK_SCAN
  | ADD_BIT_TO_FEATURE_MASK(F_QUICK_SCAN_BIT)
  #endif /* FEATURE_QUICK_SCAN */
  , 0
  #ifdef FEATURE_STANDBY_DEBUG_MESSAGES
  | ADD_BIT_TO_FEATURE_MASK(F_STANDBY_DEBUG_MESSAGES_BIT)
  #endif /* FEATURE_STANDBY_DEBUG_MESSAGES */
  #ifdef FEATURE_NO_VBB
  | ADD_BIT_TO_FEATURE_MASK(F_NO_VBB_BIT)
  #endif /* FEATURE_NO_VBB */
  #ifdef FEATURE_NO_TCXO_VOTE
#error code not present
  #endif /* FEATURE_NO_TCXO_VOTE */
  #ifdef FEATURE_EXT_LINEARIZER
#error code not present
  #endif /* FEATURE_EXT_LINEARIZER */
  #ifdef FEATURE_FINGER_POLL
#error code not present
  #endif /* FEATURE_FINGER_POLL */
  #ifdef FEATURE_FING_MERGE_DETECT
#error code not present
  #endif /* FEATURE_FING_MERGE_DETECT */
  #ifdef FEATURE_MINIMIZE_ISR_LOADING
  | ADD_BIT_TO_FEATURE_MASK(F_MINIMIZE_ISR_LOADING_BIT)
  #endif /* FEATURE_MINIMIZE_ISR_LOADING */
  #ifdef FEATURE_Q_NO_SELF_QPTR
  | ADD_BIT_TO_FEATURE_MASK(F_Q_NO_SELF_QPTR_BIT)
  #endif /* FEATURE_Q_NO_SELF_QPTR */
  , 0
  #ifdef FEATURE_Q_SINGLE_LINK
  | ADD_BIT_TO_FEATURE_MASK(F_Q_SINGLE_LINK_BIT)
  #endif /* FEATURE_Q_SINGLE_LINK */
  #ifdef FEATURE_FFPC
  | ADD_BIT_TO_FEATURE_MASK(F_FFPC_BIT)
  #endif /* FEATURE_FFPC */
  #ifdef FEATURE_RXC_ACTION_TIME_PROCESS
  | ADD_BIT_TO_FEATURE_MASK(F_RXC_ACTION_TIME_PROCESS_BIT)
  #endif /* FEATURE_RXC_ACTION_TIME_PROCESS */
  #ifdef FEATURE_DS_IS2000
  | ADD_BIT_TO_FEATURE_MASK(F_DS_IS2000_BIT)
  #endif /* FEATURE_DS_IS2000 */
  #ifdef FEATURE_DS_RLP3
  | ADD_BIT_TO_FEATURE_MASK(F_DS_RLP3_BIT)
  #endif /* FEATURE_DS_RLP3 */
  #ifdef FEATURE_IS2000_SCH
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_SCH_BIT)
  #endif /* FEATURE_IS2000_SCH */
  #ifdef FEATURE_IS2000_F_SCH
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_F_SCH_BIT)
  #endif /* FEATURE_IS2000_F_SCH */
  #ifdef FEATURE_RLP_LOGGING
  | ADD_BIT_TO_FEATURE_MASK(F_RLP_LOGGING_BIT)
  #endif /* FEATURE_RLP_LOGGING */
  , 0
  #ifdef FEATURE_SURF_FLASH2
#error code not present
  #endif /* FEATURE_SURF_FLASH2 */
  #ifdef FEATURE_EFS_FLASH2
#error code not present
  #endif /* FEATURE_EFS_FLASH2 */
  #ifdef FEATURE_NV_ITEM_MGR
  | ADD_BIT_TO_FEATURE_MASK(F_NV_ITEM_MGR_BIT)
  #endif /* FEATURE_NV_ITEM_MGR */
  #ifdef FEATURE_T53
  | ADD_BIT_TO_FEATURE_MASK(F_T53_BIT)
  #endif /* FEATURE_T53 */
  #ifdef FEATURE_JCDMA
  | ADD_BIT_TO_FEATURE_MASK(F_JCDMA_BIT)
  #endif /* FEATURE_JCDMA */
  #ifdef FEATURE_MONITOR
  | ADD_BIT_TO_FEATURE_MASK(F_MONITOR_BIT)
  #endif /* FEATURE_MONITOR */
  #ifdef FEATURE_ANALOG_LOGGING
  | ADD_BIT_TO_FEATURE_MASK(F_ANALOG_LOGGING_BIT)
  #endif /* FEATURE_ANALOG_LOGGING */
  #ifdef FEATURE_NEWCM
  | ADD_BIT_TO_FEATURE_MASK(F_NEWCM_BIT)
  #endif /* FEATURE_NEWCM */
  , 0
  #ifdef FEATURE_NEWUASMS
#error code not present
  #endif /* FEATURE_NEWUASMS */
  #ifdef FEATURE_DS_ENABLE_RM_DMNCY_IF_CTA_0
  | ADD_BIT_TO_FEATURE_MASK(F_DS_ENABLE_RM_DMNCY_IF_CTA_0_BIT)
  #endif /* FEATURE_DS_ENABLE_RM_DMNCY_IF_CTA_0 */
  #ifdef FEATURE_IS2000_LTU_CRCS
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_LTU_CRCS_BIT)
  #endif /* FEATURE_IS2000_LTU_CRCS */
  #ifdef FEATURE_QWORD_MISALIGNED_METHOD
  | ADD_BIT_TO_FEATURE_MASK(F_QWORD_MISALIGNED_METHOD_BIT)
  #endif /* FEATURE_QWORD_MISALIGNED_METHOD */
  #ifdef FEATURE_COMPOSE_MO_SMS
  | ADD_BIT_TO_FEATURE_MASK(F_COMPOSE_MO_SMS_BIT)
  #endif /* FEATURE_COMPOSE_MO_SMS */
  #ifdef FEATURE_NEW_DSM
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_DSM_BIT)
  #endif /* FEATURE_NEW_DSM */
  #ifdef FEATURE_16BIT_SHADOW_REG
  | ADD_BIT_TO_FEATURE_MASK(F_16BIT_SHADOW_REG_BIT)
  #endif /* FEATURE_16BIT_SHADOW_REG */
  #ifdef FEATURE_EVRC_RDA
  | ADD_BIT_TO_FEATURE_MASK(F_EVRC_RDA_BIT)
  #endif /* FEATURE_EVRC_RDA */
  , 0
  #ifdef FEATURE_COMPLETE_SNM
  | ADD_BIT_TO_FEATURE_MASK(F_COMPLETE_SNM_BIT)
  #endif /* FEATURE_COMPLETE_SNM */
  #ifdef FEATURE_SD20
  | ADD_BIT_TO_FEATURE_MASK(F_SD20_BIT)
  #endif /* FEATURE_SD20 */
  #ifdef FEATURE_IO_CARD
#error code not present
  #endif /* FEATURE_IO_CARD */
  #ifdef FEATURE_NATIVE_MODE
  | ADD_BIT_TO_FEATURE_MASK(F_NATIVE_MODE_BIT)
  #endif /* FEATURE_NATIVE_MODE */
  #ifdef FEATURE_CRF3100_PA
  | ADD_BIT_TO_FEATURE_MASK(F_CRF3100_PA_BIT)
  #endif /* FEATURE_CRF3100_PA */
  #ifdef FEATURE_RFR3100
  | ADD_BIT_TO_FEATURE_MASK(F_RFR3100_BIT)
  #endif /* FEATURE_RFR3100 */
  #ifdef FEATURE_PA_RANGE_TEMP_FREQ_COMP
  | ADD_BIT_TO_FEATURE_MASK(F_PA_RANGE_TEMP_FREQ_COMP_BIT)
  #endif /* FEATURE_PA_RANGE_TEMP_FREQ_COMP */
  #ifdef FEATURE_4PAGE_TX_LINEARIZER
  | ADD_BIT_TO_FEATURE_MASK(F_4PAGE_TX_LINEARIZER_BIT)
  #endif /* FEATURE_4PAGE_TX_LINEARIZER */
  , 0
  #ifdef FEATURE_IS2000_P2
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_P2_BIT)
  #endif /* FEATURE_IS2000_P2 */
  #ifdef FEATURE_IS2000_CHS
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_CHS_BIT)
  #endif /* FEATURE_IS2000_CHS */
  #ifdef FEATURE_TX_ADJ_WINDDOWN
  | ADD_BIT_TO_FEATURE_MASK(F_TX_ADJ_WINDDOWN_BIT)
  #endif /* FEATURE_TX_ADJ_WINDDOWN */
  #ifdef FEATURE_MAX_PWR_PROTECTION
  | ADD_BIT_TO_FEATURE_MASK(F_MAX_PWR_PROTECTION_BIT)
  #endif /* FEATURE_MAX_PWR_PROTECTION */
  #ifdef FEATURE_IS2000_QPCH_CCI
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_QPCH_CCI_BIT)
  #endif /* FEATURE_IS2000_QPCH_CCI */
  #ifdef FEATURE_TTY
  | ADD_BIT_TO_FEATURE_MASK(F_TTY_BIT)
  #endif /* FEATURE_TTY */
  #ifdef FEATURE_MCLK_DYNAMIC_SPEED_CTRL
  | ADD_BIT_TO_FEATURE_MASK(F_MCLK_DYNAMIC_SPEED_CTRL_BIT)
  #endif /* FEATURE_MCLK_DYNAMIC_SPEED_CTRL */
  #ifdef FEATURE_MCLK_43TCXO
#error code not present
  #endif /* FEATURE_MCLK_43TCXO */
  , 0
  #ifdef FEATURE_QDSP_TASK
  | ADD_BIT_TO_FEATURE_MASK(F_QDSP_TASK_BIT)
  #endif /* FEATURE_QDSP_TASK */
  #ifdef FEATURE_SBI_CLK_SOURCE
  | ADD_BIT_TO_FEATURE_MASK(F_SBI_CLK_SOURCE_BIT)
  #endif /* FEATURE_SBI_CLK_SOURCE */
  #ifdef FEATURE_BSPUI_API
  | ADD_BIT_TO_FEATURE_MASK(F_BSPUI_API_BIT)
  #endif /* FEATURE_BSPUI_API */
  #ifdef FEATURE_32K_XTAL
  | ADD_BIT_TO_FEATURE_MASK(F_32K_XTAL_BIT)
  #endif /* FEATURE_32K_XTAL */
  #ifdef FEATURE_GPIO_GROUP_INT
  | ADD_BIT_TO_FEATURE_MASK(F_GPIO_GROUP_INT_BIT)
  #endif /* FEATURE_GPIO_GROUP_INT */
  #ifdef FEATURE_SURF3100
  | ADD_BIT_TO_FEATURE_MASK(F_SURF3100_BIT)
  #endif /* FEATURE_SURF3100 */
  #ifdef FEATURE_SURF3300
  | ADD_BIT_TO_FEATURE_MASK(F_SURF3300_BIT)
  #endif /* FEATURE_SURF3300 */
  #ifdef FEATURE_FFA3300
#error code not present
  #endif /* FEATURE_FFA3300 */
  , 0
  #ifdef FEATURE_FFA
#error code not present
  #endif /* FEATURE_FFA */
  #ifdef FEATURE_HEADSET_GPIO5
  | ADD_BIT_TO_FEATURE_MASK(F_HEADSET_GPIO5_BIT)
  #endif /* FEATURE_HEADSET_GPIO5 */
  #ifdef FEATURE_SEC
  | ADD_BIT_TO_FEATURE_MASK(F_SEC_BIT)
  #endif /* FEATURE_SEC */
  #ifdef FEATURE_SEC_MEM_POOL
  | ADD_BIT_TO_FEATURE_MASK(F_SEC_MEM_POOL_BIT)
  #endif /* FEATURE_SEC_MEM_POOL */
  #ifdef FEATURE_SEC_CRYPT_TESTAPP
#error code not present
  #endif /* FEATURE_SEC_CRYPT_TESTAPP */
  #ifdef FEATURE_SEC_SSL
  | ADD_BIT_TO_FEATURE_MASK(F_SEC_SSL_BIT)
  #endif /* FEATURE_SEC_SSL */
  #ifdef FEATURE_SEC_SSL_SVR_TEST_CERT
#error code not present
  #endif /* FEATURE_SEC_SSL_SVR_TEST_CERT */
  #ifdef FEATURE_SEC_SSL_ERROR_CB_ONLY
  | ADD_BIT_TO_FEATURE_MASK(F_SEC_SSL_ERROR_CB_ONLY_BIT)
  #endif /* FEATURE_SEC_SSL_ERROR_CB_ONLY */
  , 0
  #ifdef FEATURE_SEC_SSL_KEYX_DEBUG
  | ADD_BIT_TO_FEATURE_MASK(F_SEC_SSL_KEYX_DEBUG_BIT)
  #endif /* FEATURE_SEC_SSL_KEYX_DEBUG */
  #ifdef FEATURE_SEC_SSL_ALLOW_NULL_CIPH
#error code not present
  #endif /* FEATURE_SEC_SSL_ALLOW_NULL_CIPH */
  #ifdef FEATURE_SEC_SSL_TESTAPP
#error code not present
  #endif /* FEATURE_SEC_SSL_TESTAPP */
  #ifdef FEATURE_MENU_REORG
  | ADD_BIT_TO_FEATURE_MASK(F_MENU_REORG_BIT)
  #endif /* FEATURE_MENU_REORG */
  #ifdef FEATURE_NEW_SOUND_API
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_SOUND_API_BIT)
  #endif /* FEATURE_NEW_SOUND_API */
  #ifdef FEATURE_AUDIO_AGC
  | ADD_BIT_TO_FEATURE_MASK(F_AUDIO_AGC_BIT)
  #endif /* FEATURE_AUDIO_AGC */
  #ifdef FEATURE_HEADSET
  | ADD_BIT_TO_FEATURE_MASK(F_HEADSET_BIT)
  #endif /* FEATURE_HEADSET */
  #ifdef FEATURE_ANALOG_HFK
  | ADD_BIT_TO_FEATURE_MASK(F_ANALOG_HFK_BIT)
  #endif /* FEATURE_ANALOG_HFK */
  , 0
  #ifdef FEATURE_STEREO_DAC
  | ADD_BIT_TO_FEATURE_MASK(F_STEREO_DAC_BIT)
  #endif /* FEATURE_STEREO_DAC */
  #ifdef FEATURE_I2C
  | ADD_BIT_TO_FEATURE_MASK(F_I2C_BIT)
  #endif /* FEATURE_I2C */
  #ifdef FEATURE_NEW_SBI
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_SBI_BIT)
  #endif /* FEATURE_NEW_SBI */
  #ifdef FEATURE_UP_CLOCK_SWITCHING
  | ADD_BIT_TO_FEATURE_MASK(F_UP_CLOCK_SWITCHING_BIT)
  #endif /* FEATURE_UP_CLOCK_SWITCHING */
  #ifdef FEATURE_RUNTIME_DEVMAP
  | ADD_BIT_TO_FEATURE_MASK(F_RUNTIME_DEVMAP_BIT)
  #endif /* FEATURE_RUNTIME_DEVMAP */
  #ifdef FEATURE_USB
  | ADD_BIT_TO_FEATURE_MASK(F_USB_BIT)
  #endif /* FEATURE_USB */
  #ifdef FEATURE_USB_CDC_ACM
  | ADD_BIT_TO_FEATURE_MASK(F_USB_CDC_ACM_BIT)
  #endif /* FEATURE_USB_CDC_ACM */
  #ifdef FEATURE_USB_HDR
#error code not present
  #endif /* FEATURE_USB_HDR */
  , 0
  #ifdef FEATURE_RDEVMAP_DS_DEFAULT_TO_U
  | ADD_BIT_TO_FEATURE_MASK(F_RDEVMAP_DS_DEFAULT_TO_U_BIT)
  #endif /* FEATURE_RDEVMAP_DS_DEFAULT_TO_U */
  #ifdef FEATURE_HW_FING_MERGE_DETECT
  | ADD_BIT_TO_FEATURE_MASK(F_HW_FING_MERGE_DETECT_BIT)
  #endif /* FEATURE_HW_FING_MERGE_DETECT */
  #ifdef FEATURE_QUARTER_ROLL_TIMELINE
#error code not present
  #endif /* FEATURE_QUARTER_ROLL_TIMELINE */
  #ifdef FEATURE_INT_125_FIQ
  | ADD_BIT_TO_FEATURE_MASK(F_INT_125_FIQ_BIT)
  #endif /* FEATURE_INT_125_FIQ */
  #ifdef FEATURE_VOC_TASK
  | ADD_BIT_TO_FEATURE_MASK(F_VOC_TASK_BIT)
  #endif /* FEATURE_VOC_TASK */
  #ifdef FEATURE_PM1000
#error code not present
  #endif /* FEATURE_PM1000 */
  #ifdef FEATURE_PM1000_LDO_ONLY
#error code not present
  #endif /* FEATURE_PM1000_LDO_ONLY */
  #ifdef FEATURE_PM1000_SCI
#error code not present
  #endif /* FEATURE_PM1000_SCI */
  , 0
  #ifdef FEATURE_PM1000_32K_XTAL
#error code not present
  #endif /* FEATURE_PM1000_32K_XTAL */
  #ifdef FEATURE_ENC_BTF_IN_NV
  | ADD_BIT_TO_FEATURE_MASK(F_ENC_BTF_IN_NV_BIT)
  #endif /* FEATURE_ENC_BTF_IN_NV */
  #ifdef FEATURE_GPSONE
#error code not present
  #endif /* FEATURE_GPSONE */
  #ifdef FEATURE_IS2000_CAGC
  | ADD_BIT_TO_FEATURE_MASK(F_IS2000_CAGC_BIT)
  #endif /* FEATURE_IS2000_CAGC */
  #ifdef FEATURE_PA_BYPASS_ENABLE
#error code not present
  #endif /* FEATURE_PA_BYPASS_ENABLE */
  #ifdef FEATURE_SUBPCG_PA_WARMUP_DELAY
  | ADD_BIT_TO_FEATURE_MASK(F_SUBPCG_PA_WARMUP_DELAY_BIT)
  #endif /* FEATURE_SUBPCG_PA_WARMUP_DELAY */
  #ifdef FEATURE_FSG_CONTROL
  | ADD_BIT_TO_FEATURE_MASK(F_FSG_CONTROL_BIT)
  #endif /* FEATURE_FSG_CONTROL */
  #ifdef FEATURE_QRF3300
  | ADD_BIT_TO_FEATURE_MASK(F_QRF3300_BIT)
  #endif /* FEATURE_QRF3300 */
  , 0
  #ifdef FEATURE_TRIMODE_ITEMS
  | ADD_BIT_TO_FEATURE_MASK(F_TRIMODE_ITEMS_BIT)
  #endif /* FEATURE_TRIMODE_ITEMS */
  #ifdef FEATURE_4MB_ROM
  | ADD_BIT_TO_FEATURE_MASK(F_4MB_ROM_BIT)
  #endif /* FEATURE_4MB_ROM */
  #ifdef FEATURE_EFS_2ND_FLASH_ONLY
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_2ND_FLASH_ONLY_BIT)
  #endif /* FEATURE_EFS_2ND_FLASH_ONLY */
  #ifdef FEATURE_SEARCH3
#error code not present
  #endif /* FEATURE_SEARCH3 */
  #ifdef FEATURE_PPM_DB_1
  | ADD_BIT_TO_FEATURE_MASK(F_PPM_DB_1_BIT)
  #endif /* FEATURE_PPM_DB_1 */
  #ifdef FEATURE_FULL_SNM
  | ADD_BIT_TO_FEATURE_MASK(F_FULL_SNM_BIT)
  #endif /* FEATURE_FULL_SNM */
  #ifdef FEATURE_GPS_SRCH_ENGINE
#error code not present
  #endif /* FEATURE_GPS_SRCH_ENGINE */
  #ifdef FEATURE_GPSONE_MATH_IMPROVEMENT
#error code not present
  #endif /* FEATURE_GPSONE_MATH_IMPROVEMENT */
  , 0
  #ifdef FEATURE_GPSONE_SA
#error code not present
  #endif /* FEATURE_GPSONE_SA */
  #ifdef FEATURE_TX_SPECTRAL_INVERSION
  | ADD_BIT_TO_FEATURE_MASK(F_TX_SPECTRAL_INVERSION_BIT)
  #endif /* FEATURE_TX_SPECTRAL_INVERSION */
  #ifdef FEATURE_AARDVARK
#error code not present
  #endif /* FEATURE_AARDVARK */
  #ifdef FEATURE_1MB_RAM
  | ADD_BIT_TO_FEATURE_MASK(F_1MB_RAM_BIT)
  #endif /* FEATURE_1MB_RAM */
  #ifdef FEATURE_NSOTASP
  | ADD_BIT_TO_FEATURE_MASK(F_NSOTASP_BIT)
  #endif /* FEATURE_NSOTASP */
  #ifdef FEATURE_DIAG_V7_PKT_IFACE
  | ADD_BIT_TO_FEATURE_MASK(F_DIAG_V7_PKT_IFACE_BIT)
  #endif /* FEATURE_DIAG_V7_PKT_IFACE */
  #ifdef FEATURE_SURF_FLASH
  | ADD_BIT_TO_FEATURE_MASK(F_SURF_FLASH_BIT)
  #endif /* FEATURE_SURF_FLASH */
  #ifdef FEATURE_EFS_ACCESS_METHODS
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_ACCESS_METHODS_BIT)
  #endif /* FEATURE_EFS_ACCESS_METHODS */
  , 0
  #ifdef FEATURE_EFS_FLASH
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_FLASH_BIT)
  #endif /* FEATURE_EFS_FLASH */
  #ifdef FEATURE_EFS_SFAT
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_SFAT_BIT)
  #endif /* FEATURE_EFS_SFAT */
  #ifdef FEATURE_AUTO_REMOVE_REMOTE_LINK
  | ADD_BIT_TO_FEATURE_MASK(F_AUTO_REMOVE_REMOTE_LINK_BIT)
  #endif /* FEATURE_AUTO_REMOVE_REMOTE_LINK */
  #ifdef FEATURE_EFS_MITSUBISHI
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_MITSUBISHI_BIT)
  #endif /* FEATURE_EFS_MITSUBISHI */
  #ifdef FEATURE_EFS_AMD
  | ADD_BIT_TO_FEATURE_MASK(F_EFS_AMD_BIT)
  #endif /* FEATURE_EFS_AMD */
  #ifdef FEATURE_DS_CHAP_NV
  | ADD_BIT_TO_FEATURE_MASK(F_DS_CHAP_NV_BIT)
  #endif /* FEATURE_DS_CHAP_NV */
  #ifdef FEATURE_UASMS_SAVE_MEM
#error code not present
  #endif /* FEATURE_UASMS_SAVE_MEM */
  #ifdef FEATURE_VR_HELPFUL_PROMPTS
  | ADD_BIT_TO_FEATURE_MASK(F_VR_HELPFUL_PROMPTS_BIT)
  #endif /* FEATURE_VR_HELPFUL_PROMPTS */
  , 0
  #ifdef FEATURE_VR_EMAIL_VM
  | ADD_BIT_TO_FEATURE_MASK(F_VR_EMAIL_VM_BIT)
  #endif /* FEATURE_VR_EMAIL_VM */
  #ifdef FEATURE_PM1000_RTC
#error code not present
  #endif /* FEATURE_PM1000_RTC */
  #ifdef FEATURE_PM1000_NO_COIN_BATT
#error code not present
  #endif /* FEATURE_PM1000_NO_COIN_BATT */
  #ifdef FEATURE_PM1000_MANAGED_LDO
#error code not present
  #endif /* FEATURE_PM1000_MANAGED_LDO */
  #ifdef FEATURE_PM1000_LOW_BATT_DETECTI
#error code not present
  #endif /* FEATURE_PM1000_LOW_BATT_DETECTI */
  #ifdef FEATURE_GPS_MODE
#error code not present
  #endif /* FEATURE_GPS_MODE */
  #ifdef FEATURE_CANNED_AA_DATA
#error code not present
  #endif /* FEATURE_CANNED_AA_DATA */
  #ifdef FEATURE_GPSONE_DBM
#error code not present
  #endif /* FEATURE_GPSONE_DBM */
  , 0
  #ifdef FEATURE_GPSONE_GPS_FTEST
#error code not present
  #endif /* FEATURE_GPSONE_GPS_FTEST */
  #ifdef FEATURE_BIG_DIAG_BUFFER_FOR_GPS
#error code not present
  #endif /* FEATURE_BIG_DIAG_BUFFER_FOR_GPS */
  #ifdef FEATURE_MSM3300_PPM_SRCH_ENGINE
#error code not present
  #endif /* FEATURE_MSM3300_PPM_SRCH_ENGINE */
  #ifdef FEATURE_FAST_QDSP
#error code not present
  #endif /* FEATURE_FAST_QDSP */
  #ifdef FEATURE_EXTENDED_PPM_LOG
  | ADD_BIT_TO_FEATURE_MASK(F_EXTENDED_PPM_LOG_BIT)
  #endif /* FEATURE_EXTENDED_PPM_LOG */
  #ifdef FEATURE_MIDI
  | ADD_BIT_TO_FEATURE_MASK(F_MIDI_BIT)
  #endif /* FEATURE_MIDI */
  #ifdef FEATURE_WEBAUDIO
  | ADD_BIT_TO_FEATURE_MASK(F_WEBAUDIO_BIT)
  #endif /* FEATURE_WEBAUDIO */
  #ifdef FEATURE_MP3
  | ADD_BIT_TO_FEATURE_MASK(F_MP3_BIT)
  #endif /* FEATURE_MP3 */
  , 0
  #ifdef FEATURE_MIDI_OUT
  | ADD_BIT_TO_FEATURE_MASK(F_MIDI_OUT_BIT)
  #endif /* FEATURE_MIDI_OUT */
  #ifdef FEATURE_MIDI_OUT_QCP
  | ADD_BIT_TO_FEATURE_MASK(F_MIDI_OUT_QCP_BIT)
  #endif /* FEATURE_MIDI_OUT_QCP */
  #ifdef FEATURE_NEW_SYNTH
  | ADD_BIT_TO_FEATURE_MASK(F_NEW_SYNTH_BIT)
  #endif /* FEATURE_NEW_SYNTH */
  #ifdef FEATURE_MULTIMEDIA
  | ADD_BIT_TO_FEATURE_MASK(F_MULTIMEDIA_BIT)
  #endif /* FEATURE_MULTIMEDIA */
  #ifdef FEATURE_QCP
  | ADD_BIT_TO_FEATURE_MASK(F_QCP_BIT)
  #endif /* FEATURE_QCP */
  #ifdef FEATURE_PNG_DECODER
  | ADD_BIT_TO_FEATURE_MASK(F_PNG_DECODER_BIT)
  #endif /* FEATURE_PNG_DECODER */
  #ifdef FEATURE_SAF
  | ADD_BIT_TO_FEATURE_MASK(F_SAF_BIT)
  #endif /* FEATURE_SAF */
  #ifdef FEATURE_ADEC
  | ADD_BIT_TO_FEATURE_MASK(F_ADEC_BIT)
  #endif /* FEATURE_ADEC */
  , 0
  #ifdef FEATURE_QSYNTH
  | ADD_BIT_TO_FEATURE_MASK(F_QSYNTH_BIT)
  #endif /* FEATURE_QSYNTH */
  #ifdef FEATURE_QTUNES
  | ADD_BIT_TO_FEATURE_MASK(F_QTUNES_BIT)
  #endif /* FEATURE_QTUNES */
  #ifdef FEATURE_VOICE_PLAYBACK
  | ADD_BIT_TO_FEATURE_MASK(F_VOICE_PLAYBACK_BIT)
  #endif /* FEATURE_VOICE_PLAYBACK */
  #ifdef FEATURE_AUDIO_FORMAT
  | ADD_BIT_TO_FEATURE_MASK(F_AUDIO_FORMAT_BIT)
  #endif /* FEATURE_AUDIO_FORMAT */
  #ifdef FEATURE_CMX
  | ADD_BIT_TO_FEATURE_MASK(F_CMX_BIT)
  #endif /* FEATURE_CMX */
  #ifdef FEATURE_VS_TASK
  | ADD_BIT_TO_FEATURE_MASK(F_VS_TASK_BIT)
  #endif /* FEATURE_VS_TASK */
  #ifdef FEATURE_BT
  | ADD_BIT_TO_FEATURE_MASK(F_BT_BIT)
  #endif /* FEATURE_BT */
  #ifdef FEATURE_BT_NA
  | ADD_BIT_TO_FEATURE_MASK(F_BT_NA_BIT)
  #endif /* FEATURE_BT_NA */
  , 0
  #ifdef FEATURE_BT_AG
  | ADD_BIT_TO_FEATURE_MASK(F_BT_AG_BIT)
  #endif /* FEATURE_BT_AG */
  #ifdef FEATURE_BT_MSG_DEBUG
  | ADD_BIT_TO_FEATURE_MASK(F_BT_MSG_DEBUG_BIT)
  #endif /* FEATURE_BT_MSG_DEBUG */
  #ifdef FEATURE_BT_HS
#error code not present
  #endif /* FEATURE_BT_HS */
  #ifdef FEATURE_BT_ICON
#error code not present
  #endif /* FEATURE_BT_ICON */
  #ifdef FEATURE_BT_MY_BD_ADDR
#error code not present
  #endif /* FEATURE_BT_MY_BD_ADDR */
  #ifdef FEATURE_BT_TEST_SDP
#error code not present
  #endif /* FEATURE_BT_TEST_SDP */
  #ifdef FEATURE_BT_TEST_RC_2_SIO
#error code not present
  #endif /* FEATURE_BT_TEST_RC_2_SIO */
  #ifdef FEATURE_BT_TEST_API
#error code not present
  #endif /* FEATURE_BT_TEST_API */
  , 0
  #ifdef FEATURE_BT_TEST_MODE_TESTER
  | ADD_BIT_TO_FEATURE_MASK(F_BT_TEST_MODE_TESTER_BIT)
  #endif /* FEATURE_BT_TEST_MODE_TESTER */
  #ifdef FEATURE_BT_DEBUG
#error code not present
  #endif /* FEATURE_BT_DEBUG */
  #ifdef FEATURE_BT_DEVICE_DISCOVERY
  | ADD_BIT_TO_FEATURE_MASK(F_BT_DEVICE_DISCOVERY_BIT)
  #endif /* FEATURE_BT_DEVICE_DISCOVERY */
  #ifdef FEATURE_MMC
  | ADD_BIT_TO_FEATURE_MASK(F_MMC_BIT)
  #endif /* FEATURE_MMC */
  #ifdef FEATURE_ENHANCED_VR
#error code not present
  #endif /* FEATURE_ENHANCED_VR */
  #ifdef FEATURE_PHONE_VR
  | ADD_BIT_TO_FEATURE_MASK(F_PHONE_VR_BIT)
  #endif /* FEATURE_PHONE_VR */
  #ifdef FEATURE_PHONE_VR_HFK
  | ADD_BIT_TO_FEATURE_MASK(F_PHONE_VR_HFK_BIT)
  #endif /* FEATURE_PHONE_VR_HFK */
  #ifdef FEATURE_PHONE_VR_NO_DUP
  | ADD_BIT_TO_FEATURE_MASK(F_PHONE_VR_NO_DUP_BIT)
  #endif /* FEATURE_PHONE_VR_NO_DUP */
  , 0
  #ifdef FEATURE_VOICE_MEMO
  | ADD_BIT_TO_FEATURE_MASK(F_VOICE_MEMO_BIT)
  #endif /* FEATURE_VOICE_MEMO */
  #ifdef FEATURE_DFM_ANSWER_MACHINE
#error code not present
  #endif /* FEATURE_DFM_ANSWER_MACHINE */
  #ifdef FEATURE_VM_MEM_TO_QCP
#error code not present
  #endif /* FEATURE_VM_MEM_TO_QCP */
  #ifdef FEATURE_VOICE_DATABASE
  | ADD_BIT_TO_FEATURE_MASK(F_VOICE_DATABASE_BIT)
  #endif /* FEATURE_VOICE_DATABASE */
  #ifdef FEATURE_VOICE_RECORD
  | ADD_BIT_TO_FEATURE_MASK(F_VOICE_RECORD_BIT)
  #endif /* FEATURE_VOICE_RECORD */
  #ifdef FEATURE_NO_REMOTE_FILE
#error code not present
  #endif /* FEATURE_NO_REMOTE_FILE */
  #ifdef FEATURE_SKIP_INTEGRITY_CHECK
  | ADD_BIT_TO_FEATURE_MASK(F_SKIP_INTEGRITY_CHECK_BIT)
  #endif /* FEATURE_SKIP_INTEGRITY_CHECK */
  #ifdef FEATURE_MSM5105_PPM_SRCH_ENGINE
  | ADD_BIT_TO_FEATURE_MASK(F_MSM5105_PPM_SRCH_ENGINE_BIT)
  #endif /* FEATURE_MSM5105_PPM_SRCH_ENGINE */
  , 0
  #ifdef FEATURE_PPM_DB_2
  | ADD_BIT_TO_FEATURE_MASK(F_PPM_DB_2_BIT)
  #endif /* FEATURE_PPM_DB_2 */
  #ifdef FEATURE_SRCH_SCHEDULER
#error code not present
  #endif /* FEATURE_SRCH_SCHEDULER */
  #ifdef FEATURE_SRCH_SLEW_IN_DRV
  | ADD_BIT_TO_FEATURE_MASK(F_SRCH_SLEW_IN_DRV_BIT)
  #endif /* FEATURE_SRCH_SLEW_IN_DRV */
  #ifdef FEATURE_SRCH_4_SHOULDERS
  | ADD_BIT_TO_FEATURE_MASK(F_SRCH_4_SHOULDERS_BIT)
  #endif /* FEATURE_SRCH_4_SHOULDERS */
  #ifdef FEATURE_BITMAP
  | ADD_BIT_TO_FEATURE_MASK(F_BITMAP_BIT)
  #endif /* FEATURE_BITMAP */
  #ifdef FEATURE_DS_MOBILE_IP
  | ADD_BIT_TO_FEATURE_MASK(F_DS_MOBILE_IP_BIT)
  #endif /* FEATURE_DS_MOBILE_IP */
}; /* end diag_feature_mask */
/*lint -restore */
