<?xml version="1.0" encoding="utf-16"?>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" encoding="us-ascii"/>
  <xsl:template match="/CALIBRATION_DATABASE">
<![CDATA[
/* linesize(132)
** pagesize(60)
** title("Dual Mode Subscriber Station")
** subtitle("Audio Calibration Database")
*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

           V O C O D E R   C A L I B R A T I O N   D A T A B A S E
              D A T A   S T O R A G E  A N D   R E T R I V A L

DESCRIPTION
  The actual vocoder calibration values and the functions to gain access
  to the data.  This is version is based on constant ROM data.

EXTERNALIZED FUNCTIONS
  voc_cal_get_pcm_cal
    Get a pointer to pcm calibration structure.
  voc_cal_get_codec_config
    Get a pointer the codec configuration data.
  voc_cal_get_dfm_config
    Get a pointer to DFM configuration.
  voc_cal_get_dfm_dev_limit
    Get the DFM deviation limit.
  voc_cal_get_mic_gain_adjust
    Get the mic gain adjustment value for the specified codec.
  voc_cal_set_mic_gain_adjust
    Set the mic gain adjustment value for the specified codec.
  voc_cal_read_nv_cal
    Reads all NV items related to voc calibration.

INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright(c) 1999 - 2007 by QUALCOMM, Incorporated. All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* <EJECT> */

/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //source/qcom/qct/multimedia/audio/6k/ver1/avs/main/latest/src/voccal.c#16 $ $DateTime: 2008/11/20 11:43:50 $ $Author: kmodak $

when       who     what, where, why
--------   ---     ---------------------------------------------
11/18/08   knm     Added Macro for HS-USB along with USB car kit
11/17/08   rm      Fix provided for  CR 163916 - dualmic: muted uplink and downlink  and
                   updation of calibration sections.
11/11/08   rm      SURF 6800 calibration values updated from depot code.
11/03/08   dp      Correcting featurization issue for FM over BT
10/22/08   dp      FM over BT AG changes
10/14/08   sk      Modifed the code to update the HS mode value to 
                   0x14FF for WB spekerphone.CR 154396.
30/08/08   vsud    Check in of RVE changes on behalf of vocoder team.
28/08/08   rm	   Added support for RVE
08/07/08   av      Added support for CrystalSpeech using EXTERNAL_SADC
04/11/08   sj      Lowered the codec Tx gain for voc_pcm_tty_on_chip_1_cal 
                   and voc_pcm_tty_hco from 0x4000 to 0x800 for 6270/6240. 
                   This will prevent Tx baudot to be saturated. fixed CR 151381.
05/08/08   pl      CR 143215 - Updated qsynth adrc paramter table for all supported 
                   sample rates. 
04/10/08   sp      Added all pass conefficients for 5 stage IIR filters that did 
                   not have any coefficients. Fixed no audio issue for AMR WB
                   call on speakerphone and BT headset.
03/17/08  ymc/anb  Modified codec gain ctrl api to control gain changes.
                   Fix for SC2X codec pop issue through MSMAUD_PCM_DC_OFFSET feature.
02/07/08   vs      Added cal data for LCU (SURF and FFA)
12/06/07   anb     Fixes CR 129526-Updated the cal values for Handset on SC2X
10/19/07   anb     Updated the cal values for Headset on SC2X.
10/03/07   anb     Modified Rx PCM filter for Speaker Phone on SC2X
08/27/07   ymc     Added Crystal Speech support.
08/27/07  sg/wfd   Define unique OFF_BOARD AuxPCM Coded settings for 6800A-
                   like targets.  Cleanup obsolete code for older targets.
                   Specifically, #else code for MSMAUD_MSM6050_CODEC_CONFIG.
08/23/07   ymc     Added wideband EC parameters.
           ymc     Updated 5 stages IIR filter parameters for handset and 
                   headset.
08/07/07    sk     Updated M6800 65nm IIR filter parameters. 
07/27/07   ymc     Updated 5 stages IIR filter parameters 
                   for handset and headset.
06/21/07   anb     Updated the QSC60x5 calibration values from system's team.
06/15/07   anb     Updated QSC60X5 codectxgain to support Q factor change in firmware
05/22/07   anb     Updated QSC60x5 Audio Calibration
05/14/07   sud     EPIC Vreg_NCP support in ground referenced capless mode
                   for QSC60x5 chipsets.
05/10/07    sp     Added support for AUX PCM primary PCM mode.
                   Added support for external SOC based BT solution that needs
                   primary pcm mode.
04/25/07   anb     Fixed a compilation issue when FEATURE_MM_REC is defined
04/20/07  sud/anb  Added QSC60X5 FFA audio calibration.
04/20/07  sp/anb   Added AUX PCM definitions for the SC2X hardware.
02/27/07   sud     Added 6800 65nm audio calibration.
02/27/07   ymc     Removed 6260 dependencies on new EC calibrations.
           ymc     Updated Copyright.
02/26/07   kan     Added AMR-WB changes 
02/23/07   suk     Updated 6260 Audio Calibration. CR#110642
01/23/07   ymc     Correct new EC parameters naming.
           ymc     Updated Copyright.
01/23/07    kk     Fixed the issues related to adding 44k sample rate.
12/04/06   ymc     Added VOC_EC_BT_HEADSET support.
           ymc     Used VOC_EC_BT_HEADSET for HFK device.
11/23/06   suk     Removed the definition QDSP_INTERNAL_PCM_FORMAT_1 for 6260.
11/21/06   suk     Updated 6260 FFA audio calibration and added comments.
11/16/06   suk     Added 6260 FFA audio calibration.
11/10/06    az     Fixed the CR: 105868 In-Call MP3: Noise heard on 6260 FFA during 
                   In-Call MP3 while in MONO Mode 
10/05/06   suk     Added 6260 FFA audio calibration values for new EC (headset
                   only).
                   Fixed DENS_gamma_e_high placement in the handset, headset,
                   handsfree, and speaker structures.
09/11/06    ay     Fixed 6280 and QSC60X0 to use the same PCM filter
                   coefficients.
09/08/06    pl     Added support for 44K clock.
08/31/06    ay     Added 6280 FFA audio calibration.
08/29/06    hz     Added support for incall MP3 on 65nm platforms.
07/26/06  nm/ymc   Added FEATURE_AVS_NEXTGEN_EC.
          nm/ymc   Corrected speaker EC calibrations for new EC when
                   FEATURE_AVS_NEXTGEN_EC is defined .
07/20/06   anb     Added support for FEATURE_AVS_AUDIO_DECODER_SCO
07/18/06   act     Updated QSC60x0 audio calibration.
07/10/06   act     Added hssd parameter to codec calibration data.
                   Also added missing codecs to voc_cal_mic_gain_adjust[]
                   and voc_cal_codec_vr_types[].
04/11/06   act     Added QSC60x0 FFA audio calibration.
03/24/06    pl     Seperated FIR filter from FEATURE_QSYNTH_ADRC and
                   FEATURE_QTUNES_AdRC.
03/15/06   ymc     Added FEATURE_INTERNAL_SADC support.
03/11/06   ymc/ay  Fixed mic muted when recording with speaker enabled.
03/10/06   sm/sp   Fixed a featurization issue with SDAC
02/14/06   ymc     Added 6280 FFA audio calibration.
                   Updated QTunes PCM filter control table.
                   Fixed BT_AG featurization in MM_REC adie config table.
                   Updated Copyright.
01/30/06    sp     Added support for I2S SBC interface.
12/02/05   act     Re-featurizing stereo-related codecs and sound devices.
10/08/05    sp     Added the feature MSMAUD_6500_FFA_AUDIO_CAL.
09/18/05    sp     Added support for DSP based SBC encoder.
09/18/05    st     Added output_3d_mode entries to voc_pcm_path_cal_type
                   structures.
09/02/05    sm     Modified stereo USB cal to use mono spkr+mic for voice
08/31/05    sm     Use voc_data_get_codec_mode()
08/10/05    sm     Featurized stereo USB support.
                   Adjusted speakerphone gains for better EC performance.
07/28/05    sm     Fixed missed entry on stereo USB support.
07/26/05    sm     Added stereo usb support
07/05/05    aw     Modified qsynth pcm filter for backward compatiblity.
05/27/05    sp     Added support for BT A2DP profile and ARM based SBC codec.
05/25/05    sm     Added GSM TTY calibration tables.
05/24/05    hz     Added support for MultiMedia/AAC record functionality.
05/04/05    aw     Replace PCM filter with IIR filter support for Qsynth.
04/22/05    aw     Clean up for audio side chain filter.
04/21/05   act     Changed name of voc_codec_type to voc_codec_class_type.
                   Reverted name of voc_codec_id_type to voc_codec_type.
04/01/05   act     Added tables and access functions to associate a specific
                   codec with a generic codec type.
04/01/05    hz     Added support for Enhanced AAC Plus decoder.
03/02/05    aw     Added support for side chain tuning filters.
02/15/05   act     Added EC parameter calibration structures.
02/15/05    sm     Added FEATURE_IIR_FILTER
02/14/05    hz     Added support for IMAGE_WM.
02/10/05    aw     Added support for T_FFA, since FEATURE_FFA will no longer be
                   used on newer targets.
01/20/05    sg     Modified to support MIDI on BT_AG codec.
01/07/05  sm/act   Added support for FEATURE_VOC_MIC_GAIN_ADJUST and
                   FEATURE_VOC_NV_CAL
12/03/04    sm     Removed FEATURE_USB_ISOC_AUDIO
12/01/04    aw     Added support for MP4D_AAC_NO_VPP image.
11/19/04    sg     Added support for QTV and QTV_AAC images.
10/15/04    hz     Added support for QDSP_IMAGE_MP4D_AAC_PLUS.
09/22/04    aw     Added support for in call viewfinder.
08/19/04    sm     Added FEATURE_AUDIO_CAL_MED_HIGH_FFA.
06/01/04    aw     Added support for H264 image.
05/11/04    vp     Merged ADRC and PCM filter support MP3/AAC from
                   MSMSHARED_AVS.00.09.05.02.00. Added support for H263 images.
04/01/04    sm     Audio gains for 6250 under FEATURE_AUDIO_CAL_MED_HIGH.
12/03/03    aw     Added audio support for QGL image.
11/24/03    aw     Modified code to support qsynth ADRC and PCM filter at
                   different sampling rate. Fix featurization on stereo headset.
11/22/03    sg     Added support for RealAudio codec.
10/30/03    sm     Added multimode calibration support.
10/10/03    sg     Added support for MP4D_MP3 image.
09/23/03    sm     Increased all audio gains for 6300 under
                   FEATURE_AUDIO_CAL_HIGH
08/21/03    aw     Added adie codec config for BT intercom device, CR#29347.
            st     Added definitions for BT intercom device.
07/24/03    sg     Added support for stereo headset device.
05/13/03   ymc     Corrected PCM format definitions for UMTS FFA.
04/18/03    aw     Added audio support for Q3D image.
04/17/03    st     Added support for DFM_SAT_DC_OFFSET.
03/13/03    st     Added support for MP4D+AAC image.
03/12/03    st     Modified BT AG codec config to use off board setting.
01/25/03    st     Disabled echo canceller for all TTY devices as recommended.
01/05/03    sg     Modified voc_cal_get_codec_config() to check for invalid
                   image type.
12/03/02    st     Modified code to use vocoder codec config settings as
                   default.
11/06/02    sm     Include msmaud.h.
10/30/02    aw     Fixed featurization.
10/29/02  st/sg    Added calibration values for speaker phone. Reorganized
                   ADIE config data so that it is no longer part of
                   voc_pcm_path_cal_type. ADIE config can be obtained by clients
                   using voc_cal_get_adie_config().
10/17/02   ymc     Redo audio calibration for UMTS FFA and SURF.
09/18/02    sm     Added in MSMAUD_ALT_BT_AG_CONFIG and MSMAUD_PCM_FORMAT_DAI.
                   Look for QDSP_IMAGE_BT_DEFINED when referring to f/w image.
09/16/02    st     Removed reference to QDSP_IMAGE_GPS; modified featurization
                   for QDSP_CODEC_CTRL_WB_AMP_1 and QDSP_CODEC_CTRL_WB_AMP_2.
09/06/02    sg     Moved ADIE config to msmaud.h; fixed BT headset config
                   values.
08/22/02    sg     Modified code to support FEATURE_EXTERNAL_SDAC and
                   FEATURE_INTERNAL_SDAC; added support for
                   QDSP_IMAGE_VOC_DEFINED; removed reference to QDSP_IMAGE_BT.
08/19/02    st     Changed VOC_DFM_SAT_AGC_NOM to 0xe6 for FFA and SURF.
08/13/02   sg/st   Added support for MP4 and AAC.
07/09/02    sm     Synced to perforce tip.
            sm     Replaced MSMHW_5200 by T_MSM5200.
           ymc     Replaced T_MSM5200 by MSMHW_MSM5200.  Removed T_KOVU.
06/13/02    st     Updated ADRC values for 32kHz synth.
06/11/02    st     Modified code to support FEATURE_HWTC.
03/21/02    st     Updated cal values; updated ESEC and NS settings for TTY
                   devices.
03/12/02    st     Modified code to add MSM6050 support; corrected the codec
                   configuration values for MSM6050; updated ADIE codec config
                   sequences to remove pops; added codecRxGain values in
                   cal tables.
03/04/02   jkl     Added FEATURE_VR_PUFE.
01/15/02   ymc     Added GSM and WCDMA support.  Added FEATURE_UMTS_FFA.
           ymc     Updated copyright.
12/11/01    aw     Added MSMAUD_ADIE_CODEC_CONFIG. Updated codec config command.
            aw     Added defines for MSM6050 codec config command.
            ro     Use msmaud.h to eliminate targetization.
12/05/01    sg     Mic gain changed to P6 and CODEC sidetone gain set to 0 for
                   VCO mode. PCM slope filter disabled for HCO mode.
10/04/01    sg     Added VCO and HCO modes for TTY.
10/01/01    sm     Added FEATURE_BT_AG_LOCAL_AUDIO.
09/11/01    st     Updated default values for ADRC and PCM filter settings for
                   QSynth image.
09/04/01    aw     Added FEATURE_QSYNTH_ADRC. Added defines for QSynth PCM
                   filter and ADRC data structure in each PCM paths.
08/28/01    st     Modified value of VOC_DFM_AUDIO_DEF in order to mute Tx
                   and disable SAT transponding.
07/31/01  sm/ro    Change TX volume for AUX PCM HFK to pass DFM tests.
                   Changed voc_cal_codec_tty_off_board for external PCM.
06/18/01  jkl/ym   Added FEATURE_ACP.
05/21/01   jkl     Removed Enhanced VR feature.
05/02/01    sm     Removed unnecessary TTY codec.
04/26/01    sm     Added FEATURE_USB_ISOC_AUDIO support.
04/11/01    sm     Calibrated 5105 handset AAGC.
03/08/01    sm     Corrected another TTY featurization error.
03/04/01    sm     Added codec config for QSynth and QTunes for off board
                   codec (digital HFK); removed NULL entries in codec config
                   table.
02/28/01    st     Removed support for 16K codec types; added proper
                   featurization to voc_cal_codec_cfg; changed
                   FEATURE_AUDIO_FORMAT to use FEATURE_QSYNTH || FEATURE_QTUNES;
                   modified codec configuration to enable wideband compensation
                   filter for QTunes and QSynth internal codec configurations.
02/22/01    sm     Renamed FEATURE_GPSONE to FEATURE_GPS_MODE.
02/21/01    vl     Added MSM5100 support.
12/10/00    st     Fixed #elif statement; modified TX DTMF gain to 0x1000.
12/05/00   jkl     Added FEATURE_ENHANCED_VR.
12/04/00  st/sm    Added QTUNES support, updated calibration tables.
10/18/00    sm     voc_cal_get_codec_config() updated for QDSP_IMAGE_VRA.
10/13/00   ymc     Added MSM5105 support; T_MSM33 as T_MSM33 & !T_MSM5105;
                   !T_MSM33 as !T_MSM33 || T_MSM5105.
09/21/00    sm     Added voc_cal_get_codec_config().
09/18/00    sm     Added analog QSynth codec path, 22khz sdac flag.
09/08/00    sm     Added Bluetooth/PPG support.
08/15/00   spf     Removed QDSP_PCM_MODE_16K_V setting from the
                   QDSP_INT_16K_PCM_FORMAT definition for PPG target.
08/14/00   spf     Updated codec configuration command defintions for PPG.
08/03/00    st     Replaced "#if define" with "#if defined".
08/03/00    sm     Added SDAC calibration for PPG.
07/14/00   spf     Added support for TTY headset and HFK devices.
                   Removed voc_cal_get_tty_cal().
06/16/00    sm     Updated calibration for avcRlinkSensitivityOffset.
05/30/00    st     Added defines for codec configuration commands for new PCM
                   paths.
05/26/00   spf     Updated FFA and TTP Tx calibration to match 5GP.
05/16/00    st     Modified codec configuration command for stereo DAC.
05/12/00   spf     Add TTY support: voc_tty_cal and voc_cal_get_tty_cal().
05/02/00    ro     Recal SAT AGC level for FFA.
           spf     Set VOC_DFM_SAT_THRESH to 0x0320.
03/28/00    sm     AAGC mainline.
03/22/00   spf     TTP phone targets use same Tx Volume as FFA for internal
                   codec channel 0.
03/08/00   spf     Added DFM configuration support.
02/35/00    ro     Increased AUX PCM TX gain by 2.5 dB.
01/25/00    ro     Use voc_ec_type and voc_ns_type.
01/21/00   spf     Updated off-board, off-chip PCM calibration to use
                   AEC instead of ESEC echo cancellation.
12/17/99   jkl     Adjusted TX gains for AUX channel (Analog HFK).
12/01/99   spf     Merged with 1.12.1.0: Calibrated audio AGC.
11/29/99   jkl     Modified Echo Canceller mode for headset and Analog HFK.
11/22/99   jkl     Added new AGC /AVC parameters values.
11/16/99   jkl     Set AUX_CLK_VAL to be level HIGH.
11/11/99   jkl     Lowered the DTMF TX gain.
11/04/99   jkl     Included FFA phone specific calibration data.
10/28/99   jkl     Updated calibration values.
10/18/99    st     Removed initialization for agc parameters.
10/14/99   jkl     Disabled Codec reset strobe from calibration table.
10/04/99   jkl     Included CAL_MEMORY for calibration tests.
09/22/99   spf     Adjusted codec side tone gains to 0x800 for internal codec.
                   Modified codec interface definitions to use
                   QDSP_DETECT_ZEROES_V instead of QDSP_DETECT_ONES_V.
09/10/99   spf     Removed T_MSM31_TCX0_DIV2.
09/09/99   jkl     Included CODEC TX and ST gains
08/26/99   spf     Pink Panther Rev2 support.
08/02/99   spf     Zeroed the tx_filter and rx_filter fields of
                   voc_pcm_on_board_cal.
06/15/99    ro     First version.

===========================================================================*/

/* <EJECT> */

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"            /* Definitions for byte, word, etc.        */
#include "msmaud.h"            /* MSMAudio features                       */
#include "clkregim.h"          /* Clock regime                            */
#include "voccal.h"            /* Interface definition for voc cal data   */
#include "vocdata.h"

#ifdef FEATURE_VOC_NV_CAL
#include "nv.h"                /* NV read operations                      */
#include "voci.h"              /* For VOC_NV_SIG                          */
#endif /* FEATURE_VOC_NV_CAL */

/* <EJECT> */

/* ===========================================================================
**
**                M A I N  C O N F I G U R A T I O N   A N D
**                     C A L I B R A T I O N   D A T A
**
** =========================================================================*/

/* Configuration features
*/

/* off-chip on-board codec - uLaw or linear (default) */
#undef VOC_USE_ULAW


#ifdef FEATURE_VOC_MIC_GAIN_ADJUST
/* Cached mic gain adjustment values (default=0) */
sint15 voc_cal_mic_gain_adjust[VOC_CODEC_MAX] =
{
  /*  VOC_CODEC_ON_CHIP_0         */ 0
#ifdef FEATURE_AVS_CRYSTAL_SPEECH
  /* VOC_CODEC_ON_CHIP_0_DUAL_MIC */,0
#endif
  /*  VOC_CODEC_ON_CHIP_1         */,0
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
  /*  VOC_CODEC_STEREO_HEADSET    */,0
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
  /*  VOC_CODEC_ON_CHIP_AUX       */,0
  /*  VOC_CODEC_ON_BOARD          */,0
#ifdef FEATURE_SPEAKER_PHONE
  /*  VOC_CODEC_SPEAKER           */,0
#endif /* FEATURE_SPEAKER_PHONE */
#ifdef FEATURE_BT
  /*  VOC_CODEC_BT_INTERCOM       */,0
#ifdef FEATURE_BT_AG
  /*  VOC_CODEC_BT_AG             */,0
#ifdef FEATURE_BT_AG_LOCAL_AUDIO
  /*  VOC_CODEC_BT_AG_LOCAL_AUDIO */,0
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */
#endif /* FEATURE_BT_AG */
#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
  /* VOC_CODEC_BT_A2DP            */,0
  /* VOC_CODEC_BT_A2DP_SCO        */,0
#endif /* FEATURE_SBC_CODEC */
#endif /* FEATURE_BT */
  /*  VOC_CODEC_OFF_BOARD         */,0
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
  /*  VOC_CODEC_SDAC              */,0
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
#if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
 /* VOC_CODEC_IN_MONO_SADC_OUT_MONO_HANDSET    */
                                    ,0
 /* VOC_CODEC_IN_MONO_SADC_OUT_STEREO_HEADSET  */
                                    ,0
 /* VOC_CODEC_IN_STEREO_SADC_OUT_MONO_HANDSET  */
                                    ,0
 /* VOC_CODEC_IN_STEREO_SADC_OUT_STEREO_HEADSET*/
                                    ,0
#endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */
#ifdef FEATURE_TTY
  /*  VOC_CODEC_TTY_ON_CHIP_1     */,0
  /*  VOC_CODEC_TTY_OFF_BOARD     */,0
  /*  VOC_CODEC_TTY_VCO           */,0
  /*  VOC_CODEC_TTY_HCO           */,0
#endif /* FEATURE_TTY */
#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
  /*  VOC_CODEC_USB               */,0
#ifdef FEATURE_INTERNAL_SDAC
  /*  VOC_CODEC_STEREO_USB        */,0
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
/* FM over BT AG */
#ifdef FEATURE_BT_AG
                                    ,0
#endif                                    

};
#endif /* FEATURE_VOC_MIC_GAIN_ADJUST */


/* Codec types */
voc_codec_class_type voc_cal_codec_class[VOC_CODEC_MAX] =
{
  /*  VOC_CODEC_ON_CHIP_0         */ VOC_CODEC_CLASS_INTERNAL
#ifdef FEATURE_AVS_CRYSTAL_SPEECH
  /* VOC_CODEC_ON_CHIP_0_DUAL_MIC */,VOC_CODEC_CLASS_INTERNAL
#endif
  /*  VOC_CODEC_ON_CHIP_1         */,VOC_CODEC_CLASS_INTERNAL
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
#ifdef FEATURE_INTERNAL_SDAC
  /*  VOC_CODEC_STEREO_HEADSET    */,VOC_CODEC_CLASS_INTERNAL_STEREO
#else
  /*  VOC_CODEC_STEREO_HEADSET    */,VOC_CODEC_CLASS_INTERNAL
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
  /*  VOC_CODEC_ON_CHIP_AUX       */,VOC_CODEC_CLASS_INTERNAL
  /*  VOC_CODEC_ON_BOARD          */,VOC_CODEC_CLASS_EXTERNAL
#ifdef FEATURE_SPEAKER_PHONE
  /*  VOC_CODEC_SPEAKER           */,VOC_CODEC_CLASS_INTERNAL
#endif /* FEATURE_SPEAKER_PHONE */
#ifdef FEATURE_BT
  /*  VOC_CODEC_BT_INTERCOM       */,VOC_CODEC_CLASS_INTERNAL
#ifdef FEATURE_BT_AG
  /*  VOC_CODEC_BT_AG             */,VOC_CODEC_CLASS_BLUETOOTH
#ifdef FEATURE_BT_AG_LOCAL_AUDIO
  /*  VOC_CODEC_BT_AG_LOCAL_AUDIO */,VOC_CODEC_CLASS_BLUETOOTH_LOCAL
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */
#endif /* FEATURE_BT_AG */
#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
  /* VOC_CODEC_BT_A2DP            */,VOC_CODEC_CLASS_BLUETOOTH_A2DP
  /* VOC_CODEC_BT_A2DP_SCO        */,VOC_CODEC_CLASS_BLUETOOTH_A2DP_SCO
#endif /* FEATURE_SBC_CODEC */
#endif /* FEATURE_BT */
  /*  VOC_CODEC_OFF_BOARD         */,VOC_CODEC_CLASS_EXTERNAL
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
#ifdef FEATURE_INTERNAL_SDAC
  /*  VOC_CODEC_SDAC              */,VOC_CODEC_CLASS_INTERNAL_STEREO
#else
  /*  VOC_CODEC_SDAC              */,VOC_CODEC_CLASS_EXTERNAL_STEREO
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
#if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
#ifdef FEATURE_INTERNAL_SADC
 /* VOC_CODEC_IN_MONO_SADC_OUT_MONO_HANDSET    */
                                    ,VOC_CODEC_CLASS_INTERNAL_SADC_HANDSET
 /* VOC_CODEC_IN_MONO_SADC_OUT_STEREO_HEADSET  */
                                    ,VOC_CODEC_CLASS_INTERNAL_SADC_HEADSET
 /* VOC_CODEC_IN_STEREO_SADC_OUT_MONO_HANDSET  */
                                    ,VOC_CODEC_CLASS_INTERNAL_SADC_HANDSET
 /* VOC_CODEC_IN_STEREO_SADC_OUT_STEREO_HEADSET*/
                                    ,VOC_CODEC_CLASS_INTERNAL_SADC_HEADSET
#else
 /* VOC_CODEC_IN_MONO_SADC_OUT_MONO_HANDSET    */
                                    ,VOC_CODEC_CLASS_EXTERNAL_SADC_HANDSET
 /* VOC_CODEC_IN_MONO_SADC_OUT_STEREO_HEADSET  */
                                    ,VOC_CODEC_CLASS_EXTERNAL_SADC_HEADSET
 /* VOC_CODEC_IN_STEREO_SADC_OUT_MONO_HANDSET  */
                                    ,VOC_CODEC_CLASS_EXTERNAL_SADC_HANDSET
 /* VOC_CODEC_IN_STEREO_SADC_OUT_STEREO_HEADSET*/
                                    ,VOC_CODEC_CLASS_EXTERNAL_SADC_HEADSET
#endif /* FEATURE_INTERNAL_SADC */
#endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */
#ifdef FEATURE_TTY
  /*  VOC_CODEC_TTY_ON_CHIP_1     */,VOC_CODEC_CLASS_INTERNAL
  /*  VOC_CODEC_TTY_OFF_BOARD     */,VOC_CODEC_CLASS_EXTERNAL
  /*  VOC_CODEC_TTY_VCO           */,VOC_CODEC_CLASS_INTERNAL
  /*  VOC_CODEC_TTY_HCO           */,VOC_CODEC_CLASS_INTERNAL
#endif /* FEATURE_TTY */
#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
  /*  VOC_CODEC_USB               */,VOC_CODEC_CLASS_INTERNAL
#ifdef FEATURE_INTERNAL_SDAC
  /*  VOC_CODEC_STEREO_USB        */,VOC_CODEC_CLASS_INTERNAL_STEREO
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
/* FM over BT AG */
#ifdef FEATURE_BT_AG
                                    ,VOC_CODEC_CLASS_BLUETOOTH
#endif                                    

};


#ifdef FEATURE_PHONE_VR
/* Codec VR type */
voc_codec_vr_type voc_cal_codec_vr_types[VOC_CODEC_MAX] =
{
  /*  VOC_CODEC_ON_CHIP_0         */ VOC_CODEC_VR_TYPE_HANDSET
#ifdef FEATURE_AVS_CRYSTAL_SPEECH
  /* VOC_CODEC_ON_CHIP_0_DUAL_MIC */,VOC_CODEC_VR_TYPE_HANDSET
#endif
  /*  VOC_CODEC_ON_CHIP_1         */,VOC_CODEC_VR_TYPE_HEADSET
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
  /*  VOC_CODEC_STEREO_HEADSET    */,VOC_CODEC_VR_TYPE_HEADSET
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
  /*  VOC_CODEC_ON_CHIP_AUX       */,VOC_CODEC_VR_TYPE_CARKIT
  /*  VOC_CODEC_ON_BOARD          */,VOC_CODEC_VR_TYPE_NONE
#ifdef FEATURE_SPEAKER_PHONE
  /*  VOC_CODEC_SPEAKER           */,VOC_CODEC_VR_TYPE_CARKIT
#endif /* FEATURE_SPEAKER_PHONE */
#ifdef FEATURE_BT
  /*  VOC_CODEC_BT_INTERCOM       */,VOC_CODEC_VR_TYPE_NONE
#ifdef FEATURE_BT_AG
  /*  VOC_CODEC_BT_AG             */,VOC_CODEC_VR_TYPE_HEADSET
#ifdef FEATURE_BT_AG_LOCAL_AUDIO
  /*  VOC_CODEC_BT_AG_LOCAL_AUDIO */,VOC_CODEC_VR_TYPE_NONE
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */
#endif /* FEATURE_BT_AG */
#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
  /* VOC_CODEC_BT_A2DP            */,VOC_CODEC_VR_TYPE_NONE
  /* VOC_CODEC_BT_A2DP_SCO        */,VOC_CODEC_VR_TYPE_HEADSET
#endif /* FEATURE_SBC_CODEC */
#endif /* FEATURE_BT */
  /*  VOC_CODEC_OFF_BOARD         */,VOC_CODEC_VR_TYPE_CARKIT
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
  /*  VOC_CODEC_SDAC              */,VOC_CODEC_VR_TYPE_NONE
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */
#if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
 /* VOC_CODEC_IN_MONO_SADC_OUT_MONO_HANDSET    */
                                    ,VOC_CODEC_VR_TYPE_NONE
 /* VOC_CODEC_IN_MONO_SADC_OUT_STEREO_HEADSET  */
                                    ,VOC_CODEC_VR_TYPE_NONE
 /* VOC_CODEC_IN_STEREO_SADC_OUT_MONO_HANDSET  */
                                    ,VOC_CODEC_VR_TYPE_NONE
 /* VOC_CODEC_IN_STEREO_SADC_OUT_STEREO_HEADSET*/
                                    ,VOC_CODEC_VR_TYPE_NONE
#endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */
#ifdef FEATURE_TTY
  /*  VOC_CODEC_TTY_ON_CHIP_1     */,VOC_CODEC_VR_TYPE_NONE
  /*  VOC_CODEC_TTY_OFF_BOARD     */,VOC_CODEC_VR_TYPE_NONE
  /*  VOC_CODEC_TTY_VCO           */,VOC_CODEC_VR_TYPE_NONE
  /*  VOC_CODEC_TTY_HCO           */,VOC_CODEC_VR_TYPE_NONE
#endif /* FEATURE_TTY */
#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
  /*  VOC_CODEC_USB               */,VOC_CODEC_VR_TYPE_CARKIT
#ifdef FEATURE_INTERNAL_SDAC
  /*  VOC_CODEC_STEREO_USB        */,VOC_CODEC_VR_TYPE_CARKIT
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
/* FM over BT AG */
#ifdef FEATURE_BT_AG
                                    ,VOC_CODEC_VR_TYPE_HEADSET
#endif                                    
};
#endif /* FEATURE_PHONE_VR */


/* <EJECT> */
/* ===========================================================================
**
**               V O C O D E R   C O N F I G U R A T I O N   A N D
**                  C A L I B R A T I O N   C O N S T A N T S
**
** =========================================================================*/

/* Compatibility defines
*/
#ifdef MSMAUD_DIN_LOOP_BIT
#define VOC_CAL_DIN_LOOP_V QDSP_DIN_LOOP_DIS_V
#else
#define VOC_CAL_DIN_LOOP_V QDSP_RESERVED_V
#endif


/* SDAC setup
*/
#define VOC_CAL_SDAC_CTRL_M       QDSP_I2S_CTRL_M            | \
                                  QDSP_SDAC_EN_M

#define VOC_CAL_SDAC_ENA_V        QDSP_I2S_DIS_V             | \
                                  QDSP_SDAC_EN_ON_V

#define VOC_CAL_SIGN_SWAP_V       QDSP_SDAC_SIGN_SWAP_DIS_V


#ifdef VOC_USE_ULAW
/* PCM format: 8-bit u-law without padding
*/
#define QDSP_PHONE_PCM_FORMAT    ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_ULAW_V        | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_ULAW_V        )

#else
/* PCM format: 13-bit linear with padding enabled
*/

/* Off-chip, on-board codec */
#define QDSP_PHONE_PCM_FORMAT    ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_ENA_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_ENA_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

/* Internal codec */
#if defined(FEATURE_AUDIO_CAL_MED_HIGH) || \
                                         defined(FEATURE_AUDIO_CAL_MED_HIGH_FFA)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#elif defined(MSMAUD_6260_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#elif defined(MSMAUD_6800_SURF_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_DIS_V          | \
                                    QDSP_TX_HPF_DIS_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )                                    
#elif defined(MSMAUD_6800_GSM_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#elif defined(MSMAUD_6280_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#elif defined (MSMAUD_6500_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#elif defined (MSMAUD_QSC6270_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_ENA_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#else
#define QDSP_INTERNAL_PCM_FMT_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                    QDSP_RX_HPF_DIS_V          | \
                                    QDSP_TX_HPF_ENA_V          | \
                                    QDSP_TX_SLOPE_FILT_DIS_V   | \
                                    QDSP_CODEC_RES_DIS_V       | \
                                    QDSP_DEC_PAD_DIS_V         | \
                                    QDSP_DEC_PCM_LIN_V         | \
                                    QDSP_ENC_PAD_DIS_V         | \
                                    QDSP_ENC_PCM_LIN_V         )
