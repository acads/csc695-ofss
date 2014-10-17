/*
 * CSC 695 - Thesis Research, Fall 2014
 *
 * This module implemeents OpenFlow Flexible Payload Match (FPM) experimenter
 * message routines.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifdef OFP_FPM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openflow/openflow.h"
#include "ofl-exp-fpm.h"
#include "../oflib/ofl-log.h"
#include "../oflib/ofl-print.h"

#define LOG_MODULE ofl_exp_fpm
OFL_LOG_INIT(LOG_MODULE)


int                 
ofl_exp_fpm_msg_pack(struct ofl_msg_experimenter *msg, uint8_t **buf,
                size_t *buf_len)
{
    struct ofl_exp_fpm_msg_header *exp = (struct ofl_exp_fpm_msg_header *) msg;
    
    if ((!msg) || (!buf) || (!buf_len)) {
        fpm_assert(0);
        goto error_exit;
    }

    switch (exp->type) {
        case OFP_EXP_FPM_ADD:
            break;

        case OFP_EXP_FPM_DEL:
            break;

        case OFP_EXP_FPM_MOD:
            break;

        case OFP_EXP_FPM_STAT:
            break;

        case OFP_EXP_FPM_DESC:
            break;

        default:
            fpm_assert(0);
    }

    return 0;

error_exit:
    return -1;
}    


ofl_err 
ofl_exp_fpm_msg_unpack(struct ofp_header *oh, size_t *len,
                struct ofl_msg_experimenter **msg)
{
    return 0;
}


int
ofl_exp_fpm_msg_free(struct ofl_msg_experimenter *msg)
{
    return 0;
}


char *
ofl_exp_fpm_msg_to_string(struct ofl_msg_experimenter *msg)
{
    return 0;
}

#endif /* OFP_FPM */

