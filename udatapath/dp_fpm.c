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
#include "oflib/oxm-match.h"
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

inline bool
fpm_is_id_valid(uint8_t id)
{
    return ((id >= FPM_MIN_ID) && (id <= FPM_MAX_ID) ? TRUE : FALSE);
}

static inline bool
fpm_is_id_present(uint8_t id)
{
    return ((g_fpm_table.entries[id]) ? TRUE : FALSE);
}

inline bool
fpm_is_max_match_configured(struct of_fpm_table_entry *tbl_entry)
{
    return ((tbl_entry->nfpm < FPM_MAX_MATCH) ? FALSE : TRUE);
}

inline struct of_fpm_table_entry *
fpm_get_table_entry(uint8_t id)
{
    if (fpm_is_id_present(id))
        return g_fpm_table.entries[id];
    else
        return NULL;
}

static inline struct of_fpm_table_entry *
fpm_get_entry(uint8_t id)
{
    return ((fpm_is_id_present(id)) ? (g_fpm_table.entries[id]) : NULL);
}

static inline uint8_t
fpm_get_id_ref_count(uint8_t id)
{
    return (fpm_is_id_present(id) ? (g_fpm_table.entries[id]->nref) : 0);
}

inline void
fpm_increment_id_ref_count(uint8_t id)
{
    g_fpm_table.nref[id] += 1;
    return;
}

inline void
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

uint8_t
fpm_get_fpm_id_from_fmod(struct ofl_msg_flow_mod *mod)
{
    uint8_t                 fpm_id = FPM_ALL_ID;
    uint32_t                md_header = OXM_OF_METADATA;
    struct ofl_match_tlv    *tlv = NULL;

    tlv = oxm_match_lookup(md_header, (struct ofl_match *) (mod->match));
    if (!tlv) {
        return FPM_ALL_ID;
    }

    fpm_id = *((uint8_t *) tlv->value);
    return fpm_id;
}

uint8_t
fpm_get_fpm_id_from_pkt(struct packet *pkt)
{
    uint8_t                 fpm_id = FPM_ALL_ID;
    uint32_t                md_header = OXM_OF_METADATA;
    struct ofl_match_tlv    *tlv = NULL;

    tlv = oxm_match_lookup(md_header, &(pkt->handle_std->match));
    if (!tlv) {
        return FPM_ALL_ID;
    }

    fpm_id = *((uint8_t *) tlv->value);
    return fpm_id;
}

inline bool
fpm_is_fpm_table(uint8_t table_id)
{
    return ((FPM_TABLE_ID == table_id) ? TRUE : FALSE);
}


