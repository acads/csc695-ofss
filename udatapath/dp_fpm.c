/*
 * CSC 695 - Thesis Research, Fall 2014
 * 
 * This module implements OpenFlow Flexible Payload Match (FPM) experimenter.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifdef OFP_FPM

#include "dp_exp.h"
#include "packets.h"
#include "pipeline.h"
#include "oflib/ofl.h"
#include "oflib/ofl-messages.h"
#include "oflib/ofl-log.h"
#include "util.h"
#include "vlog.h"

#include "oflib-exp/ofl-exp-fpm.h"
#include "openflow/fpm-ext.h"
#include "dp_fpm.h"

#define LOG_MODULE VLM_dp_fpm

/* FPM table */
struct of_fpm_table g_fpm_table;

static void
fpm_init(void)
{
    uint16_t    i = 0;

    for (i = 0; i < FPM_MAX_ID + 1; ++i)
        g_fpm_table.entries[i] = NULL;
    memset(&g_fpm_table.nref, 0, sizeof(g_fpm_table.nref));
    g_fpm_table.count = 0;

    return;
}

static inline bool
fpm_is_id_present(uint8_t id)
{
    return ((g_fpm_table.entries[id]) ? TRUE : FALSE);
}

static inline bool
fpm_get_id_ref_count(uint8_t id)
{
    return (g_fpm_table.nref[id]);
}

static inline void
fpm_increment_id_ref_count(uint8_t id)
{
    g_fpm_table.nref[id] += 1;
    return;
}

static inline void
fpm_decrement_id_ref_count(uint8_t id)
{
    if (g_fpm_table.nref[id])
        g_fpm_table.nref[id] -= 1;
    return;
}

static inline uint32_t
fpm_get_count(void)
{
    return g_fpm_table.count;
}

static inline void
fpm_increment_count(void)
{
    g_fpm_table.count += 1;
}

static inline void
fpm_decrement_count(void)
{
    if (g_fpm_table.count)
        g_fpm_table.count -= 1;
}

ofl_err
dp_fpm_handle_add(struct datapath *dp UNUSED,
        struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED)
{
    ofl_err             err_code = 0;
    struct of_fpm_entry *entry = NULL;
    struct of_fpm_entry *in_entry = NULL;
    struct of_fpm_entry *loc_entry = NULL;

    in_entry = (struct of_fpm_entry *) exp_msg->fpm_entry;
    VLOG_INFO(LOG_MODULE, "Received fpm-add for id %u.", in_entry->id);

    /* Error out if the incoming ID has been configured already. */
    if (fpm_is_id_present(in_entry->id)) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has been confiured already.",
                in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_EXISTS);
        goto error_exit;
    }

    loc_entry = (struct of_fpm_entry *) calloc(1, sizeof(*loc_entry));
    memcpy(loc_entry, in_entry, sizeof(*loc_entry));

    g_fpm_table.entries[loc_entry->id] = loc_entry;
    fpm_increment_count();

    entry = (struct of_fpm_entry *) g_fpm_table.entries[loc_entry->id];
    VLOG_INFO(LOG_MODULE, "Configured FPM id %u, offset %u, len %u, match %s",
            entry->id, entry->offset, entry->len, entry->match);

    return err_code;

error_exit:
    if (loc_entry)
        free(loc_entry);

    return err_code;
}

ofl_err
dp_fpm_handle_del(struct datapath *dp UNUSED,
        struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED)
{
    ofl_err             err_code = 0;
    uint32_t            tmp_count = 0;
    struct of_fpm_entry *in_entry = NULL;
    struct of_fpm_entry *loc_entry = NULL;

    in_entry = (struct of_fpm_entry *) exp_msg->fpm_entry;
    VLOG_INFO(LOG_MODULE, "Received fpm-del for id %u.", in_entry->id);

    if (!fpm_is_id_present(in_entry->id)) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has not been configured.",
                in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_EXISTS);
        goto error_exit;
    }

    if ((tmp_count = fpm_get_id_ref_count(in_entry->id)) > 0) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has %u flows associated with it.",
                in_entry->id, tmp_count);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_ACTIVE);
        goto error_exit;
    }

    loc_entry = (struct of_fpm_entry *) g_fpm_table.entries[in_entry->id];
    free(loc_entry);
    fpm_decrement_count();
    g_fpm_table.entries[in_entry->id] = NULL;

    VLOG_INFO(LOG_MODULE, "FPM id %u has been deleted.", in_entry->id);

    return err_code;

error_exit:
    return err_code;
}

#endif /* OFP_FPM */

