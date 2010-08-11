#ifndef PRLDIAG_H
#define PRLDIAG_H

/*==========================================================================
          Diagnostic System Packet Definitions for PRL

  Description: Packet definitions to support the interface between the
  DMSS software and the external device for Preffered Roaming list-related 
  packets.

Copyright (c) 2003-2006 by QUALCOMM, Incorporated.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                            Edit History

  $Header: //depot/asic/msmshared/services/diag/prldiag.h#4 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/03/08   vg     Updated code to use PACK() vs. PACKED
12/14/06   as     Fixed critical lint errors.
05/04/05   as     Featurized nv_stat_enum_type to ensure uint16 for external api.
11/20/03   as     Created file.

===========================================================================*/
#include "customer.h"
#include "comdef.h"

#include "nv.h" 

#ifdef FEATURE_PREFERRED_ROAMING

/*===========================================================================

PACKET   DIAG_PR_LIST_WR_F

PURPOSE  Sent by external device to write a Preferred Roaming List to
         the phone.

RESPONSE The diag_pr_list_wr_rsp_type will be sent in response.

===========================================================================*/
#define DIAG_PR_LIST_BLOCK_SIZE 120   /* Size in bytes of the PR_LIST block */
typedef PACK(struct)
{
  byte cmd_code;                      /* Command code */
  byte seq_num;                       /* Sequence number */
  byte more;                          /* More to come? */
  byte nam;                           /* which NAM this is associated with */
  word num_bits;                      /* length in bits of valid data */
  byte pr_list_data[DIAG_PR_LIST_BLOCK_SIZE];  /* The block of PR_LIST */
} diag_pr_list_wr_req_type;

#define DIAG_RL_WR_OK          0    /* No errors */
#define DIAG_RL_WR_OK_DONE     1    /* No errors, PR_LIST is complete */
#define DIAG_RL_WR_OUT_OF_SEQ  2    /* Sequence number out of order */
#define DIAG_RL_WR_OVERFLOW    3    /* PR_LIST overflow */

typedef PACK(struct)
{
  byte cmd_code;                    /* Command code */
  byte rl_status;                   /* Status of block, as above */
#ifdef FEATURE_NV_ENUMS_ARE_WORDS
#error code not present
#else
  uint16 nv_stat;                   /* nv_stat should always be 
                                       uint16 (as per ICD)*/
#endif
} diag_pr_list_wr_rsp_type;


/*===========================================================================

PACKET   DIAG_PR_LIST_RD_F

PURPOSE  Sent by external device to read a Preferred Roaming List from
         the phone.

RESPONSE The diag_pr_list_rd_rsp_type will be sent in response.

===========================================================================*/
typedef PACK(struct)
{
  byte cmd_code;                      /* Command code */
  byte seq_num;                       /* Sequence number */
  byte nam;                           /* PR_LIST for this NAM */
} diag_pr_list_rd_req_type;

#define DIAG_RL_RD_OK         0     /* No error, using non-standard PRL */
#define DIAG_RL_RD_NV_ERR     1     /* NV error */
#define DIAG_RL_RD_683A_OK    2     /* No error, using IS683A PRL */
#define DIAG_RL_RD_NV_683A_ERR   3  /* NV error, using IS683A PRL */

typedef PACK(struct)
{
  byte cmd_code;                               /* Command code */
  byte rl_status;                              /* Status of block, as above */
#ifdef FEATURE_NV_ENUMS_ARE_WORDS
#error code not present
#else
  uint16 nv_stat;                              /* nv_stat should always be 
                                                  uint16 (as per ICD)*/
#endif
  byte seq_num;                                /* Sequence number */
  byte more;                                   /* More to come? */
  word num_bits;                               /* Number of valid data bits */
  byte pr_list_data[DIAG_PR_LIST_BLOCK_SIZE];  /* The block of PR_LIST */
} diag_pr_list_rd_rsp_type;

#endif /* FEATURE_PREFERRED_ROAMING */

#endif /* PRLDIAG_H  */