#endif /* (FEATURE_AUDIO_CAL_MED_HIGH) ||
                (FEATURE_AUDIO_CAL_MED_HIGH_FFA) */


#if defined(MSMAUD_QSC60X0_AUDIO_CAL)

#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

#elif defined(MSMAUD_6260_FFA_AUDIO_CAL)

#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

                                   
#elif defined(MSMAUD_6800_SURF_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
                                   
#elif defined(MSMAUD_6800_GSM_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )


#elif defined (MSMAUD_QSC60X5_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
#else

#if defined(FEATURE_FFA) || defined(FEATURE_TTP) || defined(T_FFA)
#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

#else
#define QDSP_INTERNAL_PCM_FORMAT ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

#endif /* FEATURE_FFA || FEATURE_TTP || T_FFA */

#endif /* MSMAUD_QSC60X0_AUDIO_CAL */

#if defined(MSMAUD_QSC60X0_AUDIO_CAL)

#define QDSP_INTERNAL_PCM_FORMAT_1 ( QDSP_PCM_MODE_INTERNAL_V   | \
                                     QDSP_RX_HPF_ENA_V          | \
                                     QDSP_TX_HPF_ENA_V          | \
                                     QDSP_TX_SLOPE_FILT_ENA_V   | \
                                     QDSP_CODEC_RES_DIS_V       | \
                                     QDSP_DEC_PAD_DIS_V         | \
                                     QDSP_DEC_PCM_LIN_V         | \
                                     QDSP_ENC_PAD_DIS_V         | \
                                     QDSP_ENC_PCM_LIN_V         )