uint8_t *
fpm_get_l7_data(struct packet *pkt)
{
    uint8_t             *l7 = NULL;
    uint8_t             *tmp = NULL;
    uint8_t             ip_proto = 0;
    uint16_t            eth_type = 0;
    struct eth_header   *eth_hdr = NULL;
    struct ip_header    *ip_hdr = NULL;
    struct ipv6_header  *ip6_hdr = NULL;
    struct icmp_header  *icmp_hdr = NULL;
    struct tcp_header   *tcp_hdr = NULL;
    struct udp_header   *udp_hdr = NULL;

    tmp = pkt->buffer->data;
    if (!tmp)
        goto error_exit;

    eth_hdr = (struct eth_header *) tmp;
    if (!eth_hdr) {
        VLOG_WARN(LOG_MODULE, "Unable to fetch Ethernet header.");
        goto error_exit;
    }

    tmp += sizeof(*eth_hdr);
    eth_type = ntohs(eth_hdr->eth_type);
    if (ETH_TYPE_IP == eth_type) {
        ip_hdr = (struct ip_header *) tmp;
        tmp += sizeof(*ip_hdr);
        ip_proto = ip_hdr->ip_proto;
    } else if (ETH_TYPE_IPV6 == eth_type) {
        ip6_hdr = (struct ipv6_header *) tmp;
        tmp += sizeof(*ip6_hdr);
        ip_proto = ip6_hdr->ipv6_next_hd;
    } else {
        /* Only IP traffic is supported for FPM for now. */
        VLOG_WARN(LOG_MODULE, "FPM only supports IP and IPv6 traffic.");
        goto error_exit;
    }

    VLOG_INFO(LOG_MODULE, "eth_type: 0x%04x", eth_type);
    VLOG_INFO(LOG_MODULE, "ip_porto: %02u", ip_proto);

    switch (ip_proto)  {
        case IP_TYPE_ICMP:
            icmp_hdr = (struct icmp_header *) tmp;
            tmp += sizeof(*icmp_hdr);
            VLOG_INFO(LOG_MODULE, "icmp_type: %02u", icmp_hdr->icmp_type);
            VLOG_INFO(LOG_MODULE, "icmp_code: %02u", icmp_hdr->icmp_code);
            break;

        case IP_TYPE_TCP:
            tcp_hdr = (struct tcp_header *) tmp;
            tmp += (TCP_OFFSET(tcp_hdr->tcp_ctl) * 4);
            VLOG_INFO(LOG_MODULE, "tcp_sport: %05u", ntohs(tcp_hdr->tcp_src));
            VLOG_INFO(LOG_MODULE, "tcp_dport: %05u", ntohs(tcp_hdr->tcp_dst));
            break;

        case IP_TYPE_UDP:
            udp_hdr = (struct udp_header *) tmp;
            tmp += sizeof(*udp_hdr);
            VLOG_INFO(LOG_MODULE, "udp_sport: %05u", ntohs(udp_hdr->udp_src));
            VLOG_INFO(LOG_MODULE, "udp_dport: %05u", ntohs(udp_hdr->udp_dst));
            break;

        default:
            VLOG_WARN(LOG_MODULE, "FPM only supports ICMP, TCP and UDP traffic.");
    }

    l7 = tmp;
    return l7;

error_exit:
    return NULL;
}

bool
fpm_do_lookup(uint8_t fpm_id, uint8_t *data)
{
    char                        haystack[FPM_MAX_LEN + 1] = "";
    struct fpm                  *fpm_data = NULL;
    struct of_fpm_table_entry   *e = NULL;

    e = fpm_get_table_entry(fpm_id);
    if (!e)
        return FALSE;

    fpm_data = e->fpm_data;
    while (fpm_data) {
        memcpy(haystack, data + fpm_data->offset, fpm_data->depth);
        if (strstr(haystack, fpm_data->match))
            return TRUE;
        fpm_data = fpm_data->next;
    }

    return FALSE;
}

