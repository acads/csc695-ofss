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
#include "../oflib/ofl-log.h"
#include "../oflib/ofl-print.h"
#include "ofl-exp-fpm.h"
#include "openflow/fpm-ext.h"

#define LOG_MODULE ofl_exp_fpm
OFL_LOG_INIT(LOG_MODULE)

int                 
ofl_exp_fpm_msg_pack(struct ofl_msg_experimenter *msg, uint8_t **buf,
                size_t *buf_len)
{
    struct ofl_exp_fpm_msg          *exp_msg = NULL;
    struct ofl_exp_fpm_msg_header   *exp_hdr = NULL;
    
    if (!IS_FPM_EXPT(msg->experimenter_id)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to pack a different experimenter with FPM handler.\n");
        goto error_exit;
    }

    exp_hdr = (struct ofl_exp_fpm_msg_header *) msg;
    switch (exp_hdr->type) {
        case OFP_FPM_ADD: {
            struct of_fpm_msg   *loc_msg = NULL;
            struct of_fpm_entry *loc_entry = NULL;

            exp_msg = (struct ofl_exp_fpm_msg *) exp_hdr;
            *buf_len = sizeof(*loc_msg);
            *buf = (uint8_t *) calloc(1, *buf_len);

            loc_msg = (struct of_fpm_msg *) (*buf);
            loc_msg->fpm_header.vendor =
                htonl(exp_hdr->header.experimenter_id);
            loc_msg->fpm_header.subtype = htonl(exp_hdr->type);

            loc_entry = (struct of_fpm_entry *) &loc_msg->fpm_entry;
            loc_entry->id = exp_msg->fpm_entry->id;
            loc_entry->offset = htonl(exp_msg->fpm_entry->offset);
            loc_entry->depth = htonl(exp_msg->fpm_entry->depth);
            loc_entry->len = htonl(exp_msg->fpm_entry->len);
            memcpy(loc_entry->match, exp_msg->fpm_entry->match,
                    FPM_MAX_LEN + 1);
            loc_entry->and_match = exp_msg->fpm_entry->and_match;

            break;
        }

        case OFP_FPM_DEL: {
            struct of_fpm_msg   *loc_msg = NULL;
            struct of_fpm_entry *loc_entry = NULL;

            exp_msg = (struct ofl_exp_fpm_msg *) exp_hdr;
            *buf_len = sizeof(*loc_msg);
            *buf = (uint8_t *) calloc(1, *buf_len);

            loc_msg = (struct of_fpm_msg *) (*buf);
            loc_msg->fpm_header.vendor =
                htonl(exp_hdr->header.experimenter_id);
            loc_msg->fpm_header.subtype = htonl(exp_hdr->type);

            loc_entry = (struct of_fpm_entry *) &loc_msg->fpm_entry;
            loc_entry->id = exp_msg->fpm_entry->id;
            break;
        }

        case OFP_FPM_LOGS: {
            struct of_fpm_msg *loc_msg = NULL;

            exp_msg = (struct ofl_exp_fpm_ms *) exp_hdr;
            *buf_len = sizeof(*loc_msg);
            *buf = (uint8_t *) calloc(1, *buf_len);

            loc_msg = (struct of_fpm_msg *) (*buf);
            loc_msg->fpm_header.vendor =
                htonl(exp_hdr->header.experimenter_id);
            loc_msg->fpm_header.subtype = htonl(exp_hdr->type);
            break;
        }

        case OFP_FPM_STAT:
        case OFP_FPM_MOD:
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
    ofl_err                 err_code = 0;
    struct of_fpm_msg       *in_msg = NULL;
    struct of_fpm_header    *in_hdr = NULL;

    if (*len < sizeof(*in_hdr)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Received EXPERIMENTER message has invalid length, %zu.", *len);
        err_code = ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
        goto error_exit;
    }

    in_hdr = (struct of_fpm_header *) oh;
    if (!IS_FPM_EXPT(ntohl(in_hdr->vendor))) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to unpack a different experimenter with FPM handler.");
        err_code = ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_EXPERIMENTER);
        goto error_exit;
    }

    switch (ntohl(in_hdr->subtype)) {
        case OFP_FPM_ADD: {
            struct ofl_exp_fpm_msg  *exp_msg = NULL;
            struct of_fpm_entry     *exp_entry = NULL;

            if (*len < sizeof(*in_msg)) {
                OFL_LOG_WARN(LOG_MODULE,
                    "Received OFP_FPM_ADD message has invalid length %zu, expected at least %zu.",
                    *len, sizeof(*in_msg));
                err_code = ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
                goto error_exit;
            }
            *len -= sizeof(*in_msg);

            in_msg = (struct of_fpm_msg *) in_hdr;
            exp_msg = (struct ofl_exp_fpm_msg *) calloc(1, sizeof(*exp_msg));
            exp_entry = (struct of_fpm_entry *) calloc(1, sizeof(*exp_entry));

            exp_msg->header.header.experimenter_id =
                ntohl(in_msg->fpm_header.vendor);
            exp_msg->header.type = ntohl(in_msg->fpm_header.subtype);

            exp_msg->fpm_entry = exp_entry;
            exp_entry->id = in_msg->fpm_entry.id;
            exp_entry->offset = ntohl(in_msg->fpm_entry.offset);
            exp_entry->depth = ntohl(in_msg->fpm_entry.depth);
            exp_entry->len = ntohl(in_msg->fpm_entry.len);
            memcpy(exp_entry->match, in_msg->fpm_entry.match,
                    FPM_MAX_LEN + 1);
            exp_entry->and_match = in_msg->fpm_entry.and_match;

            *msg = (struct ofl_msg_experimenter *) exp_msg;
            return 0;
        }

        case OFP_FPM_DEL: {
            struct ofl_exp_fpm_msg  *exp_msg = NULL;
            struct of_fpm_entry     *exp_entry = NULL;

            if (*len < sizeof(*in_msg)) {
                OFL_LOG_WARN(LOG_MODULE,
                    "Received OFP_FPM_DEL message has invalid length, %zu.",
                    *len);
                err_code = ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
                goto error_exit;
            }
            *len -= sizeof(*in_msg);

            in_msg = (struct of_fpm_msg *) in_hdr;
            exp_msg = (struct ofl_exp_fpm_msg *) calloc(1, sizeof(*exp_msg));
            exp_entry = (struct of_fpm_entry *) calloc(1, sizeof(*exp_entry));

            exp_msg->header.header.experimenter_id =
                ntohl(in_msg->fpm_header.vendor);
            exp_msg->header.type = ntohl(in_msg->fpm_header.subtype);

            exp_msg->fpm_entry = exp_entry;
            exp_entry->id = in_msg->fpm_entry.id;

            *msg = (struct ofl_msg_experimenter *) exp_msg;
            return 0;
        }

        case OFP_FPM_LOGS: {
            struct ofl_exp_fpm_msg  *exp_msg = NULL;

            if (*len < sizeof(*in_msg)) {
                OFL_LOG_WARN(LOG_MODULE,
                    "Received OFP_FPM_LOGS message has invalid length %zu, expected at least %zu.",
                    *len, sizeof(*in_msg));
                err_code = ofl_error(OFPET_BAD_REQUEST, OFPBRC_BAD_LEN);
                goto error_exit;
            }
            *len -= sizeof(*in_msg);

            in_msg = (struct of_fpm_msg *) in_hdr;
            exp_msg = (struct ofl_exp_fpm_msg *) calloc(1, sizeof(*exp_msg));

            exp_msg->header.header.experimenter_id =
                ntohl(in_msg->fpm_header.vendor);
            exp_msg->header.type = ntohl(in_msg->fpm_header.subtype);
            exp_msg->fpm_entry = NULL;

            *msg = (struct ofl_msg_experimenter *) exp_msg;
            return 0;
        }

        case OFP_FPM_STAT:
        case OFP_FPM_MOD:
        case OFP_FPM_DESC:
            break;

        default:
            fpm_assert(0);
    }

    return 0;

