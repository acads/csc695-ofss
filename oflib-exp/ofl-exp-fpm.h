/*
 * CSC 695 - Thesis Research, Fall 2014
 *
 * This module contains the required constants, data structures and function
 * declarations for OpenFlow Flexible Payload Match (FPM) experimenter pack and
 * unpack routines.
 *
 * Author: Aravindhan Dhanasekaran <adhanas@ncsu.edu>
 */

#ifdef OFP_FPM

#ifndef OFL_EXP_FPM_H
#define OFL_EXP_FPM_H 

#include "../oflib/ofl-structs.h"
#include "../oflib/ofl-messages.h"
#include "../include/openflow/fpm-ext.h"

struct ofl_exp_fpm_msg_header {
    struct ofl_msg_experimenter header;
    uint32_t                    type;
};

struct ofl_exp_fpm_msg {
    struct ofl_exp_fpm_msg_header   header;
    struct of_fpm_entry             *fpm_entry;
};

struct ofl_exp_fpm_stats_request {
    struct ofl_exp_fpm_msg_header   fpm_exp_header;
    uint8_t                         id;
};

struct ofl_exp_fpm_stats_reply {
    struct ofl_exp_fpm_msg_header   fpm_header;
    uint32_t                        fpm_num_entries;
    struct of_fpm_entry             *fpm_entries;
};

/* Function declarations */
inline bool
fpm_is_id_valid(uint8_t id);
int
ofl_exp_fpm_msg_pack(struct ofl_msg_experimenter *msg, uint8_t **buf, 
                size_t *buf_len);
ofl_err
ofl_exp_fpm_msg_unpack(struct ofp_header *oh, size_t *len, 
                struct ofl_msg_experimenter **msg);
int
ofl_exp_fpm_msg_free(struct ofl_msg_experimenter *msg);
char *
ofl_exp_fpm_msg_to_string(struct ofl_msg_experimenter *msg);

#endif /* OFL_EXP_FPM_H */

#endif /* OFP_FPM */