#define QDSP_INTERNAL_PCM_FORMAT_SPEAKER ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

#elif defined(MSMAUD_6500_FFA_AUDIO_CAL)

#define QDSP_INTERNAL_PCM_FORMAT_1 ( QDSP_PCM_MODE_INTERNAL_V   | \
                                     QDSP_RX_HPF_ENA_V          | \
                                     QDSP_TX_HPF_ENA_V          | \
                                     QDSP_TX_SLOPE_FILT_ENA_V   | \
                                     QDSP_CODEC_RES_DIS_V       | \
                                     QDSP_DEC_PAD_DIS_V         | \
                                     QDSP_DEC_PCM_LIN_V         | \
                                     QDSP_ENC_PAD_DIS_V         | \
                                     QDSP_ENC_PCM_LIN_V         )


#define QDSP_INTERNAL_PCM_FORMAT_SPEAKER ( QDSP_PCM_MODE_INTERNAL_V   | \
                                           QDSP_RX_HPF_ENA_V          | \
                                           QDSP_TX_HPF_ENA_V          | \
                                           QDSP_TX_SLOPE_FILT_DIS_V   | \
                                           QDSP_CODEC_RES_DIS_V       | \
                                           QDSP_DEC_PAD_DIS_V         | \
                                           QDSP_DEC_PCM_LIN_V         | \
                                           QDSP_ENC_PAD_DIS_V         | \
                                           QDSP_ENC_PCM_LIN_V         )
#elif defined (MSMAUD_QSC60X5_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FORMAT_1 ( QDSP_PCM_MODE_INTERNAL_V   | \
                                     QDSP_RX_HPF_ENA_V          | \
                                     QDSP_TX_HPF_ENA_V          | \
                                     QDSP_TX_SLOPE_FILT_ENA_V   | \
                                     QDSP_CODEC_RES_DIS_V       | \
                                     QDSP_DEC_PAD_DIS_V         | \
                                     QDSP_DEC_PCM_LIN_V         | \
                                     QDSP_ENC_PAD_DIS_V         | \
                                     QDSP_ENC_PCM_LIN_V         )

#define QDSP_INTERNAL_PCM_FORMAT_SPEAKER ( QDSP_PCM_MODE_INTERNAL_V   | \
                                           QDSP_RX_HPF_ENA_V          | \
                                           QDSP_TX_HPF_ENA_V          | \
                                           QDSP_TX_SLOPE_FILT_DIS_V   | \
                                           QDSP_CODEC_RES_DIS_V       | \
                                           QDSP_DEC_PAD_DIS_V         | \
                                           QDSP_DEC_PCM_LIN_V         | \
                                           QDSP_ENC_PAD_DIS_V         | \
                                           QDSP_ENC_PCM_LIN_V         )
#else

#define QDSP_INTERNAL_PCM_FORMAT_1 ( QDSP_PCM_MODE_INTERNAL_V   | \
                                     QDSP_RX_HPF_ENA_V          | \
                                     QDSP_TX_HPF_ENA_V          | \
                                     QDSP_TX_SLOPE_FILT_ENA_V   | \
                                     QDSP_CODEC_RES_DIS_V       | \
                                     QDSP_DEC_PAD_DIS_V         | \
                                     QDSP_DEC_PCM_LIN_V         | \
                                     QDSP_ENC_PAD_DIS_V         | \
                                     QDSP_ENC_PCM_LIN_V         )

#define QDSP_INTERNAL_PCM_FORMAT_SPEAKER ( QDSP_PCM_MODE_INTERNAL_V   | \
                                           QDSP_RX_HPF_ENA_V          | \
                                           QDSP_TX_HPF_ENA_V          | \
                                           QDSP_TX_SLOPE_FILT_DIS_V   | \
                                           QDSP_CODEC_RES_DIS_V       | \
                                           QDSP_DEC_PAD_DIS_V         | \
                                           QDSP_DEC_PCM_LIN_V         | \
                                           QDSP_ENC_PAD_DIS_V         | \
                                           QDSP_ENC_PCM_LIN_V         )                                     
#endif  /* MSMAUD_QSC60X0_AUDIO_CAL */

#if defined(FEATURE_AUDIO_CAL_MED_HIGH_FFA)
#define QDSP_INTERNAL_PCM_FMT_1_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                      QDSP_RX_HPF_ENA_V          | \
                                      QDSP_TX_HPF_ENA_V          | \
                                      QDSP_TX_SLOPE_FILT_DIS_V   | \
                                      QDSP_CODEC_RES_DIS_V       | \
                                      QDSP_DEC_PAD_DIS_V         | \
                                      QDSP_DEC_PCM_LIN_V         | \
                                      QDSP_ENC_PAD_DIS_V         | \
                                      QDSP_ENC_PCM_LIN_V         )
#elif defined(MSMAUD_6260_FFA_AUDIO_CAL) || \
      defined(MSMAUD_6280_FFA_AUDIO_CAL) || \
      defined(MSMAUD_6500_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_1_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                      QDSP_RX_HPF_ENA_V          | \
                                      QDSP_TX_HPF_ENA_V          | \
                                      QDSP_TX_SLOPE_FILT_DIS_V   | \
                                      QDSP_CODEC_RES_DIS_V       | \
                                      QDSP_DEC_PAD_DIS_V         | \
                                      QDSP_DEC_PCM_LIN_V         | \
                                      QDSP_ENC_PAD_DIS_V         | \
                                      QDSP_ENC_PCM_LIN_V         )
#elif defined(MSMAUD_QSC6270_FFA_AUDIO_CAL)
#define QDSP_INTERNAL_PCM_FMT_1_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                      QDSP_RX_HPF_ENA_V          | \
                                      QDSP_TX_HPF_ENA_V          | \
                                      QDSP_TX_SLOPE_FILT_ENA_V   | \
                                      QDSP_CODEC_RES_DIS_V       | \
                                      QDSP_DEC_PAD_DIS_V         | \
                                      QDSP_DEC_PCM_LIN_V         | \
                                      QDSP_ENC_PAD_DIS_V         | \
                                      QDSP_ENC_PCM_LIN_V         )
#else
#define QDSP_INTERNAL_PCM_FMT_1_GSM ( QDSP_PCM_MODE_INTERNAL_V   | \
                                      QDSP_RX_HPF_DIS_V          | \
                                      QDSP_TX_HPF_ENA_V          | \
                                      QDSP_TX_SLOPE_FILT_ENA_V   | \
                                      QDSP_CODEC_RES_DIS_V       | \
                                      QDSP_DEC_PAD_DIS_V         | \
                                      QDSP_DEC_PCM_LIN_V         | \
                                      QDSP_ENC_PAD_DIS_V         | \
                                      QDSP_ENC_PCM_LIN_V         )
#endif /* defined(FEATURE_AUDIO_CAL_MED_HIGH_FFA) */
#endif  /* VOC_USE_ULAW */


/* PCM format: 8-bit u-law with padding enabled
*/
#define QDSP_AUX_PCM_FORMAT     ( QDSP_PCM_MODE_INTERNAL_V   | \
                                  QDSP_DEC_PAD_ENA_V         | \
                                  QDSP_DEC_PCM_ULAW_V        | \
                                  QDSP_ENC_PAD_ENA_V         | \
                                  QDSP_ENC_PCM_ULAW_V        )

#ifdef FEATURE_BT
#define QDSP_BT_INTERCOM_PCM_FORMAT  (QDSP_PCM_MODE_STANDALONE_V | \
                                      QDSP_RX_HPF_ENA_V          | \
                                      QDSP_TX_HPF_ENA_V          | \
                                      QDSP_TX_SLOPE_FILT_ENA_V   | \
                                      QDSP_CODEC_RES_DIS_V       | \
                                      QDSP_DEC_PAD_DIS_V         | \
                                      QDSP_DEC_PCM_LIN_V         | \
                                      QDSP_ENC_PAD_DIS_V         | \
                                      QDSP_ENC_PCM_LIN_V         )

#ifdef FEATURE_BT_AG
#ifdef MSMAUD_ALT_BT_AG_CONFIG
/* PCM Format contains DAI instead of BT mode.
*/
#define QDSP_BT_AG_PCM_FORMAT    ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

/* FM over BT AG */
#define QDSP_FM_BT_AG_PCM_FORMAT ( QDSP_PCM_MODE_STANDALONE_V | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )


#ifdef FEATURE_BT_AG_LOCAL_AUDIO
#define QDSP_BT_AG_LA_PCM_FORMAT  (QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */

#else /* MSMAUD_ALT_BT_AG_CONFIG */

#define QDSP_BT_AG_PCM_FORMAT    ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
/* FM over BT AG */
#define QDSP_FM_BT_AG_PCM_FORMAT ( QDSP_PCM_MODE_STANDALONE_V | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )


#ifdef FEATURE_AVS_AUDIO_DECODER_SCO
#define QDSP_BT_AG_MM_PCM_FORMAT ( QDSP_PCM_MODE_32K_STEREO_V | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
#endif /*FEATURE_AVS_AUDIO_DECODER_SCO*/

