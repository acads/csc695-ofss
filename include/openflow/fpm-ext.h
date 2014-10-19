/*
 * CSC 695 - Thesis Research, Fall 2014
 *
 * This module contains the required constants, data structures and function
 * declarations for OpenFlow Flexible Payload Match (FPM) experimenter.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifndef FPM_EXT_H
#define FPM_EXT_H 

#include <assert.h>

#include "openflow/openflow.h"

/* Constants */
#define OFP_EXP_FPM_ID  0x00ABCDEF  /* FPM experimenter ID          */
#define FPM_MAX_LEN     32          /* FPM length of data to match  */
#define FPM_MIN_ID      0
#define FPM_MAX_ID      127
#ifndef TRUE
#define TRUE            1
#endif /* TRUE */
#ifndef FALSE
#define FALSE           0
#endif /* FALSE */

/* Util macros */
#define IS_FPM_EXPT(ID)         (OFP_EXP_FPM_ID == ID)
#define fpm_assert(val)         assert(val)

/* Supported FPM commands */
enum ofp_fmp_cmds {
    OFP_FPM_ADD,    /* add a new FPM            */
    OFP_FPM_DEL,    /* delete an existing FPM   */
    OFP_FPM_MOD,    /* modify an existing FPM   */
    OFP_FPM_STAT,   /* stats of an existing FPM */
    OFP_FPM_DESC    /* FPM experimenter desc    */
};

/* FPM header */
struct of_fpm_header {
    struct ofp_header   of_header;
    uint32_t            vendor;
    uint32_t            subtype;
};
OFP_ASSERT(sizeof(struct of_fpm_header) % 4 == 0);

/* FPM table entry */
struct of_fpm_entry {
    uint8_t     id;                     /* FPM ID           */
    uint32_t    offset;                 /* start offset     */
    uint32_t    len;                    /* bytes to match   */
    char        match[FPM_MAX_LEN + 1]; /* what to match?   */
};

/* FPM msg */
struct of_fpm_msg {
    struct of_fpm_header    fpm_header; /* OF + EXP header  */
    struct of_fpm_entry     fpm_entry;  /* actual FPM entry */
    uint8_t                 pad[7];     /* 64-bit boundary  */
};
OFP_ASSERT(sizeof(struct ofl_exp_msg) % 4 == 0);

/* FPM table */
struct of_fpm_table {
    struct of_fpm_msg  *fpm_entries[FPM_MAX_ID + 1];
    uint32_t           fpm_nref[FPM_MAX_ID + 1];
    uint8_t            nfpm;
};
#endif /* FPM_EXT_H */

