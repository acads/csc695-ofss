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

inline bool
fpm_is_id_valid(uint8_t id)
{
    return ((id >= FPM_MIN_ID) && (id <=FPM_MAX_ID));
}

int                 
ofl_exp_fpm_msg_pack(struct ofl_msg_experimenter *msg, uint8_t **buf,
                size_t *buf_len)
{
    struct ofl_exp_fpm_msg          *fpm_msg = NULL;
    struct ofl_exp_fpm_msg_header   *exp = NULL;
    
    if (!IS_FPM_EXPT(msg->experimenter_id)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to pack a different experimenter with FPM handler.\n");
        goto error_exit;
    }

    exp = (struct ofl_exp_fpm_msg_header *) msg;
    switch (exp->type) {
        case OFP_FPM_ADD: {
            break;
        }

        case OFP_FPM_DEL:
            break;

        case OFP_FPM_MOD:
            break;

        case OFP_FPM_STAT:
            break;

        case OFP_FPM_DESC:
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
    char *str;
    size_t  str_size;
    FILE *stream;
    struct ofl_exp_fpm_msg_header *exp = NULL;

    if (!IS_FPM_EXPT(msg->experimenter_id)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to pack a different experimenter with FPM handler.\n");
        goto error_exit;
    }

    stream = open_memstream(&str, &str_size);
    exp = (struct ofl_exp_fpm_msg_header *) msg;

    switch (exp->type) {
        case OFP_FPM_ADD: {
            struct ofl_exp_fpm_msg *fpm_msg = (struct ofl_exp_fmp_msg *) msg;
            struct of_fpm_entry *entry =
                (struct of_fpm_entry *) fpm_msg->fpm_entry;
            fprintf(stream, "-fpm-mod {id=%u, offset=%u, len=%u, match=%s}",
                    entry->id, entry->offset, entry->len, entry->match);
            break;
        }

        case OFP_FPM_DEL:
            break;

        case OFP_FPM_MOD:
            break;

        case OFP_FPM_STAT:
            break;

        case OFP_FPM_DESC:
            break;

        default:
            fpm_assert(0);
    }

    fclose(stream);
    return str;

error_exit:
    fclose(stream);
    free(str);
    return NULL;;
}

#endif /* OFP_FPM */