ofl_err
dp_fpm_handle_add(struct datapath *dp UNUSED,
        struct ofl_exp_fpm_msg *exp_msg,
        const struct sender *sender UNUSED)
{
    bool                        fpm_id_avail = FALSE;
    ofl_err                     err_code = 0;
    struct of_fpm_entry         *in_entry = NULL;
    struct of_fpm_table_entry   *loc_entry = NULL;
    struct fpm                  *loc_data = NULL;

    in_entry = (struct of_fpm_entry *) exp_msg->fpm_entry;
    VLOG_INFO(LOG_MODULE, "Received fpm-add for id %u.", in_entry->id);
    
    if (in_entry->len > FPM_MAX_LEN) {
        VLOG_ERR(LOG_MODULE, "Bad length %u for FPM id %u",
                in_entry->len, in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_BAD_PARAMS);
        goto error_exit;
    }

    if (in_entry->offset + in_entry->depth < in_entry->len) {
        VLOG_ERR(LOG_MODULE, "Len %u greater than offset + depth (%u + %u) for FPM id %u.",
                in_entry->len, in_entry->offset, in_entry->depth, in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_BAD_PARAMS);
        goto error_exit;
    }

    loc_entry = fpm_get_table_entry(in_entry->id);
    fpm_id_avail = loc_entry ? TRUE : FALSE;

    /* Error out if the incoming ID has max matches. */
    if (loc_entry && fpm_is_max_match_configured(loc_entry)) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has max. # of matches already.",
                in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_MAX_MATCH);
        goto error_exit;
    }

    if (!fpm_id_avail) {
        /* ID is being configured for the first time. */
        loc_entry = (struct of_fpm_table_entry *) 
            calloc(1, sizeof(*loc_entry));
        loc_entry->id = in_entry->id;
    }

    loc_data = (struct fpm *) calloc(1, sizeof(*loc_entry->fpm_data));
    loc_data->offset = in_entry->offset;
    loc_data->depth = in_entry->depth;
    loc_data->len = in_entry->len;
    memcpy(loc_data->match, in_entry->match, in_entry->len);

    /* 
     * Place the new match at the entry's head and update the
     * global FPM table if the entry is being added for the 1st time.
     */
    loc_entry->nfpm += 1;
    if (fpm_id_avail) {
        loc_data->next = loc_entry->fpm_data;
        loc_entry->fpm_data = loc_data;
        VLOG_INFO(LOG_MODULE, "New match configured for fpm id %u, nfpm %u; " \
                "offset %u, depth %u, len %u, match %s",
                loc_entry->id, loc_entry->nfpm, 
                loc_data->offset, loc_data->depth, 
                loc_data->len, loc_data->match);
    } else {
        loc_data->next = NULL;
        loc_entry->fpm_data = loc_data;
        
        g_fpm_table.entries[loc_entry->id] = loc_entry;
        fpm_increment_count();
        
        VLOG_INFO(LOG_MODULE, "New fpm id %u, nfpm %u; " \
                "offset %u, depth %u, len %u, match %s",
                loc_entry->id, loc_entry->nfpm, 
                loc_data->offset, loc_data->depth, 
                loc_data->len, loc_data->match);
    }

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
    ofl_err                     err_code = 0;
    uint32_t                    tmp_count = 0;
    struct of_fpm_entry         *in_entry = NULL;
    struct of_fpm_table_entry   *loc_entry = NULL;
    struct fpm                  *tmp_fpm_data = NULL;

    in_entry = (struct of_fpm_entry *) exp_msg->fpm_entry;
    VLOG_INFO(LOG_MODULE, "Received fpm-del for id %u.", in_entry->id);

    if (!fpm_is_id_present(in_entry->id)) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has not been configured.",
                in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_NOT_FOUND);
        goto error_exit;
    }

    if ((tmp_count = fpm_get_id_ref_count(in_entry->id)) > 0) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has %u flows associated with it.",
                in_entry->id, tmp_count);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_ACTIVE);
        goto error_exit;
    }

    loc_entry = fpm_get_table_entry(in_entry->id);

    /* First delete all configured matches for the given id. */
    while (loc_entry->fpm_data && loc_entry->nfpm) {
        tmp_fpm_data = loc_entry->fpm_data;
        loc_entry->fpm_data = tmp_fpm_data->next;
        loc_entry->nfpm -= 1;
        VLOG_INFO(LOG_MODULE, "fpm id %u, match %s deleted, nfpm %u",
                loc_entry->id, tmp_fpm_data->match, loc_entry->nfpm);
        free(tmp_fpm_data);
    }

    /* Delete the main entry now. */
    free(loc_entry);
    fpm_decrement_count();
    g_fpm_table.entries[in_entry->id] = NULL;

    VLOG_INFO(LOG_MODULE, "FPM id %u has been deleted.", in_entry->id);

    return err_code;

error_exit:
    return err_code;
}

ofl_err
dp_fpm_handle_stats(struct datapath *dp,
        struct ofl_msg_multipart_request_fpm *msg,
        const struct sender *sender)
{
    return 0;
}

ofl_err
dp_fpm_handle_logs(struct datapath *dp UNUSED,
        struct ofl_exp_fpm_msg *exp_msg UNUSED,
        const struct sender *sender UNUSED)
{
    ofl_err                     err_code = 0;
    uint8_t                     id = 0;
    uint32_t                    nentries = 0;
    struct fpm                  *loc_data = NULL;
    struct of_fpm_table_entry   *loc_entry = NULL;

    VLOG_INFO(LOG_MODULE, "Received fp-logs.");

    nentries = fpm_get_count();
    if (!nentries) {
        VLOG_INFO(LOG_MODULE, "No FPMs has been configured.");
        return err_code;
    }

    for (id = 0; (id <= FPM_MAX_ID); ++id) {
        if (!fpm_is_id_present(id))
            continue;

        loc_entry = fpm_get_table_entry(id);
        VLOG_INFO(LOG_MODULE,
            "fpm-stats: id %u, nfpm %u, nref %u, nref %u",
            loc_entry->id, loc_entry->nfpm, loc_entry->nref);
        loc_data = loc_entry->fpm_data;
        while (loc_data) {
            VLOG_INFO(LOG_MODULE, 
                "   offset %u, depth %u, len %u, match \"%s\"",
                loc_data->offset, loc_data->depth, 
                loc_data->len, loc_data->match);
            loc_data = loc_data->next;
        }
    }

    return err_code;
}

