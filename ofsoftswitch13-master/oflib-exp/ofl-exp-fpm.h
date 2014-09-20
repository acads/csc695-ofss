/*
 * CSC 695 - Thesis Research, Fall 2014
 *
 * This module contains the required constants, data structures and function
 * declarations for OpenFlow Flexible Payload Match (FPM) experimenter.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifndef OFL_EXP_FPM_H
#define OFL_EXP_FPM_H

#include "../oflib/ofl-structs.h"
#include "../oflib/ofl-messages.h"

/* Constants */
#define OFP_EXP_FPM_ID      0x00ABCDEF  /* FPM experimenter ID  */
#define FPM_DESC_STR_LEN    255


/* Util macros */
#define fpm_assert(val) assert(val)


/* FPM msg header */
struct fpm_header {
    struct ofp_header   header;     /* Standard OF msg header   */
    uint32_t            vendor;     /* Experimenter ID          */
    uint32_t            subtype;    /* Experimenter msg type    */
};
OFP_ASSERT(sizeof(struuct fmp_header) == 16);


/* FPM msg statistics */
struct fpm_stats {
    uint16_t    num_flows;      /* # of FPM flows   */
    uint64_t    num_pkts;       /* total # of pkts  */
    uint64_t    num_bytes;      /* total # of bytes */
};


struct fpm_match {
    uint16_t    start;
    uint16_t    len;
    uchar       value[FPM_MATCH_LEN];
};


/* FPM msg payload - based on the msg type */
union fpm_msg_data {
    char                desc[FPM_DESC_STR_LEN];
    struct fpm_match    match;
    struct fpm_stats    stats;
};


/* FPM msg header and type */
struct fpm_msg {
    struct fpm_header   fpm_hdr;
    uint32_t            fpm_type;
    union   fpm_data    fpm_data;
};


/* Supported FPM commands */
enum ofp_exp_fmp_cmds {
    OFP_EXP_FPM_CMD_ADD,    /* add a new FPM            */
    OFP_EXP_FPM_CMD_DEL,    /* delete an existing FPM   */
    OFP_EXP_FPM_CMD_MOD,    /* modify an existing FPM   */
    OFP_EXP_FPM_CMD_STAT,   /* stats of an existing FPM */
    OFP_EXP_FPM_CMD_DESC    /* FPM experimenter desc    */
};


/* Function declarations */
int
ofl_exp_fpm_msg_pack(struct ofl_experimenter *msg, uint8_t **buf, 
        size_t *buf_len);

ofl_err
ofl_exp_fpm_msg_unpack(struct ofp_header *oh, size_t *len, 
        struct ofl_experimenter **msg);

int
ofl_exp_fpm_msg_free(struct ofl_msg_experimenter *msg);

char *
ofl_exp_fpm_msg_to_string(struct ofl_msg_experimenter *msg);

#endif /* OFL_EXP_FPM_H */
