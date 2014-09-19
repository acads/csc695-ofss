/*
 * CSC 695 - Thesis Research, Fall 2014
 *
 * This module implemeents OpenFlow Flexible Payload Match (FPM) experimenter
 * message routines.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ofl-exp-fpm.h"
#include "../oflib/ofl-print.h"
#include "../oflib/ofl-log.h"

#define LOG_MODULE ofl_exp_fpm
OFL_LOG_INIT(LOG_MODULE)


int                 
ofl_exp_fpm_msg_pack(struct ofl_experimenter *msg, uint8_t **buf,
                size_t *buf_len)
{
    if ((!msg) || (!buf) || (!buf_len)) {
        OFL_LOG_WARN(LOG_MODULE, "Null pointers in %s.", __func__);
        fpm_assert(0);
        goto error_exit;
    }

    if (OFP_EXP_FPM_ID == msg->experimenter_id) {
        struct ofl_exp_fmp_header *fpm_msg = NULL;

        fpm_msg = (struct ofl_exp_fmp_header *) msg;
        switch (fpm_msg->type) {
            case OFP_EXP_FPM_CMD_ADD:
                break;

            case OFP_EXP_FPM_CMD_DEL:
                break;

            case OFP_EXP_FPM_CMD_MOD:
                break;

            case OFP_EXP_FPM_CMD_STAT:
                break;

            case OFP_EXP_FPM_CMD_DESC:
                break;

            default:
                OF_LOG_WARN("Unknown message type, %d, received by FPM.\n",
                        fpm_msg->type);
                fpm_assert(0);

        }

    } else {
        OF_LOG_WARN("Unknown experimenter handled to FPM.");
        fpm_assert(0);
        goto error_exit;
    }

error_exit:
}    


ofl_err 
ofl_exp_fpm_msg_unpack(struct ofp_header *oh, size_t *len,
                struct ofl_experimenter **msg)
{
}


int
ofl_exp_fpm_msg_free(struct ofl_msg_experimenter *msg)
{
}


char *
ofl_exp_fpm_msg_to_string(struct ofl_msg_experimenter *msg)
{
}