#if 0
ofl_err
dp_fpm_handle_stats(struct datapath *dp,
        struct ofl_msg_multipart_request_fpm *msg,
        const struct sender *sender)
{
    uint8_t                             id = 0;
    ofl_err                             err_code = 0;
    struct of_fpm_entry                 *loc_entry = NULL;
    struct of_fpm_stats_entry           *stats_entry = NULL;
    struct ofl_msg_multipart_reply_fpm  reply = {
        {{.type = OFPT_MULTIPART_REPLY},
        .type = OFPMP_FPM, .flags = 0x0000},
        .stats_num = 0,
        .stats = NULL
    };

    id = msg->id;
    if (FPM_ALL_ID == id) {
        VLOG_INFO(LOG_MODULE,
                "FPM stats request received for sent for all available IDs.");
        reply.stats_num = fpm_get_count();
        reply.stats = xmalloc(reply.stats_num * sizeof(*stats_entry));
        stats_entry = (struct of_fpm_stats_entry *) reply.stats;

        for (id = 0; (id <= FPM_MAX_ID) && (fpm_is_id_present(id)); ++id) {
            loc_entry = (struct of_fpm_entry *) g_fpm_table.entries[id];

            stats_entry->id = loc_entry->id;
            stats_entry->offset = loc_entry->offset;
            stats_entry->len = loc_entry->len;
            memcpy(stats_entry->match, loc_entry->match, FPM_MAX_LEN);
            stats_entry->nref = fpm_get_id_ref_count(id);

            stats_entry += 1;
        }
        VLOG_INFO(LOG_MODULE, "FPM stats sent for all available IDs.");
    } else {
        VLOG_INFO(LOG_MODULE, "FPM stats request received for id %u.", id);
        if (!fpm_is_id_present(id)) {
            VLOG_ERR(LOG_MODULE, "FPM id %u has not been configured.", id);
            err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_EXISTS);
            goto error_exit;
        }

        reply.stats_num = 1;
        reply.stats = xmalloc(sizeof(*stats_entry) * 1);
        loc_entry = (struct of_fpm_entry *) g_fpm_table.entries[id];

        stats_entry = (struct of_fpm_stats_entry *) reply.stats[0];
        stats_entry->id = loc_entry->id;
        stats_entry->offset = loc_entry->offset;
        stats_entry->len = loc_entry->len;
        strncpy(stats_entry->match, loc_entry->match, strlen(loc_entry->match));
        stats_entry->nref = fpm_get_id_ref_count(id);

        VLOG_INFO(LOG_MODULE, "FPM stats sent for id %u.", id);
    }


    dp_send_message(dp, (struct ofl_msg_header *) &reply, sender);

    free(reply.stats);
    ofl_msg_free((struct ofl_msg_header *) msg, dp->exp);

    return err_code;

error_exit:
    return err_code;
}

ofl_err
dp_fpm_handle_stat(uint8_t id, struct ofp_fpm_stats_entry *stats_entry)
{
    ofl_err err_code = 0;

    if (!fpm_is_id_present(in_entry->id)) {
        VLOG_ERR(LOG_MODULE, "FPM id %u has not been configured.",
                in_entry->id);
        err_code = ofl_error(OFPET_EXPERIMENTER, OFFFPMC_ID_EXISTS);
        goto error_exit;
    }

    loc_entry = (struct of_fpm_entry *) g_fpm_table.entries[id];;
    stats_entry->id = loc_entry->id;
    stats_entry->offset = htonl(loc_entry->offset);
    stats_entry->len = htonl(loc_entry->len);
    memcpy(stats_entry->match, loc_entry->match, FPM_MAX_LEN);
    stats_entry->nref = htonl(fpm_get_id_ref_count(id));

    return err_code;

error_exit:
    return err_code;
}
#endif

#endif /* OFP_FPM */