#ifdef FEATURE_BT_AG_LOCAL_AUDIO
#define QDSP_BT_AG_LA_PCM_FORMAT  (QDSP_PCM_MODE_STANDALONE_V | \
                                   QDSP_RX_HPF_ENA_V          | \
                                   QDSP_TX_HPF_ENA_V          | \
                                   QDSP_TX_SLOPE_FILT_ENA_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */
#endif /* MSMAUD_ALT_BT_AG_CONFIG */
#endif /* FEATURE_BT_AG */
#endif /* FEATURE_BT */

#if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)
#define QDSP_EXT_SADC_PCM_FORMAT  ( QDSP_PCM_MODE_ENCODER_V |\
                                QDSP_RX_HPF_DIS_V           |\
                                QDSP_DEC_PCM_LIN_V          |\
                                QDSP_ENC_PCM_LIN_V)

#endif  /* FEATURE_AVS_CRYSTAL_SPEECH && EATURE_EXTERNAL_SADC*/
/*
**  Constants for pcm_ctrl
*/

#ifdef VOC_USE_ULAW
/* 8-bit PCM Frames
*/
#define QDSP_PCM_CTRL_DEF       ( QDSP_PCM_LB_DIS_V          | \
                                  QDSP_PCM_CLK_SENSE_NORM_V  | \
                                  QDSP_DEC_PCM_WIDTH_8_V     | \
                                  QDSP_DEC_PCM_SLOT_V(0)     | \
                                  QDSP_ENC_PCM_WIDTH_8_V     | \
                                  QDSP_ENC_PCM_SLOT_V(0)     )
#else
/* 16-bit PCM frames
*/
#define QDSP_PCM_CTRL_DEF       ( QDSP_PCM_LB_DIS_V          | \
                                  QDSP_PCM_CLK_SENSE_NORM_V  | \
                                  QDSP_DEC_PCM_WIDTH_16_V    | \
                                  QDSP_DEC_PCM_SLOT_V(0)     | \
                                  QDSP_ENC_PCM_WIDTH_16_V    | \
                                  QDSP_ENC_PCM_SLOT_V(0)     )
#endif

#define QDSP_AUX_PCM_CTRL_DEF   ( QDSP_PCM_LB_DIS_V          | \
                                  QDSP_PCM_CLK_SENSE_NORM_V  | \
                                  QDSP_DEC_PCM_WIDTH_16_V    | \
                                  QDSP_DEC_PCM_SLOT_V(0)     | \
                                  QDSP_ENC_PCM_WIDTH_16_V    | \
                                  QDSP_ENC_PCM_SLOT_V(0)     )

/* Internal codec not used
*/
#define QDSP_CODEC_INT_UNUSED   0


#if defined(FEATURE_QSYNTH_COMMON) || defined(FEATURE_QTUNES_COMMON)
#define QDSP_INT_16K_PCM_FORMAT ( QDSP_PCM_MODE_32K_INT_V    | \
                                  QDSP_CODEC_RES_DIS_V       | \
                                  QDSP_WB_COMP_ENA_V         | \
                                  QDSP_DEC_PAD_DIS_V         | \
                                  QDSP_DEC_PCM_LIN_V         | \
                                  QDSP_SDAC_SIGN_SWAP_DIS_V  )
#endif /* FEATURE_QSYNTH_COMMON || FEATURE_QTUNES_COMMON */

#ifdef FEATURE_INTERNAL_SDAC
#define QDSP_INTERNAL_SDAC_PCM_FORMAT ( QDSP_PCM_MODE_32K_INT_STEREO_V | \
                                        QDSP_CODEC_RES_DIS_V           | \
                                        QDSP_WB_COMP_DIS_V             | \
                                        QDSP_DEC_PAD_DIS_V             | \
                                        QDSP_DEC_PCM_LIN_V             | \
                                        VOC_CAL_SIGN_SWAP_V            )
#endif /* FEATURE_INTERNAL_SDAC */

#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
#define QDSP_SBC_PCM_FORMAT           ( QDSP_PCM_MODE_32K_INT_STEREO_V | \
                                        QDSP_CODEC_RES_DIS_V           | \
                                        QDSP_WB_COMP_DIS_V             | \
                                        QDSP_DEC_PAD_DIS_V             | \
                                        QDSP_DEC_PCM_LIN_V             | \
                                        VOC_CAL_SIGN_SWAP_V            )
#endif /* FEATURE_SBC_CODEC || FEATURE_SBC_DSP_CODEC */

#ifdef FEATURE_EXTERNAL_SDAC
#define QDSP_SDAC_PCM_FORMAT    ( QDSP_PCM_MODE_32K_STEREO_V | \
                                  QDSP_CODEC_RES_DIS_V       | \
                                  QDSP_WB_COMP_DIS_V         | \
                                  QDSP_DEC_PAD_DIS_V         | \
                                  QDSP_DEC_PCM_LIN_V         | \
                                  VOC_CAL_SIGN_SWAP_V        )
#endif /* FEATURE_EXTERNAL_SDAC */

#if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
#define QDSP_SADC_PCM_FORMAT    ( QDSP_PCM_MODE_32K_INT_STEREO_V | \
                                  QDSP_CODEC_RES_DIS_V           | \
                                  QDSP_WB_COMP_DIS_V             | \
                                  QDSP_DEC_PAD_DIS_V             | \
                                  QDSP_DEC_PCM_LIN_V             | \
                                  VOC_CAL_SIGN_SWAP_V        )
#endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */


/*
**  Constants for codec_func_ctrl
*/
#define QDSP_CODEC_CTRL_AMP_OFF   QDSP_VBAP_CODEC_PWR_OFF_V
#define QDSP_CODEC_CTRL_AMP_1     QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_AMP_2     QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_VCO       QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_HCO       QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_AMP_AUX   QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_WB_AMP_1  QDSP_VBAP_CODEC_PWR_ON_V
#define QDSP_CODEC_CTRL_WB_AMP_2  QDSP_VBAP_CODEC_PWR_ON_V
#if defined(FEATURE_MM_REC) || defined(FEATURE_AVS_I2SSBC)
#define QDSP_CODEC_CTRL_PCM_IN_1  ( QDSP_VBAP_CODEC_I2S_MONO        | \
                                    QDSP_VBAP_CODEC_MODE_SEL_MONO   | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_ON_V )

#define QDSP_CODEC_CTRL_PCM_IN_2  ( QDSP_VBAP_CODEC_I2S_STEREO      | \
                                    QDSP_VBAP_CODEC_MODE_SEL_STEREO | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_ON_V        )

#define QDSP_CODEC_CTRL_PCM_IN_3  ( QDSP_VBAP_CODEC_INTERNAL_MONO   | \
                                    QDSP_VBAP_CODEC_MODE_SEL_MONO   | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_ON_V        )

#define QDSP_CODEC_CTRL_PCM_IN_4  ( QDSP_VBAP_CODEC_INTERNAL_STEREO | \
                                    QDSP_VBAP_CODEC_MODE_SEL_STEREO | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_ON_V        )
#endif /* FEATURE_MM_REC || FEATURE_AVS_I2SSBC */

#if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)

#define QDSP_EXT_CODEC_CTRL_DUAL_MIC  ( QDSP_VBAP_CODEC_MODE_SEL_STEREO | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_OFF_V        )

#endif  /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/


#define QDSP_CODEC_CTRL_DUAL_MIC  ( QDSP_VBAP_CODEC_MODE_SEL_STEREO | \
                                    QDSP_VBAP_CODEC_L_R_N           | \
                                    QDSP_VBAP_CODEC_PWR_ON_V        )



/*
**  Constants for codec_interface
*/

/* Internal codec
*/
#define QDSP_CODEC_INT          ( QDSP_LOOP_SEL_NONE_V       | \
                                  QDSP_I2S_DIS_V             | \
                                  QDSP_SDAC_SIGN_SAME_V      | \
                                  QDSP_AUX_CLK_DIS_V         | \
                                  QDSP_AUX_CLK_VAL_LO_V      | \
                                  QDSP_AUX_SYNC_VAL_LO_V     | \
                                  QDSP_CLK_SYNC_LOOP_DIS_V   | \
                                  QDSP_SDAC_BCLK_OUTP_V      | \
                                  QDSP_AUX_CLK_SENSE_NORM_V  | \
                                  QDSP_SDAC_MCLK_OUTP_V      | \
                                  QDSP_AUX_CODEC_NORM_V      | \
                                  QDSP_AUX_POL_NORMAL_V      | \
                                  QDSP_PCM_CLK_DIR_EXT_V     | \
                                  QDSP_SDAC_EN_OFF_V         )

/* off-chip, on-board codec
*/
#define QDSP_CODEC_ON_BOARD     ( QDSP_LOOP_SEL_NONE_V       | \
                                  QDSP_I2S_DIS_V             | \
                                  QDSP_SDAC_SIGN_SAME_V      | \
                                  QDSP_AUX_CLK_DIS_V         | \
                                  QDSP_AUX_CLK_VAL_LO_V      | \
                                  QDSP_AUX_SYNC_VAL_LO_V     | \
                                  QDSP_CLK_SYNC_LOOP_DIS_V   | \
                                  QDSP_SDAC_BCLK_OUTP_V      | \
                                  QDSP_AUX_CLK_SENSE_NORM_V  | \
                                  QDSP_SDAC_MCLK_OUTP_V      | \
                                  QDSP_AUX_CODEC_NORM_V      | \
                                  QDSP_AUX_POL_NORMAL_V      | \
                                  QDSP_PCM_CLK_DIR_MOD_V     | \
                                  QDSP_SDAC_EN_OFF_V         )

/* off-chip, off-board codec
*/

/* Configure the AUX PCM interface into primary PCM mode */
#if defined(MSMAUD_QSC60X5_AUDIO_HW)
/* For Q60X5 platforms */
#define QDSP_CODEC_OFF_BOARD    ( QDSP_AUX_CODEC_MODE_AUX_PCM    | \
                                  QDSP_AUX_PCM_MODE_MASTER_PRIM  | \
                                  QDSP_PCM_SYNC_INVERT_DIS       | \
                                  QDSP_PCM_SYNC_SHORT_OFFSET_DIS | \
                                  QDSP_PCM_SYNC_LONG_OFFSET_DIS  | \
                                  QDSP_ADSP_CODEC_CTL_ENA        | \
                                  QDSP_AUX_PCM_ENABLE            )

#elif defined(MSMAUD_6800A_AUX_INTERFACE)
/* For platforms that have HW Codec parameter setting like the 6800A */
#define QDSP_CODEC_OFF_BOARD    ( QDSP_LOOP_SEL_NONE_V       | \
                                  QDSP_I2S_DIS_V             | \
                                  QDSP_AUX_PRI_PCM_ENA_V     )

#else
/* For 6050, 6100, 6250, 6500, 6550, ... */
#define QDSP_CODEC_OFF_BOARD    ( QDSP_LOOP_SEL_NONE_V       | \
                                  QDSP_I2S_DIS_V             | \
                                  QDSP_SDAC_SIGN_SAME_V      | \
                                  QDSP_AUX_CLK_ENA_V         | \
                                  QDSP_AUX_CLK_VAL_LO_V      | \
                                  QDSP_AUX_SYNC_VAL_LO_V     | \
                                  QDSP_CLK_SYNC_LOOP_DIS_V   | \
                                  QDSP_SDAC_BCLK_OUTP_V      | \
                                  QDSP_AUX_CLK_SENSE_NORM_V  | \
                                  QDSP_SDAC_MCLK_OUTP_V      | \
                                  QDSP_AUX_CODEC_AUX_V       | \
                                  QDSP_AUX_POL_INVERTED_V    | \
                                  QDSP_PCM_CLK_DIR_EXT_V     | \
                                  QDSP_SDAC_EN_OFF_V         )
#endif /* MSMAUD_QSC60X5_AUDIO_HW */

#ifdef FEATURE_EXTERNAL_SDAC
/* EXTERNAL STEREO DAC
*/

#ifdef MSMAUD_QSC60X5_AUDIO_HW
#define QDSP_CODEC_SDAC         (QDSP_AUX_CODEC_MODE_I2S     | \
                                 QDSP_I2S_CLK_MODE_MASTER    | \
                                 QDSP_I2S_SDAC_MODE          | \
                                 QDSP_I2S_MCLK_MODE_MASTER   | \
                                 QDSP_I2S_MCLK_SRC_SDAC_CLK  | \
                                 QDSP_ADSP_CODEC_CTL_ENA     | \
                                 QDSP_I2S_ENABLE)
#else /* 6050, 6100, 6250, 6500, 6550, ... */
/* Currently, 6800A not known to be different from other non-60X5 6K platforms*/
#define QDSP_CODEC_SDAC         ( QDSP_I2S_DIS_V             | \
                                  QDSP_SDAC_SIGN_SAME_V      | \
                                  QDSP_AUX_CLK_DIS_V         | \
                                  QDSP_AUX_CLK_VAL_LO_V      | \
                                  QDSP_AUX_SYNC_VAL_LO_V     | \
                                  QDSP_CLK_SYNC_LOOP_DIS_V   | \
                                  QDSP_SDAC_BCLK_OUTP_V      | \
                                  QDSP_AUX_CLK_SENSE_NORM_V  | \
                                  QDSP_SDAC_MCLK_OUTP_V      | \
                                  QDSP_AUX_CODEC_NORM_V      | \
                                  QDSP_AUX_POL_NORMAL_V      | \
                                  QDSP_PCM_CLK_DIR_MOD_V     | \
                                  VOC_CAL_SDAC_ENA_V         )
#endif
#endif /* FEATURE_EXTERNAL_SDAC */

#ifdef FEATURE_EXTERNAL_SADC
#define VOC_CAL_SADC_ENA_V        QDSP_I2S_DIS_V             | \
                                  QDSP_RESERVED_V

#define QDSP_CODEC_SADC         ( QDSP_I2S_ENA_V             | \
                                  QDSP_SDAC_SIGN_REV_V       | \
                                  QDSP_AUX_CLK_ENA_V         | \
                                  QDSP_AUX_CLK_VAL_LO_V      | \
                                  QDSP_AUX_SYNC_VAL_LO_V     | \
                                  QDSP_CLK_SYNC_LOOP_DIS_V   | \
                                  QDSP_SDAC_BCLK_INP_V       | \
                                  QDSP_AUX_CLK_SENSE_NORM_V  | \
                                  QDSP_SDAC_MCLK_OUTP_V      | \
                                  QDSP_AUX_CODEC_NORM_V      | \
                                  QDSP_AUX_POL_NORMAL_V      | \
                                  QDSP_PCM_CLK_DIR_MOD_V     | \
                                  VOC_CAL_SADC_ENA_V         )
#endif /* FEATURE_EXTERNAL_SADC */

#if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)
#define QDSP_CODEC_EXT_SADC_DUALMIC  ( QDSP_I2S_ENABLE          |\
                               QDSP_ADSP_CODEC_CTL_ENA  |\
                               QDSP_I2S_CLK_MODE_SLAVE  |\
                               QDSP_I2S_MCLK_MODE_SLAVE |\
                               QDSP_AUX_CODEC_MODE_I2S )

