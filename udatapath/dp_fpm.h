/*
 * CSC 695 - Thesis Research, Fall 2014
 * 
 * This module implements OpenFlow Flexible Payload Match (FPM) experimenter's
 * function declarations.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifndef DP_FPM_H
#define DP_FPM_H

#ifdef OFP_FPM

#include "dp_exp.h"
#include "oflib/ofl.h"
#include "oflib/ofl-structs.h"
#include "oflib/ofl-messages.h"
#include "oflib-exp/ofl-exp-fpm.h"

/* Function declarations */
uint8_t
fpm_get_fpm_id_from_pkt(struct packet *pkt);
inline bool
fpm_is_fpm_table(uint8_t table_id);
uint8_t *
fpm_get_l7_data(struct packet *pkt);

ofl_err
dp_fpm_handle_add(struct datapath *dp, struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED);
ofl_err
dp_fpm_handle_del(struct datapath *dp UNUSED, struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED);
ofl_err
dp_fpm_handle_logs(struct datapath *dp UNUSED, struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED);
ofl_err
dp_fpm_handle_stats(struct datapath *dp,
        struct ofl_msg_multipart_request_fpm *_msg,
        const struct sender *sender);
#endif /* OFP_FPM */

#endif /* DP_FPM_H */