error_exit:
    return err_code;
}


int
ofl_exp_fpm_msg_free(struct ofl_msg_experimenter *msg)
{
    struct ofl_exp_fpm_msg          *exp_msg = NULL;
    struct ofl_exp_fpm_msg_header   *exp_hdr = NULL;

    if (!IS_FPM_EXPT(msg->experimenter_id)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to pack a different experimenter with FPM handler.\n");
        goto error_exit;
    }

    exp_hdr = (struct ofl_exp_fpm_msg_header *) msg;
    switch (exp_hdr->type) {
        case OFP_FPM_ADD:
        case OFP_FPM_DEL:
            exp_msg = (struct ofl_exp_fpm_msg *) exp_hdr;
            free(exp_msg->fpm_entry);
            break;

        case OFP_FPM_LOGS:
        case OFP_FPM_STAT:
        case OFP_FPM_MOD:
        case OFP_FPM_DESC:
            break;

        default:
            OFL_LOG_WARN(LOG_MODULE,
                "Trying to free a unknown subtype with FPM handler.\n");
            break;
    }

    free(msg);
    return 0;

error_exit:
    free(msg);
    return -1;
}


char *
ofl_exp_fpm_msg_to_string(struct ofl_msg_experimenter *msg)
{
    char                            *str = NULL;
    size_t                          str_size;
    FILE                            *stream = NULL;
    uint8_t                         id = 0;
    struct of_fpm_entry             *entry = NULL;
    struct ofl_exp_fpm_msg          *exp_msg = NULL;
    struct ofl_exp_fpm_msg_header   *exp_hdr = NULL;

    if (!IS_FPM_EXPT(msg->experimenter_id)) {
        OFL_LOG_WARN(LOG_MODULE,
                "Trying to pack a different experimenter with FPM handler.\n");
        goto error_exit;
    }

    stream = open_memstream(&str, &str_size);
    exp_hdr = (struct ofl_exp_fpm_msg_header *) msg;
    exp_msg = (struct ofl_exp_fpm_msg *) msg;
    entry = (struct of_fpm_entry *) exp_msg->fpm_entry;

    switch (exp_hdr->type) {
        case OFP_FPM_ADD:
            fprintf(stream,
                    "-fpm-add {id=%u, offset=%u, depth=%u, len=%u, match=%s}",
                    entry->id, entry->offset, entry->depth, entry->len,
                    entry->match);
            break;

        case OFP_FPM_DEL:
            fprintf(stream, "-fpm-del {id=%u}", entry->id);
            break;

        case OFP_FPM_LOGS:
            fprintf(stream, "-fpm-logs");
            break;

        case OFP_FPM_STAT: {
            uint8_t                             id = 0;
            struct ofl_exp_fpm_stats_request    *exp_req = NULL;

            exp_req = (struct ofl_exp_fpm_stats_request *) msg;
            id = exp_req->id;
            if (FPM_ALL_ID == id)
                fprintf(stream, "-fpm-stat");
            else
                fprintf(stream, "-fpm-stat {id=%u}", id);
            break;
        }

        case OFP_FPM_MOD:
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