#endif/*FEATURE_AVS_CRYSTAL_SPEECH && FEATURE_EXTERNAL_SADC*/


#ifndef MSMAUD_UP_DMA_PATH_CONTROL
/*
**  Constants for DMA Path Control
*/
#define QDSP_DMA_DEF            ( QDSP_DMA_CH_45_SEL_CODEC_V | \
                                  QDSP_DMA_CH_23_SEL_DFM_V   | \
                                  QDSP_DMA_CH_01_SEL_PCM_V   )

#endif /* MSMAUD_UP_DMA_PATH_CONTROL */

/*
 * This section is specifically for incall mixer configuration.
 */
#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
#define QDSP_INTERNAL_PCM_FORMAT_MIXER ( QDSP_PCM_MODE_INTERNAL_V   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )

/* This is the new field added for SATURN HW codec, DSP
 * always needs it to be set to ONE for internal codecs.
 */
#define QDSP_INTERNAL_CODEC_MIXER 0x0001

#define QDSP_INTERNAL_PCM_FORMAT_1_MIXER ( QDSP_PCM_MODE_DECODER_V   | \
                                     QDSP_RX_HPF_DIS_V          | \
                                     QDSP_TX_HPF_DIS_V          | \
                                     QDSP_TX_SLOPE_FILT_DIS_V   | \
                                     QDSP_CODEC_RES_DIS_V       | \
                                     QDSP_DEC_PAD_DIS_V         | \
                                     QDSP_DEC_PCM_LIN_V         | \
                                     QDSP_ENC_PAD_DIS_V         | \
                                     QDSP_ENC_PCM_LIN_V         )

#define QDSP_BT_AG_PCM_FORMAT_MIXER    ((QDSP_PCM_MODE_M      + \
                                   QDSP_PCM_MODE_ENCODER_V)   | \
                                   QDSP_RX_HPF_DIS_V          | \
                                   QDSP_TX_HPF_DIS_V          | \
                                   QDSP_TX_SLOPE_FILT_DIS_V   | \
                                   QDSP_CODEC_RES_DIS_V       | \
                                   QDSP_DEC_PAD_DIS_V         | \
                                   QDSP_DEC_PCM_LIN_V         | \
                                   QDSP_ENC_PAD_DIS_V         | \
                                   QDSP_ENC_PCM_LIN_V         )
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */

/* FM over BT AG */
#if defined(MSMAUD_ADIE_CODEC_FM_BT_AG_CONFIG_SEQ) 

#define VOCCAL_FM_OVER_BT_AG

#endif


/* <EJECT> */
/* ===========================================================================
**
**               V O C O D E R   C O N F I G U R A T I O N   A N D
**                    C A L I B R A T I O N   D A T A
**
** =========================================================================*/

/*
 * This section is specifically for incall mixer configuration.
 */
