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

/* Function declarations */
ofl_err
dp_fpm_handle_add(struct datapath *dp, struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED);
ofl_err
dp_fpm_handle_del(struct datapath *dp UNUSED, struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED);
#endif /* OFP_FPM */

#endif /* DP_FPM_H */