#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
/* Internal codec 0 - for mixer architecture */
const qdsp_cmd_codec_config_type voc_cal_codec_int0_mixer = {
  QDSP_INTERNAL_PCM_FORMAT_MIXER,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_INTERNAL_CODEC_MIXER,  /* Internal codec control: For Saturn HW */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
/* Internal codec 0 dual mic - for mixer architecture */
const qdsp_cmd_codec_config_type voc_cal_codec_int0_dual_mic_mixer = {
  QDSP_INTERNAL_PCM_FORMAT_MIXER,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_DUAL_MIC,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_INTERNAL_CODEC_MIXER,  /* Internal codec control: For Saturn HW */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

/* Internal codec 1 - for mixer architecture */
const qdsp_cmd_codec_config_type voc_cal_codec_int1_mixer = {
  QDSP_INTERNAL_PCM_FORMAT_1_MIXER,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_2,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_INTERNAL_CODEC_MIXER,  /* Internal codec control: For Saturn HW */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Bluetooth AG codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_ag_mixer = {
  QDSP_BT_AG_PCM_FORMAT_MIXER,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_OFF_BOARD,
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
};
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */

/* Internal codec 0 */
const qdsp_cmd_codec_config_type voc_cal_codec_int0 = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Internal codec 0 (GSM) */
const qdsp_cmd_codec_config_type voc_cal_codec_gsm_int0 = {
  QDSP_INTERNAL_PCM_FMT_GSM,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
/* Internal codec 0 dual mic */
const qdsp_cmd_codec_config_type voc_cal_codec_int0_dual_mic = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_DUAL_MIC,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Internal codec 0 dual mic (GSM) */
const qdsp_cmd_codec_config_type voc_cal_codec_gsm_int0_dual_mic = {
  QDSP_INTERNAL_PCM_FMT_GSM,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_DUAL_MIC,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

/* Internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_int1 = {
  QDSP_INTERNAL_PCM_FORMAT_1,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_2,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Internal codec 1 (GSM) */
const qdsp_cmd_codec_config_type voc_cal_codec_gsm_int1 = {
  QDSP_INTERNAL_PCM_FMT_1_GSM,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_2,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Internal codec, aux channel */
const qdsp_cmd_codec_config_type voc_cal_codec_aux = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_AUX,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_SPEAKER_PHONE
/* Internal codec, aux ear, mic1 */
const qdsp_cmd_codec_config_type voc_cal_codec_speaker = {
#if defined(MSMAUD_6500_FFA_AUDIO_CAL) || defined(MSMAUD_QSC60X0_AUDIO_CAL) || \
    defined(MSMAUD_QSC60X5_AUDIO_CAL)
  QDSP_INTERNAL_PCM_FORMAT_SPEAKER,
#else
  QDSP_INTERNAL_PCM_FORMAT,
#endif
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* Internal codec, aux ear, mic1 */
const qdsp_cmd_codec_config_type voc_cal_codec_gsm_speaker = {
  QDSP_INTERNAL_PCM_FMT_GSM,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_SPEAKER_PHONE */

/* Off-chip, on-board codec */
const qdsp_cmd_codec_config_type voc_cal_codec_on_board = {
  QDSP_PHONE_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_ON_BOARD,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_BT
/* Bluetooth Intercom codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_intercom = {
  QDSP_BT_INTERCOM_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
};

#ifdef FEATURE_BT_AG
#ifdef MSMAUD_ALT_BT_AG_CONFIG
/* Bluetooth AG codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_ag = {
  QDSP_BT_AG_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_OFF,
  QDSP_CODEC_INT,
  QDSP_DMA_BT_CODEC_INT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_BT_V
};

/* FM over BT AG */
const qdsp_cmd_codec_config_type voc_cal_codec_fm_bt_ag = {
  QDSP_FM_BT_AG_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_OFF,
  QDSP_CODEC_INT,
  QDSP_DMA_BT_CODEC_INT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
};


#ifdef FEATURE_BT_AG_LOCAL_AUDIO
/* Bluetooth AG Local Audio codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_ag_la = {
  QDSP_BT_AG_LA_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
  QDSP_DMA_BT_CODEC_INT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
};
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */

#else /* MSMAUD_ALT_BT_AG_CONFIG */

/* Bluetooth AG codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_ag = {
  QDSP_BT_AG_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_OFF_BOARD,
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
};

/* FM over BT AG */
const qdsp_cmd_codec_config_type voc_cal_codec_fm_bt_ag = {
  QDSP_FM_BT_AG_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_OFF_BOARD,
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
};

#ifdef FEATURE_AVS_AUDIO_DECODER_SCO
/* Bluetooth AG-MM codec */
const qdsp_cmd_codec_config_type voc_cal_mm_codec_bt_ag = {
  QDSP_BT_AG_MM_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_OFF_BOARD,
  QDSP_DMA_BT_CODEC_INT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_BT_V
};
#endif /* FEATURE_AVS_AUDIO_DECODER_SCO */

#ifdef FEATURE_BT_AG_LOCAL_AUDIO
/* Bluetooth AG Local Audio codec */
const qdsp_cmd_codec_config_type voc_cal_codec_bt_ag_la = {
  QDSP_BT_AG_LA_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_1,
  QDSP_CODEC_INT,
  QDSP_DMA_BT_CODEC_INT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
};
#endif /* FEATURE_BT_AG_LOCAL_AUDIO */
#endif /* MSMAUD_ALT_BT_AG_CONFIG */
#endif /* FEATURE_BT_AG */

#ifdef FEATURE_AVS_I2SSBC
const qdsp_cmd_codec_config_type voc_cal_codec_i2ssbc = {
  QDSP_SADC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_2,
  QDSP_CODEC_SADC,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SADC,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
  /* QDSP_8KHZ_INT_MODE_PCM_V */
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_AVS_I2SSBC */

#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
const qdsp_cmd_codec_config_type voc_cal_codec_bt_sbc = {
  QDSP_SBC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_WB_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_SBC_CODEC */
#endif /* FEATURE_BT */

/* Off-chip, off-board codec */
const qdsp_cmd_codec_config_type voc_cal_codec_off_board = {
  QDSP_AUX_PCM_FORMAT,
  QDSP_AUX_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_OFF_BOARD,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};

#if defined(FEATURE_QSYNTH_COMMON) || defined(FEATURE_QTUNES_COMMON)
/* 16KHz internal codec 0 */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_int0 = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_WB_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* 16KHz internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_int1 = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_WB_AMP_2,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* 16KHz internal codec, aux channel  */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_aux = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_AUX,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_SPEAKER_PHONE
/* 16KHz internal codec, aux ear, mic1  */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_speaker = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_WB_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_SPEAKER_PHONE */
#endif /* FEATURE_QSYNTH_COMMON || FEATURE_QTUNES_COMMON */

#ifdef FEATURE_MM_REC
/* Internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_int1_mm_rec = {
  QDSP_INTERNAL_PCM_FORMAT_1,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

const qdsp_cmd_codec_config_type voc_cal_codec_16k_int0_mm_rec = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

const qdsp_cmd_codec_config_type voc_cal_codec_int0_mm_rec = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* 16KHz internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_int1_mm_rec = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* 16KHz internal codec, aux channel  */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_aux_mm_rec = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_SPEAKER_PHONE
/* 16KHz internal codec, aux ear, mic1  */
const qdsp_cmd_codec_config_type voc_cal_codec_16k_speaker_mm_rec = {
  QDSP_INT_16K_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_SPEAKER_PHONE */

#ifdef FEATURE_INTERNAL_SDAC
/* PCM output using Internal Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sdac_mm_rec = {
  QDSP_INTERNAL_SDAC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#elif defined(FEATURE_EXTERNAL_SDAC)
/* PCM output using External Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sdac_mm_rec = {
  QDSP_SDAC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_SDAC,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SDAC,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* #ifdef FEATURE_INTERNAL_SDAC */

#ifdef FEATURE_INTERNAL_SADC
/* PCM output using External Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sadc_mono_mm_rec = {
  QDSP_SADC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

const qdsp_cmd_codec_config_type voc_cal_codec_sadc_stereo_mm_rec = {
  QDSP_SADC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_4,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#elif defined(FEATURE_EXTERNAL_SADC)
/* PCM output using External Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sadc_mono_mm_rec = {
  QDSP_SADC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_1,
  QDSP_CODEC_SADC,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SADC,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

const qdsp_cmd_codec_config_type voc_cal_codec_sadc_stereo_mm_rec = {
  QDSP_SADC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_2,
  QDSP_CODEC_SADC,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SADC,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
  /* QDSP_8KHZ_INT_MODE_PCM_V */
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_INTERNAL_SADC */

const qdsp_cmd_codec_config_type voc_cal_codec_off_board_mm_rec = {
  QDSP_AUX_PCM_FORMAT,
  QDSP_AUX_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_OFF_BOARD,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};

/* Off-chip, on-board codec */
const qdsp_cmd_codec_config_type voc_cal_codec_on_board_mm_rec = {
  QDSP_PHONE_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_PCM_IN_3,
  QDSP_CODEC_ON_BOARD,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_MM_REC */

#ifdef FEATURE_INTERNAL_SDAC
/* PCM output using Internal Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sdac = {
  QDSP_INTERNAL_SDAC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_WB_AMP_1,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#elif defined(FEATURE_EXTERNAL_SDAC)
/* PCM output using External Stereo DAC */
const qdsp_cmd_codec_config_type voc_cal_codec_sdac = {
  QDSP_SDAC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_INT_UNUSED,
  QDSP_CODEC_SDAC,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SDAC,          /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_PCM_V
#else
  QDSP_DMA_DEF
#endif
};
#endif

#ifdef FEATURE_TTY
/* Channel 1 uses same as voc_cal_codec_int1 */

/* TTY in VCO mode on Internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_tty_vco = {
  QDSP_INTERNAL_PCM_FORMAT_1,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_VCO,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

/* TTY in HCO mode on Internal codec 1 */
const qdsp_cmd_codec_config_type voc_cal_codec_tty_hco = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_HCO,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#endif /* FEATURE_TTY */

#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
/* USB analog carkit, on-chip codec   */
const qdsp_cmd_codec_config_type voc_cal_codec_usb = {
  QDSP_INTERNAL_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_AUX,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};

#ifdef FEATURE_INTERNAL_SDAC
/* Stereo USB analog carkit, on-chip codec   */
const qdsp_cmd_codec_config_type voc_cal_codec_stereo_usb = {
  QDSP_INTERNAL_SDAC_PCM_FORMAT,
  QDSP_PCM_CTRL_DEF,
  QDSP_CODEC_CTRL_AMP_AUX,
  QDSP_CODEC_INT,
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_DEFAULT,       /* DMA Path control        */
  QDSP_8KHZ_INT_MODE_CODEC_V
#else
  QDSP_DMA_DEF
#endif
};
#endif /* FEATURE_INTERNAL_SDAC */
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */


#if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)
  
const qdsp_cmd_codec_config_type voc_cal_codec_tx_external_sadc_rx_internal = {
  QDSP_EXT_SADC_PCM_FORMAT,      
  QDSP_PCM_CTRL_DEF,          
  QDSP_EXT_CODEC_CTRL_DUAL_MIC,   
  QDSP_CODEC_EXT_SADC_DUALMIC, 
#ifdef MSMAUD_UP_DMA_PATH_CONTROL
  QDSP_DMA_PATH_SADC,           
  QDSP_8KHZ_INT_MODE_CODEC_V   
#else
  QDSP_DMA_DEF                  
#endif
};

#endif /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/

#ifdef MSMAUD_PMIC_CONFIG
const voc_pmic_config_type voc_cal_pmic_config_legacy_mic = {
  TRUE,
  FALSE
};
const voc_pmic_config_type voc_cal_pmic_config_legacy_nomic = {
  FALSE,
  FALSE
};
/* Capless mode is only for HPH_L/R (headset/headphone) */
#ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE  
const voc_pmic_config_type voc_cal_pmic_config_capless_mic = {
  TRUE,
  TRUE
};
const voc_pmic_config_type voc_cal_pmic_config_capless_nomic = {
  FALSE,
  TRUE
};
#endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
#endif  /* MSMAUD_PMIC_CONFIG */


/* ===========================================================================
**   ADIE Configuration
** =========================================================================*/

#ifdef MSMAUD_ADIE_CODEC

/* ADIE Register values */
const adie_codec_reg_type voc_adie_handset_config[] =
  MSMAUD_ADIE_CODEC_HANDSET_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_handset_no_micamp2_config[] =
  MSMAUD_ADIE_CODEC_HANDSET_NO_MICAMP2_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_handset_no_mic_config[] =
  MSMAUD_ADIE_CODEC_HANDSET_NO_MIC_CONFIG_SEQ;

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
const adie_codec_reg_type voc_adie_handset_dual_mic_config[] =
  MSMAUD_ADIE_CODEC_HANDSET_DUAL_MIC_CONFIG_SEQ;
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

const adie_codec_reg_type voc_adie_mono_headset_config[] =
  MSMAUD_ADIE_CODEC_MONO_HEADSET_CONFIG_SEQ;

/* FM over BT AG */
#if defined (VOCCAL_FM_OVER_BT_AG)
const adie_codec_reg_type voc_adie_fm_bt_ag_headset_config[] =
  MSMAUD_ADIE_CODEC_FM_BT_AG_CONFIG_SEQ;
#endif /* VOCCAL_FM_OVER_BT_AG */

#ifdef FEATURE_INTERNAL_SDAC
const adie_codec_reg_type voc_adie_stereo_headset_config[] =
  MSMAUD_ADIE_CODEC_STEREO_HEADSET_CONFIG_SEQ;
#endif /* FEATURE_INTERNAL_SDAC */

const adie_codec_reg_type voc_adie_mono_headphone_config[] =
  MSMAUD_ADIE_CODEC_MONO_HEADPHONE_CONFIG_SEQ;

#ifdef FEATURE_INTERNAL_SDAC
const adie_codec_reg_type voc_adie_stereo_headphone_config[] =
  MSMAUD_ADIE_CODEC_STEREO_HEADPHONE_CONFIG_SEQ;
#endif

const adie_codec_reg_type voc_adie_aux_config[] =
  MSMAUD_ADIE_CODEC_AUX_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_aux_no_mic_config[] =
  MSMAUD_ADIE_CODEC_AUX_NO_MIC_CONFIG_SEQ;

#ifdef FEATURE_SPEAKER_PHONE
const adie_codec_reg_type voc_adie_speaker_config[] =
  MSMAUD_ADIE_CODEC_SPEAKER_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_speaker_no_mic_config[] =
  MSMAUD_ADIE_CODEC_SPEAKER_NO_MIC_CONFIG_SEQ;
#endif

const adie_codec_reg_type voc_adie_tty_vco_config[] =
  MSMAUD_ADIE_CODEC_TTY_VCO_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_tty_hco_config[] =
  MSMAUD_ADIE_CODEC_TTY_HCO_CONFIG_SEQ;

#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
const adie_codec_reg_type voc_adie_usb_config[] =
  MSMAUD_ADIE_CODEC_USB_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_usb_no_mic_config[] =
  MSMAUD_ADIE_CODEC_USB_NO_MIC_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_stereo_usb_config[] =
  MSMAUD_ADIE_CODEC_STEREO_USB_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_stereo_usb_no_mic_config[] =
  MSMAUD_ADIE_CODEC_STEREO_USB_NO_MIC_CONFIG_SEQ;
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */

#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
const adie_codec_reg_type voc_adie_pwr_down_config[] =
  MSMAUD_ADIE_CODEC_PD_CONFIG_SEQ;
#endif /* FEATURE_SBC_CODEC */

#ifdef FEATURE_INTERNAL_SADC
const adie_codec_reg_type voc_adie_mono_sadc_mono_handset_config[] =
  MSMAUD_ADIE_CODEC_MONO_SADC_MONO_HANDSET_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_mono_sadc_stereo_headset_config[] =
  MSMAUD_ADIE_CODEC_MONO_SADC_STEREO_HEADSET_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_stereo_sadc_mono_handset_config[] =
  MSMAUD_ADIE_CODEC_STEREO_SADC_MONO_HANDSET_CONFIG_SEQ;

const adie_codec_reg_type voc_adie_stereo_sadc_stereo_headset_config[] =
  MSMAUD_ADIE_CODEC_STEREO_SADC_STEREO_HEADSET_CONFIG_SEQ;
#endif /* FEATURE_INTERNAL_SADC */

/* ADIE modes */
/* Handset: Earpiece and MIC1 */
const voc_adie_codec_config_type voc_adie_codec_handset_config =
{
  sizeof(voc_adie_handset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_HANDSET_DELAY_CONFIG_SIZE,
  voc_adie_handset_config
};

/* Handset: Earpiece and MIC1 with low codec gain and bypass MICAMP2 */
const voc_adie_codec_config_type voc_adie_codec_handset_no_micamp2_config =
{
  sizeof(voc_adie_handset_no_micamp2_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_HANDSET_DELAY_CONFIG_SIZE,
  voc_adie_handset_no_micamp2_config
};

/* Handset: Earpiece and NO mic inputs */
const voc_adie_codec_config_type voc_adie_codec_handset_no_mic_config =
{
  sizeof(voc_adie_handset_no_mic_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_HANDSET_NO_MIC_DELAY_CONFIG_SIZE,
  voc_adie_handset_no_mic_config
};

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
/* Handset: Earpiece and dual mic inputs */
const voc_adie_codec_config_type voc_adie_codec_handset_dual_mic_config =
{
  sizeof(voc_adie_handset_dual_mic_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_HANDSET_DUAL_MIC_DELAY_CONFIG_SIZE,
  voc_adie_handset_dual_mic_config
};
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

/* Headset: MIC2 and left headphone channel */
const voc_adie_codec_config_type voc_adie_codec_mono_headset_config =
{
  sizeof(voc_adie_mono_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_MONO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_mono_headset_config
};

/* FM over BT AG */
#if defined (VOCCAL_FM_OVER_BT_AG)
const voc_adie_codec_config_type voc_adie_codec_fm_bt_ag_config =
{
  sizeof(voc_adie_fm_bt_ag_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_FM_BT_AG_DELAY_CONFIG_SIZE,
  voc_adie_fm_bt_ag_headset_config
};
#else
/* This target do not support FM over BT AG Adie settings */
const voc_adie_codec_config_type voc_adie_codec_fm_bt_ag_config =
{
  0,
  0,
  NULL
};
#endif /* VOCCAL_FM_OVER_BT_AG */

/* Simulated Stereo Headset: left headphone channel fed to
 * both left and right, plus MIC2 input.
 */
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
const voc_adie_codec_config_type voc_adie_codec_simul_stereo_headset_config =
{
#ifdef FEATURE_INTERNAL_SDAC
  sizeof(voc_adie_stereo_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_stereo_headset_config
#else
  0, 0, NULL
#endif /* FEATURE_INTERNAL_SDAC */
};
#endif /* FEATURE_STEREO_HEADSET && FEATURE_INTERNAL_SDAC */

const voc_adie_codec_config_type voc_adie_codec_headset_config =
{
#if defined(FEATURE_STEREO_HEADSET) && defined(FEATURE_INTERNAL_SDAC)
  /* Headset: MIC2 and MONO output fed to both left and right channels */
  sizeof(voc_adie_stereo_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_stereo_headset_config
#else
  /* Headset: MIC2 and left headphone channel */
  sizeof(voc_adie_mono_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_MONO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_mono_headset_config
#endif /* FEATURE_STEREO_HEADSET && FEATURE_INTERNAL_SDAC */
};

/* Mono Headphone: left headphone channel (no mic input) */
const voc_adie_codec_config_type voc_adie_codec_mono_headphone_config =
{
  sizeof(voc_adie_mono_headphone_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_MONO_HEADPHONE_DELAY_CONFIG_SIZE,
  voc_adie_mono_headphone_config
};

/* Stereo Headphone: left + right headphone channels (no mic) */
#if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
const voc_adie_codec_config_type voc_adie_codec_stereo_headphone_config =
{
#ifdef FEATURE_INTERNAL_SDAC
  sizeof(voc_adie_stereo_headphone_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_HEADPHONE_DELAY_CONFIG_SIZE,
  voc_adie_stereo_headphone_config
#else
  0, 0, NULL
#endif /* FEATURE_INTERNAL_SDAC */
};
#endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */


#ifdef FEATURE_SPEAKER_PHONE
/* Speaker phone: Auxillary outputs and MIC1 */
const voc_adie_codec_config_type voc_adie_codec_speaker_config =
{
  sizeof(voc_adie_speaker_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_SPEAKER_DELAY_CONFIG_SIZE,
  voc_adie_speaker_config
};

/* Speaker phone: Auxillary outputs (no mic input */
const voc_adie_codec_config_type voc_adie_codec_speaker_no_mic_config =
{
  sizeof(voc_adie_speaker_no_mic_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_SPEAKER_NO_MIC_DELAY_CONFIG_SIZE,
  voc_adie_speaker_no_mic_config
};
#endif /* FEATURE_SPEAKER_PHONE */


/* Auxillary device: MIC and left + right aux channels */
const voc_adie_codec_config_type voc_adie_codec_aux_config =
{
  sizeof(voc_adie_aux_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_AUX_DELAY_CONFIG_SIZE,
  voc_adie_aux_config
};

/* Auxillary device:  left + right aux channels and NO mic input */
const voc_adie_codec_config_type voc_adie_codec_aux_no_mic_config =
{
  sizeof(voc_adie_aux_no_mic_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_AUX_NO_MIC_DELAY_CONFIG_SIZE,
  voc_adie_aux_no_mic_config
};

/* TTY in VCO mode: MIC1 and left headphone channel */
const voc_adie_codec_config_type voc_adie_codec_tty_vco_config =
{
  sizeof(voc_adie_tty_vco_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_TTY_VCO_DELAY_CONFIG_SIZE,
  voc_adie_tty_vco_config
};

/* TTY in HCO mode: MIC2 and handset earpiece */
const voc_adie_codec_config_type voc_adie_codec_tty_hco_config =
{
  sizeof(voc_adie_tty_hco_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_TTY_HCO_DELAY_CONFIG_SIZE,
  voc_adie_tty_hco_config
};

#if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
/* Auxillary device: USB Carkit: MIC and left aux channel */
const voc_adie_codec_config_type voc_adie_codec_usb_config =
{
  sizeof(voc_adie_usb_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_USB_DELAY_CONFIG_SIZE,
  voc_adie_usb_config
};

/* Auxillary device: USB Carkit: No MIC and left aux channel */
const voc_adie_codec_config_type voc_adie_codec_usb_no_mic_config =
{
  sizeof(voc_adie_usb_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_USB_NO_MIC_DELAY_CONFIG_SIZE,
  voc_adie_usb_no_mic_config
};


/* Simulated Stereo USB: left aux channel fed to
 * both left and right, plus MIC input.
 */
const voc_adie_codec_config_type voc_adie_codec_simul_stereo_usb_config =
{
  sizeof(voc_adie_stereo_usb_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_USB_DELAY_CONFIG_SIZE,
  voc_adie_stereo_usb_config
};

/* Auxillary device: USB Carkit: No MIC and left & right aux channel */
const voc_adie_codec_config_type voc_adie_codec_stereo_usb_no_mic_config =
{
  sizeof(voc_adie_stereo_usb_no_mic_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_USB_NO_MIC_DELAY_CONFIG_SIZE,
  voc_adie_stereo_usb_no_mic_config
};
#endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */

#if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
const voc_adie_codec_config_type voc_adie_codec_pwr_down_config = {
  sizeof(voc_adie_pwr_down_config)/sizeof(adie_codec_reg_type),
  0,
  voc_adie_pwr_down_config
};
#endif /*FEATURE_SBC_CODEC */

#ifdef FEATURE_INTERNAL_SADC
const
voc_adie_codec_config_type voc_adie_codec_mono_sadc_mono_handset_config =
{
  sizeof(voc_adie_mono_sadc_mono_handset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_MONO_SADC_MONO_HANDSET_DELAY_CONFIG_SIZE,
  voc_adie_mono_sadc_mono_handset_config
};

const
voc_adie_codec_config_type voc_adie_codec_mono_sadc_stereo_headset_config =
{
  sizeof(voc_adie_mono_sadc_stereo_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_MONO_SADC_STEREO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_mono_sadc_stereo_headset_config
};

const
voc_adie_codec_config_type voc_adie_codec_stereo_sadc_mono_handset_config =
{
  sizeof(voc_adie_stereo_sadc_mono_handset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_SADC_MONO_HANDSET_DELAY_CONFIG_SIZE,
  voc_adie_stereo_sadc_mono_handset_config
};

const
voc_adie_codec_config_type voc_adie_codec_stereo_sadc_stereo_headset_config =
{
 sizeof(voc_adie_stereo_sadc_stereo_headset_config)/sizeof(adie_codec_reg_type),
  MSMAUD_ADIE_CODEC_STEREO_SADC_STEREO_HEADSET_DELAY_CONFIG_SIZE,
  voc_adie_stereo_sadc_stereo_headset_config
};
#endif /* FEATURE_INTERNAL_SADC */
#endif /* MSMAUD_ADIE_CODEC */


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** Codec and ADIE configuration data, by image and path.
*/
enum {
  VOC_CAL_CODEC_CFG_VOC,
#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
  VOC_CAL_CODEC_CFG_VOC_ADEC_MIXER,
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */
#if defined(FEATURE_GSM) || defined(FEATURE_WCDMA)
  VOC_CAL_CODEC_CFG_GSM_VOC,
#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
  VOC_CAL_CODEC_CFG_GSM_VOC_ADEC_MIXER,
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */
#endif /* defined(FEATURE_GSM) || defined(FEATURE_WCDMA) */
#if defined(FEATURE_QSYNTH_COMMON) || defined(FEATURE_QTUNES_COMMON)
  VOC_CAL_CODEC_CFG_SYNTH,
#endif
#ifdef FEATURE_MM_REC
  VOC_CAL_CODEC_CFG_MMREC,
#endif /* FEATURE_MM_REC */
#ifdef FEATURE_AVS_I2SSBC
  VOC_CAL_CODEC_CFG_I2SSBC,
#endif /* FEATURE_AVS_I2SSBC */
  VOC_CAL_CODEC_CFG_MAX
} voc_cal_codec_cfg;

enum {
  VOC_CAL_PCM_PATH_CAL_CDMA,
#if defined(FEATURE_GSM) || defined(FEATURE_WCDMA)
  VOC_CAL_PCM_PATH_CAL_GSM,
#endif /* defined(FEATURE_GSM) || defined(FEATURE_WCDMA) */
  VOC_CAL_PCM_PATH_CAL_MAX
} voc_cal_pcm_path_cfg;

/* Audio path configuration - CODEC + ADIE config */
typedef struct {
  const qdsp_cmd_codec_config_type   *codec_config;
  const voc_adie_codec_config_type   *adie_config;
#ifdef MSMAUD_PMIC_CONFIG
  const voc_pmic_config_type         *pmic_config;
#endif
} voc_cal_audio_path_config_type;


#if defined (MSMAUD_ADIE_CODEC) && defined (MSMAUD_PMIC_CONFIG)
#define AUDIO_PATH_CONFIG(v,x,y) (v), (x), (y)
#elif defined (MSMAUD_ADIE_CODEC)
#define AUDIO_PATH_CONFIG(v,x,y) (v), (x)
#else
#define AUDIO_PATH_CONFIG(v,x,y) (v)
#endif

/* Audio path based on DSP image type and codec type */
const voc_cal_audio_path_config_type
      voc_cal_audio_path_config[VOC_CAL_CODEC_CFG_MAX][VOC_CODEC_MAX] =
{
  /*********************** Vocoder image ***********************/
  {
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_dual_mic,
                        &voc_adie_codec_handset_dual_mic_config,
                        &voc_cal_pmic_config_legacy_mic) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_aux,
                        &voc_adie_codec_aux_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL) }

    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_speaker,
                        &voc_adie_codec_speaker_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_SPEAKER_PHONE */

    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_intercom,
                        &voc_adie_codec_handset_no_micamp2_config,
                        &voc_cal_pmic_config_legacy_mic) }

    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }

    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_la,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
    /* VOC_CODEC_BT_SBC                */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }

    /* VOC_CODEC_BT_DUAL               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    #endif /* FEATURE_SBC_CODEC */
    #endif /* FEATURE_BT */

    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }


    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_SDAC                  */
    #ifdef FEATURE_INTERNAL_SDAC
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)   
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tx_external_sadc_rx_internal,
                        &voc_adie_codec_handset_no_mic_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #else 
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/ 

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE    
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_vco,
                        &voc_adie_codec_tty_vco_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_hco,
                        &voc_adie_codec_tty_hco_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic)}

    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
    
    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
    ,{ AUDIO_PATH_CONFIG( &voc_cal_codec_fm_bt_ag, 
                          &voc_adie_codec_fm_bt_ag_config, 
                          &voc_cal_pmic_config_legacy_mic) }
    #endif
    }

#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
  ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_dual_mic_mixer,
                        &voc_adie_codec_handset_dual_mic_config,
                        &voc_cal_pmic_config_legacy_mic) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
                      
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_aux,
                        &voc_adie_codec_aux_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL) }

    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_speaker,
                        &voc_adie_codec_speaker_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_SPEAKER_PHONE */


    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_intercom,
                        &voc_adie_codec_handset_no_micamp2_config,
                        &voc_cal_pmic_config_legacy_mic) }

    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_mixer, NULL, NULL) }
 
    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_la,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
    /* VOC_CODEC_BT_SBC */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }

    /* VOC_CODEC_BT_DUAL */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    #endif /* FEATURE_SBC_CODEC */

    #endif /* FEATURE_BT */


    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC) 
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tx_external_sadc_rx_internal,
                        &voc_adie_codec_handset_no_mic_config,
                        &voc_cal_pmic_config_legacy_nomic) } 
    #else
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/  

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_vco,
                        &voc_adie_codec_tty_vco_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_hco,
                        &voc_adie_codec_tty_hco_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }

    #ifdef FEATURE_INTERNAL_SDAC
   /* VOC_CODEC_STEREO_USB             */
  ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
    
   /* FM over BT AG */
   #ifdef FEATURE_BT_AG
  ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag, 
                       &voc_adie_codec_fm_bt_ag_config, 
                       &voc_cal_pmic_config_legacy_mic) }
   #endif    
  }
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */

#if defined(FEATURE_GSM) || defined(FEATURE_WCDMA)
  /******************* GSM Vocoder image ***********************/
 ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int0_dual_mic,
                        &voc_adie_codec_handset_dual_mic_config,
                        &voc_cal_pmic_config_legacy_mic) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif  /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_aux,
                        &voc_adie_codec_aux_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL) }

    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_speaker,
                        &voc_adie_codec_speaker_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_SPEAKER_PHONE */

    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_intercom,
                        &voc_adie_codec_handset_no_micamp2_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }

    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_la,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    /* VOC_CODEC_BT_DUAL */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    #endif /* FEATURE_SBC_CODEC */
    #endif /* FEATURE_BT */

    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }


    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)   
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tx_external_sadc_rx_internal,
                        &voc_adie_codec_handset_no_mic_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #else
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int0,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/ 
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_gsm_int1,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_vco,
                        &voc_adie_codec_tty_vco_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_hco,
                        &voc_adie_codec_tty_hco_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
   
    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag,
                        &voc_adie_codec_fm_bt_ag_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif
  }

#ifdef FEATURE_AVS_INCALL_MIXER_ADEC_PB
 ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_dual_mic_mixer,
                        &voc_adie_codec_handset_dual_mic_config,
                        &voc_cal_pmic_config_legacy_mic) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_aux,
                        &voc_adie_codec_aux_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL) }

    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_speaker_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_SPEAKER_PHONE */


    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_intercom,
                        &voc_adie_codec_handset_no_micamp2_config,
                        &voc_cal_pmic_config_legacy_mic) }

    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_mixer, NULL, NULL) }

    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag_la,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    /* VOC_CODEC_BT_DUAL */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    #endif /* FEATURE_SBC_CODEC */

    #endif /* FEATURE_BT */


    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }


    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #if defined(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC) 
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tx_external_sadc_rx_internal,
                        &voc_adie_codec_handset_no_mic_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #else 
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mixer,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /*(FEATURE_AVS_CRYSTAL_SPEECH) && defined(FEATURE_EXTERNAL_SADC)*/ 

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mixer,
                        &voc_adie_codec_mono_headset_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_vco,
                        &voc_adie_codec_tty_vco_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_tty_hco,
                        &voc_adie_codec_tty_hco_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
    
    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag, 
                        &voc_adie_codec_fm_bt_ag_config, 
                        &voc_cal_pmic_config_legacy_mic) }
    #endif
  }
#endif /* FEATURE_AVS_INCALL_MIXER_ADEC_PB */

#endif /* defined(FEATURE_GSM) || defined(FEATURE_WCDMA) */

  /*********************** SYNTH, TUNES, AAC ***********************/

#if defined(FEATURE_QSYNTH_COMMON) || defined(FEATURE_QTUNES_COMMON)
 ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #if defined(FEATURE_STEREO_HEADSET) && defined(FEATURE_INTERNAL_SDAC)
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config, 
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_STEREO_HEADSET && FEATURE_INTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_aux,
                        &voc_adie_codec_aux_no_mic_config, NULL) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL)}


    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_speaker,
                        &voc_adie_codec_speaker_no_mic_config, NULL) }
    #endif /* FEATURE_SPEAKER_PHONE */

    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    #ifdef FEATURE_BT_AG
    #ifdef FEATURE_AVS_AUDIO_DECODER_SCO
    /* VOC_CODEC_BT_MM_AG              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_mm_codec_bt_ag,NULL, NULL) }
    #else
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL) }
    #endif /*FEATURE_AVS_AUDIO_DECODER_SCO*/
    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_sbc,
                        &voc_adie_codec_pwr_down_config, NULL) }
                           /* VOC_CODEC_BT_A2DP_SCO */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_sbc,
                        &voc_adie_codec_pwr_down_config, NULL) }
    #endif /* FEATURE_SBC_CODEC */
    #endif /* FEATURE_BT */

    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic) }
    #else
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif  /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC*/
    
    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic) }
    #else
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_no_mic_config, NULL) }
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_stereo_usb,
                        &voc_adie_codec_stereo_usb_no_mic_config, NULL) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
    
    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag, 
                         &voc_adie_codec_fm_bt_ag_config, 
                         &voc_cal_pmic_config_legacy_mic) }
    #endif
  }
#endif /* FEATURE_QSYNTH_COMMON || FEATURE_QTUNES_COMMON */

#ifdef FEATURE_MM_REC /* VOC_CAL_CODEC_CFG_MMREC */
 ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mm_rec,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int0_mm_rec,
                        &voc_adie_codec_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #if defined(FEATURE_STEREO_HEADSET) && defined(FEATURE_INTERNAL_SDAC)
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac_mm_rec,
                        &voc_adie_codec_simul_stereo_headset_config, 
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac_mm_rec,
                        &voc_adie_codec_simul_stereo_headset_config, 
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_mono_headset_config, 
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_mono_headset_config, 
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_STEREO_HEADSET && FEATURE_INTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_capless_mic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_simul_stereo_headset_config,
                        &voc_cal_pmic_config_legacy_mic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_aux_mm_rec,
                        &voc_adie_codec_aux_no_mic_config, NULL) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board_mm_rec, NULL, NULL) }

    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_speaker_mm_rec,
                        &voc_adie_codec_speaker_config,
                        &voc_cal_pmic_config_legacy_mic) }
    #endif /* FEATURE_SPEAKER_PHONE */

    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0_mm_rec,
                        &voc_adie_codec_handset_no_mic_config, NULL) }

    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0_mm_rec,
                        &voc_adie_codec_handset_no_mic_config, NULL) }

    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0_mm_rec,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_sbc,
                        &voc_adie_codec_pwr_down_config, NULL) }
                           /* VOC_CODEC_BT_A2DP_SCO */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_sbc,
                        &voc_adie_codec_pwr_down_config, NULL) }
    #endif /* FEATURE_SBC_CODEC */
    #endif /* FEATURE_BT */

    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board_mm_rec, NULL, NULL) }

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    #ifdef FEATURE_INTERNAL_SADC
    /* VOC_CODEC_MONO_SADC_MONO_HANDSET */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                        &voc_adie_codec_mono_sadc_mono_handset_config,
                        &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_MONO_SADC_STEREO_HEADSET */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                       &voc_adie_codec_mono_sadc_stereo_headset_config,
                       &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                       &voc_adie_codec_mono_sadc_stereo_headset_config,
                       &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
   
    /* VOC_CODEC_STEREO_SADC_MONO_HANDSET */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_stereo_sadc_mono_handset_config,
                       &voc_cal_pmic_config_legacy_mic) }

    /* VOC_CODEC_STEREO_SADC_STEREO_HEADSET */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_stereo_sadc_stereo_headset_config,
                       &voc_cal_pmic_config_capless_mic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_stereo_sadc_stereo_headset_config,
                       &voc_cal_pmic_config_legacy_mic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
   
    #else
    /* VOC_CODEC_MONO_SADC_MONO_HANDSET */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
                       /* &voc_adie_codec_handset_config */

    /* VOC_CODEC_MONO_SADC_STEREO_HEADSET */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                       &voc_adie_codec_stereo_headphone_config, 
                       &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_mono_mm_rec,
                       &voc_adie_codec_stereo_headphone_config,
                       &voc_cal_pmic_config_legacy_nomic) }                       
    #endif   /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_STEREO_SADC_MONO_HANDSET */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_handset_no_mic_config, NULL) }
                       /* &voc_adie_codec_handset_config */
    
    /* VOC_CODEC_STEREO_SADC_STEREO_HEADSET */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_stereo_headphone_config, 
                       &voc_cal_pmic_config_capless_nomic) }                      
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sadc_stereo_mm_rec,
                       &voc_adie_codec_stereo_headphone_config,
                       &voc_cal_pmic_config_legacy_nomic) }                                             
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
   
    #endif /* FEATURE_INTERNAL_SADC */
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1_mm_rec,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL) }

    /* VOC_CODEC_TTY_VCO               */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1_mm_rec,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1_mm_rec,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    
    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0_mm_rec,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_no_mic_config, NULL) }
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_stereo_usb,
                        &voc_adie_codec_stereo_usb_no_mic_config, NULL) }
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */
    
    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag, 
                         &voc_adie_codec_fm_bt_ag_config, 
                         &voc_cal_pmic_config_legacy_mic) }
    #endif
  }
#endif /* FEATURE_MM_REC */

#ifdef FEATURE_AVS_I2SSBC
  /** Codec/Adie config values for I2SSBC **/
  ,{
    /* VOC_CODEC_ON_CHIP_0             */
    { AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}

#ifdef FEATURE_AVS_CRYSTAL_SPEECH
    /* VOC_CODEC_ON_CHIP_0_DUAL_MIC    */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL) }
#endif  /* FEATURE_AVS_CRYSTAL_SPEECH */

    /* VOC_CODEC_ON_CHIP_1             */
    #if defined(FEATURE_STEREO_HEADSET) && defined(FEATURE_INTERNAL_SDAC)
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #else
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #endif /* FEATURE_STEREO_HEADSET && FEATURE_INTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    /* VOC_CODEC_ON_CHIP_AUX           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_aux,
                        &voc_adie_codec_aux_no_mic_config, NULL) }

    /* VOC_CODEC_ON_BOARD              */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_on_board, NULL, NULL)}


    #ifdef FEATURE_SPEAKER_PHONE
    /* VOC_CODEC_SPEAKER_PHONE         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_speaker,
                        &voc_adie_codec_speaker_no_mic_config, NULL) }
    #endif /* FEATURE_SPEAKER_PHONE */


    #ifdef FEATURE_BT
    /* VOC_CODEC_BT_INTERCOM           */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}

    #ifdef FEATURE_BT_AG
    /* VOC_CODEC_BT_AG                 */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_bt_ag, NULL, NULL)}

    #ifdef FEATURE_BT_AG_LOCAL_AUDIO
    /* VOC_CODEC_BT_AG_LOCAL_AUDIO     */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}
    #endif /* FEATURE_BT_AG_LOCAL_AUDIO */
    #endif /* FEATURE_BT_AG */

    #if defined (FEATURE_SBC_CODEC) || defined (FEATURE_SBC_DSP_CODEC)
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_i2ssbc,
                        &voc_adie_codec_pwr_down_config, NULL)}
    /* VOC_CODEC_BT_A2DP_SCO */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_i2ssbc,
                        &voc_adie_codec_pwr_down_config, NULL)}
    #endif /* FEATURE_SBC_CODEC */

    #endif /* FEATURE_BT */

    /* VOC_CODEC_OFF_BOARD             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL)}


    #if defined(FEATURE_INTERNAL_SDAC) || defined(FEATURE_EXTERNAL_SDAC)
    /* VOC_CODEC_SDAC                  */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    #endif /* FEATURE_INTERNAL_SDAC || FEATURE_EXTERNAL_SDAC */

    #if defined(FEATURE_INTERNAL_SADC) || defined(FEATURE_EXTERNAL_SADC)
    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}

    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic) }
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic) }
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_ON_CHIP_0             */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}
    
    /* VOC_CODEC_STEREO_HEADSET        */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_sdac,
                        &voc_adie_codec_stereo_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */
    
    #endif /* FEATURE_INTERNAL_SADC || FEATURE_EXTERNAL_SADC */

    #ifdef FEATURE_TTY
    /* VOC_CODEC_TTY_ON_CHIP_1         */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headphone_config, 
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_int1,
                        &voc_adie_codec_mono_headphone_config, 
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_OFF_BOARD         */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_off_board, NULL, NULL)}

    /* VOC_CODEC_TTY_VCO               */
    #ifdef MSMAUD_GRND_REFERENCED_CAPLESS_MODE
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_capless_nomic)}
    #else
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int1,
                        &voc_adie_codec_mono_headphone_config,
                        &voc_cal_pmic_config_legacy_nomic)}
    #endif  /* MSMAUD_GRND_REFERENCED_CAPLESS_MODE */

    /* VOC_CODEC_TTY_HCO               */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_16k_int0,
                        &voc_adie_codec_handset_no_mic_config, NULL)}
    #endif /* FEATURE_TTY */

    #if defined(FEATURE_USB_CARKIT) || defined(FEATURE_HS_USB_ANALOG_AUDIO)
    /* VOC_CODEC_USB                   */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_usb,
                        &voc_adie_codec_usb_no_mic_config, NULL)}
    #ifdef FEATURE_INTERNAL_SDAC
    /* VOC_CODEC_STEREO_USB            */
   ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_stereo_usb,
                        &voc_adie_codec_stereo_usb_no_mic_config, NULL)}
    #endif /* FEATURE_INTERNAL_SDAC */
    #endif /* FEATURE_USB_CARKIT || FEATURE_HS_USB_ANALOG_AUDIO */

    /* FM over BT AG */
    #ifdef FEATURE_BT_AG
    ,{ AUDIO_PATH_CONFIG(&voc_cal_codec_fm_bt_ag, 
                         &voc_adie_codec_fm_bt_ag_config, 
                         &voc_cal_pmic_config_legacy_mic) }
    #endif
  }
#endif /* FEATURE_AVS_I2SSBC */
};


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
** PCM Path configuration data
*/

]]>
    <xsl:apply-templates select="CALIBRATION/DATAUNITS[@filename='voc_cal']"/>
    <xsl:apply-templates select="CALIBRATION/CAL_DB[@filename='voc_cal']"/>
<![CDATA[
/*===========================================================================

             D F M   D E F A U L T  C O N F I G U R A T I O N

===========================================================================*/

/* Default FM configuration mask
*/
#define VOC_DFM_AUDIO_DEF       ( QDSP_FM_RX_AUTO_MUTE_ENA_V | \
                                  QDSP_FM_TX_MUTE_ENA_V      | \
                                  QDSP_FM_COMP_ENA_V         | \
                                  QDSP_FM_PREEMP_ENA_V       | \
                                  QDSP_FM_LOOPBACK_DIS_V     | \
                                  QDSP_FM_DEEMP_ENA_V        | \
                                  QDSP_FM_EXPAND_ENA_V       | \
                                  QDSP_FM_SAT_TRANS_DIS_V    )

/* Default FM SAT Control Mask
*/
#define VOC_DFM_SAT_DEF         ( QDSP_FM_SAT_INT_ENA_V      | \
                                  QDSP_FM_SAT_ECC_6000_V     )

#define VOC_DFM_SAT_AGC_NOM         0x00e6
#define VOC_DFM_SAT_THRESH          0x0320
#define VOC_DFM_DEV_LIMIT_NOM       0x3180
#define VOC_DFM_DEV_LIMIT_DATA      0x3180
#define VOC_DFM_SAT_DC_OFFSET_NOM   0x0050


/* The default DFM configuration
*/
CAL_MEMORY qdsp_cmd_dfm_config_type voc_cal_dfm_config = {
  VOC_DFM_AUDIO_DEF,
  VOC_DFM_SAT_DEF,
  VOC_DFM_SAT_AGC_NOM,
  VOC_DFM_SAT_THRESH,
  VOC_DFM_DEV_LIMIT_NOM,
  VOC_DFM_SAT_DC_OFFSET_NOM
};


/* ===========================================================================
**
**                    A C C E S S   F U N C T I O N S
**
** =========================================================================*/
/*===========================================================================

FUNCTION voc_cal_get_codec_class

DESCRIPTION
  Returns the codec type given a codec id.

DEPENDENCIES
  None.

RETURN VALUE
  voc_codec_class_type   = The classification of codec referred to by the
                           function argument.

SIDE EFFECTS
  None.

===========================================================================*/
voc_codec_class_type voc_cal_get_codec_class (
  voc_codec_type     pcm_path
)
{
  if (pcm_path < VOC_CODEC_MAX)
  {
    return voc_cal_codec_class[pcm_path];
  }
  else
  {
    return VOC_CODEC_CLASS_NONE;
  }
}

#ifdef FEATURE_PHONE_VR
/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_codec_vr_type

DESCRIPTION
  Returns the codec vr type given a codec id.

DEPENDENCIES
  None.

RETURN VALUE
  voc_codec_vr_type   = The VR type of codec referred to by the function
                        argument.

SIDE EFFECTS
  None.

===========================================================================*/
voc_codec_vr_type voc_cal_get_codec_vr_type (
  voc_codec_type     pcm_path
)
{
  if (pcm_path < VOC_CODEC_MAX)
  {
    return voc_cal_codec_vr_types[pcm_path];
  }
  else
  {
    return VOC_CODEC_VR_TYPE_NONE;
  }
}
#endif /* FEATURE_PHONE_VR */

/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_pcm_cal

DESCRIPTION
  Returns a pointer the pcm calibration data.

DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  None.

===========================================================================*/
voc_cal_return_type voc_cal_get_pcm_cal (
  voc_codec_type        pcm_path,
  qdsp_image_type       image,
  voc_pcm_path_cal_type **pcm_cal_ptr
)
{
  voc_codec_mode_type mode;

  voc_data_get_codec_mode(image, &mode);
#if defined(FEATURE_GSM) || defined(FEATURE_WCDMA)
  if(mode == VOC_CODEC_MODE_GSM_VOICE) {
    *pcm_cal_ptr = (voc_pcm_path_cal_type *)
                       voc_pcm_cal_aptr[VOC_CAL_PCM_PATH_CAL_GSM][pcm_path];
  } else
#endif /* defined(FEATURE_GSM) || defined(FEATURE_WCDMA) */
  {
    *pcm_cal_ptr = (voc_pcm_path_cal_type *)
                      voc_pcm_cal_aptr[VOC_CAL_PCM_PATH_CAL_CDMA][pcm_path];
  }
  return (VOC_CAL_SUCCESS);
} /* voc_cal_get_pcm_cal */

/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_codec_config

DESCRIPTION
  Returns a pointer the codec configuration data.

DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  None.

===========================================================================*/
voc_cal_return_type voc_cal_get_codec_config (
 voc_codec_type        pcm_path,
 qdsp_image_type       image,
 qdsp_cmd_codec_config_type **codec_config_ptr
)
{
  voc_codec_mode_type mode;
  *codec_config_ptr = NULL;

  voc_data_get_codec_mode(image, &mode);
  *codec_config_ptr = (qdsp_cmd_codec_config_type *)
                         voc_cal_audio_path_config[mode][pcm_path].codec_config;
  return(VOC_CAL_SUCCESS);
} /* voc_cal_get_codec_config */

/* <EJECT> */
#ifdef MSMAUD_ADIE_CODEC
/*===========================================================================

FUNCTION voc_cal_get_adie_config

DESCRIPTION
  Gets the ADIE configuration data, based on the PCM path and the DSP image.

DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  None.

===========================================================================*/
voc_cal_return_type voc_cal_get_adie_config (
 voc_codec_type             pcm_path,
 qdsp_image_type            image,
 voc_adie_codec_config_type **adie_config_ptr
)
{
  voc_codec_mode_type mode;
  *adie_config_ptr = NULL;

  voc_data_get_codec_mode(image, &mode);
  *adie_config_ptr = (voc_adie_codec_config_type *)
                          voc_cal_audio_path_config[mode][pcm_path].adie_config;
  return(VOC_CAL_SUCCESS);
}
#endif /* MSMAUD_ADIE_CODEC */

#ifdef MSMAUD_PMIC_CONFIG
/*===========================================================================

FUNCTION voc_cal_get_pmic_config

DESCRIPTION
  Gets the PMIC configuration data, based on the PCM path and the DSP image.
  
DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  None.

===========================================================================*/
voc_cal_return_type voc_cal_get_pmic_config (
 voc_codec_type             pcm_path,
 qdsp_image_type            image,
 voc_pmic_config_type       **pmic_config_ptr
)
{
  voc_codec_mode_type mode;
  *pmic_config_ptr = NULL;

  voc_data_get_codec_mode(image, &mode);
  *pmic_config_ptr = (voc_pmic_config_type *)
                          voc_cal_audio_path_config[mode][pcm_path].pmic_config;
  return(VOC_CAL_SUCCESS);
}
#endif /* MSMAUD_PMIC_CONFIG */

#ifdef FEATURE_ACP
/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_dfm_config

DESCRIPTION
  Returns the default DFM configuration.

DEPENDENCIES
  None.

RETURN VALUE
  qdsp_cmd_dfm_config_type* - Pointer to the default DFM configuration.

SIDE EFFECTS
  None.

===========================================================================*/
qdsp_cmd_dfm_config_type* voc_cal_get_dfm_config
(
  void
)
{
  return( (qdsp_cmd_dfm_config_type*)&voc_cal_dfm_config );
} /* voc_cal_get_dfm_config */

/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_dfm_dev_limit

DESCRIPTION
  Returns the DFM deviation limit.  Value returned depends on the
  service option parameter.

DEPENDENCIES
  None.

RETURN VALUE
  uint16 - DFM deviation limit.

SIDE EFFECTS
  None.

===========================================================================*/
uint16 voc_cal_get_dfm_dev_limit
(
  voc_capability_type so
)
{
  uint16 dev_limit;

  if ( so == VOC_CAP_AMPS_DATA ) {
    dev_limit = VOC_DFM_DEV_LIMIT_DATA;
  } else {
    dev_limit = VOC_DFM_DEV_LIMIT_NOM;
  }

  return( dev_limit );
} /* voc_cal_get_dfm_dev_limit */
#endif /* FEATURE_ACP */

#ifdef FEATURE_VOC_MIC_GAIN_ADJUST
/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_get_mic_gain_adjust

DESCRIPTION
  Returns the stored mic gain adjustment value for the specified codec.

DEPENDENCIES
  voc_cal_mic_gain_adjust

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  None.

===========================================================================*/
voc_cal_return_type voc_cal_get_mic_gain_adjust
(
  voc_codec_type        pcm_path,
  sint15              **gain_cal_ptr
)
{
  if (pcm_path < (uint16) VOC_CODEC_MAX) {
    *gain_cal_ptr = &voc_cal_mic_gain_adjust[pcm_path];
    return (VOC_CAL_SUCCESS);
  } else {
    return (VOC_CAL_FAILURE);
  }
} /* voc_cal_get_mic_gain_adjust */

/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_set_mic_gain_adjust

DESCRIPTION
  Stores the specified mic gain adjustment dbm value for the specified codec.

DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - data retrieved successfully
  VOC_CAL_FAILURE - could not get data

SIDE EFFECTS
  voc_cal_mic_gain_adjust

===========================================================================*/
voc_cal_return_type voc_cal_set_mic_gain_adjust
(
  voc_codec_type        pcm_path,
  sint15                gain_cal
)
{
  if (pcm_path < (uint16) VOC_CODEC_MAX) {
    voc_cal_mic_gain_adjust[pcm_path] = gain_cal;
    return (VOC_CAL_SUCCESS);
  } else {
    return (VOC_CAL_FAILURE);
  }
} /* voc_cal_set_mic_gain_adjust */
#endif /* FEATURE_VOC_MIC_GAIN_ADJUST */

#ifdef FEATURE_VOC_NV_CAL
/* <EJECT> */
/*===========================================================================

LOCAL FUNCTION voc_cal_get_nv

DESCRIPTION
  Retrieves data stored in specified NV item.

DEPENDENCIES
  None.

RETURN VALUE
  VOC_CAL_SUCCESS - NV read operation was successful.
  VOC_CAL_FAILED  - NV read operation failed.

SIDE EFFECTS
  VOC task is blocked until NV operation completes.

===========================================================================*/
static voc_cal_return_type voc_cal_get_nv
(
  nv_items_enum_type item,        /* which item                */
  nv_item_type *data_ptr          /* pointer to space for item */
)
{
  static nv_cmd_type nvi;            /* nv command buffer                  */

  nvi.tcb_ptr    = &voc_tcb;         /* notify this task when done         */
  nvi.sigs       = VOC_NV_SIG;
  nvi.done_q_ptr = NULL;             /* command goes on no queue when done */

  nvi.item       = item;             /* item to read                       */
  nvi.cmd        = NV_READ_F;

  /* Set up NV so that it will read the data into the correct location */
  nvi.data_ptr   = data_ptr;


  /* Clear the return signal, call NV, and wait for a response */
  (void) rex_clr_sigs( &voc_tcb, VOC_NV_SIG );
  nv_cmd( &nvi );
  voc_nv_wait();

  if( nvi.status != NV_DONE_S ) {
    return VOC_CAL_FAILURE;
  }

  return VOC_CAL_SUCCESS;
}

/* <EJECT> */
/*===========================================================================

FUNCTION voc_cal_read_nv_cal

DESCRIPTION
  Reads NV related to voc calibration.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  voc_data_mic_gain_adjust

===========================================================================*/
void voc_cal_read_nv_cal (void)
{

#ifdef FEATURE_VOC_MIC_GAIN_ADJUST
  static nv_item_type data;

  /* NV_VOC_HS_MIC_GAIN_ADJUST_I */
  if (voc_cal_get_nv(NV_VOC_HS_MIC_GAIN_ADJUST_I,&data) == VOC_CAL_SUCCESS) {
    voc_cal_mic_gain_adjust[VOC_CODEC_ON_CHIP_0] =
      data.voc_hs_mic_gain_adjust;

#ifdef FEATURE_SPEAKER_PHONE
    voc_cal_mic_gain_adjust[VOC_CODEC_SPEAKER] =
      data.voc_hs_mic_gain_adjust;
#endif /* FEATURE_SPEAKER_PHONE */
  }
#endif /* FEATURE_VOC_MIC_GAIN_ADJUST */

}
#endif /* FEATURE_VOC_NV_CAL */


/* End of voccal.c */
]]>
  </xsl:template>

  <!-- CAL_DB Template -->
  <xsl:template match="CALIBRATION/CAL_DB[@filename='voc_cal']">
    <xsl:text>&#xa;</xsl:text>
    <xsl:value-of select="@typequalifier"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@datatype"/>
    <xsl:if test="@vartype = string('PTR')">
      <xsl:text>* </xsl:text>
    </xsl:if>
    <xsl:text>&#xa;&#x9;</xsl:text>
    <xsl:value-of select="@name"/>
    <!--DB is always 2D ARRAY-->
    <xsl:for-each select="INDICES/INDEX">
      <xsl:text>[</xsl:text>
      <xsl:value-of select="@value"/>
      <xsl:text>] </xsl:text>
    </xsl:for-each>
    <xsl:text>= { &#xa;</xsl:text>
    <xsl:call-template name="process_data"/>
    <xsl:text> &#xa;};&#xa;</xsl:text>
  </xsl:template>

  <!-- DATAUNITS Template -->
  <xsl:template match="CALIBRATION/DATAUNITS[@filename='voc_cal']">
    <xsl:call-template name="process_data"/>
  </xsl:template>
  
  <xsl:include href="src_tmpl.xslt"/>
 
</xsl:stylesheet>
