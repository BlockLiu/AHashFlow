/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.

 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of
 * Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Barefoot Networks,
 * Inc.
 * and its suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material is
 * strictly forbidden unless prior written permission is obtained from
 * Barefoot Networks, Inc.
 *
 * No warranty, explicit or implicit is provided, unless granted under a
 * written agreement with Barefoot Networks, Inc.
 *
 * $Id: $
 *
 ******************************************************************************/
#ifdef __TARGET_TOFINO__

/* Tofino */
#ifndef USER_FEATURE_OVERRIDE
#ifndef DC_BASIC_PROFILE
#define DC_BASIC_PROFILE
#endif
#else
#include "p4userfeatures.h"
#endif

#else

/* Standard Model */
#define EGRESS_FILTER
#define FABRIC_ENABLE
#define EGRESS_ACL_ENABLE
#define SFLOW_ENABLE
#define WCMP_ENABLE
#define FLOWLET_ENABLE
#define ILA_ENABLE
#define RACL_STATS_ENABLE

#define invalidate(x) modify_field(x, 0)

#endif

// Profiles control, default is DC_BASIC_PROFILE
//#define DC_BASIC_PROFILE
//#define ENT_DC_GENERAL_PROFILE
//#define ENT_FIN_POSTCARD_PROFILE
//#define MSDC_PROFILE

// Individual features control
//#define ACL_DISABLE
//#define INGRESS_ACL_RANGE_DISABLE
//#define EGRESS_ACL_RANGE_DISABLE
//#define BFD_OFFLOAD_ENABLE
//#define EGRESS_FILTER
//#define FAST_FAILOVER_ENABLE
//#define FLOWLET_ENABLE
//#define ILA_ENABLE
//#define INT_ENABLE
//#define INT_EP_ENABLE
//#define INT_DIGEST_ENABLE
//#define INT_OVER_L4_ENABLE
//#define INT_L4_CHECKSUM_UPDATE_ENABLE
//#define INT_TRANSIT_ENABLE
#define IPSG_DISABLE
//#define IPV4_DISABLE
//#define IPV6_DISABLE
//#define L2_DISABLE
//#define L2_MULTICAST_DISABLE
#define TUNNEL_MULTICAST_DISABLE
//#define L3_DISABLE
//#define L3_MULTICAST_DISABLE
//#define MIRROR_DISABLE
//#define DTEL_DROP_REPORT_ENABLE
#define MPLS_DISABLE
//#define MPLS_UDP_ENABLE
//#define MULTICAST_DISABLE
#define NAT_DISABLE
#define NVGRE_DISABLE
#define GENEVE_DISABLE
//#define PKTGEN_ENABLE
#define QOS_CLASSIFICATION_ENABLE
//#define SS_QOS_CLASSIFICATION_ENABLE
//#define ACL_QOS_ENABLE
//#define QOS_METERING_ENABLE
#define DOUBLE_TAGGED_DISABLE
#define RACL_DISABLE
//#define RACL_STATS_ENABLE
//#define EGRESS_ACL_STATS_ENABLE
//#define EGRESS_OUTER_BD_STATS_ENABLE
//#define MIRROR_ACL_STATS_ENABLE
//#define RESILIENT_HASH_ENABLE
//#define SFLOW_ENABLE
//#define SR_ENABLE
//#define STATS_DISABLE
//#define STORM_CONTROL_DISABLE
//#define STP_DISABLE
//#define TUNNEL_DISABLE
//#define IPV4_TUNNEL_DISABLE
//#define IPV6_TUNNEL_DISABLE
#define URPF_DISABLE
//#define WCMP_ENABLE
//#define MIRROR_ACL_ENABLE
//#define DTEL_FLOW_STATE_TRACK_ENABLE
//#define DTEL_QUEUE_REPORT_ENABLE
//#define DTEL_REPORT_LB_ENABLE
//#define DTEL_REPORT_ENABLE
//#define DTEL_WATCH_INNER_ENABLE
//#define INGRESS_MAC_ACL_DISABLE
//#define EGRESS_MAC_ACL_DISABLE
#define TUNNEL_NEXTHOP_ENABLE /* When multicast is disabled but PRE engine is still needed for tunneling */
//#define INGRESS_UC_SELF_FWD_CHECK_DISABLE
//#define TUNNEL_INDEX_BRIDGE_ENABLE
//#define TUNNEL_V4_VXLAN_ONLY
//#define TUNNEL_PARSING_DISABLE
#define MIRROR_NEXTHOP_DISABLE
//#define INGRESS_PORT_IN_EGRESS_SYSTEM_ACL_ENABLE
//#define HASH_32BIT_ENABLE
//#define ROCEV2_MIRROR_ENABLE
#define INGRESS_PORT_MIRROR_ENABLE
//#define EGRESS_PORT_MIRROR_ENABLE
#define INGRESS_ACL_ACTION_MIRROR_ENABLE
//#define EGRESS_ACL_MIRROR_ENABLE
#define RACL_REASON_CODE_DISABLE
#define OUTER_MULTICAST_BRIDGE_DISABLE
//#define MLAG_ENABLE
#define STP_TCAM_DISABLE
#define FIB_ALPM
#define EGRESS_QUEUE_STATS_ENABLE
#define INGRESS_PPG_STATS_ENABLE
//#define QOS_ACL_ENABLE
#define GLOBAL_TC_ICOS_QUEUE_TABLE
//#define CPU_TX_YID_REWRITE_ENABLE
//#define DSCP_IN_IP_ACL_KEY_ENABLE

#if defined(ENT_DC_GENERAL_PROFILE)

//#define IPV6_TUNNEL_DISABLE
//#define EGRESS_ACL_ENABLE
#define EGRESS_ACL_RANGE_DISABLE
#define EGRESS_MAC_ACL_DISABLE
#define L3_MULTICAST_DISABLE

#define REWRITE_SWAP
#define ACL_SWAP
#define PTP_ENABLE
#define ENT_DC_GENERAL_TABLE_SIZES

#elif defined(ENT_FIN_POSTCARD_PROFILE)

#define DTEL_REPORT_LB_ENABLE
#define DTEL_QUEUE_REPORT_ENABLE
#define DTEL_DROP_REPORT_ENABLE
#define IPV6_DISABLE
#define TUNNEL_DISABLE
#define DTEL_FIN_TABLE_SIZES
#define ENT_DC_GENERAL_TABLE_SIZES
#define REWRITE_SWAP
#define MIRROR_SWAP
#define MLAG_ENABLE

#define POSTCARD_ENABLE
#define DTEL_FLOW_STATE_TRACK_ENABLE

#elif defined(L3_HEAVY_INT_LEAF_PROFILE) || defined(GENERIC_INT_LEAF_PROFILE)
#define TUNNEL_DISABLE
#define IPV6_DISABLE
#define RACL_DISABLE // ipv4_acl table is used to provide racl functionality
#define ACL_SWAP // required for using ipv4_acl to provide racl functionality
#define MIRROR_ACL_ENABLE
#define MIRROR_ACL_STATS_ENABLE
#define EGRESS_PORT_MIRROR_ENABLE
#define QOS_MARKING_ENABLE
#define WRED_ENABLE
#define WRED_DROP_ENABLE
#define PTP_ENABLE
#define MIRROR_SWAP
#define LEARN_INVALIDATE_ENABLE
#define IPV4_4_TUPLE_IN_SYSTEM_ACL_KEY_ENABLE
//DTEL features
#define DTEL_REPORT_LB_ENABLE
#define DTEL_QUEUE_REPORT_ENABLE
#define DTEL_DROP_REPORT_ENABLE
#define INT_ENABLE
#define INT_EP_ENABLE
#define INT_DIGEST_ENABLE
#define INT_OVER_L4_ENABLE
//#define INT_L4_CHECKSUM_UPDATE_ENABLE
#define DTEL_FLOW_STATE_TRACK_ENABLE
#define ETHERNET_ZERO_MAC_CHECK_DISABLE

#if defined(L3_HEAVY_INT_LEAF_PROFILE)
#define L2_MULTICAST_DISABLE
#define L3_MULTICAST_DISABLE
#define STORM_CONTROL_DISABLE
#define L3_HEAVY_INT_LEAF_TABLE_SIZES

#elif defined(GENERIC_INT_LEAF_PROFILE)
#define QOS_ACL_ENABLE
#define QOS_METERING_ENABLE
#define MLAG_ENABLE
#define QINQ_ENABLE
#define TUNNEL_PARSING_DISABLE
#define CPU_TX_YID_REWRITE_ENABLE
#define GENERIC_INT_LEAF_TABLE_SIZES
#endif /* L3_HEAVY_INT_LEAF_PROFILE */

// start of all MSDC profiles
#elif defined(MSDC_PROFILE) || defined(MSDC_IPV4_PROFILE) || defined(MSDC_L3_PROFILE) \
    || defined(MSDC_LEAF_DTEL_INT_PROFILE) || defined(MSDC_SPINE_DTEL_INT_PROFILE)

// common features for all MSDC profiles
#define L2_MULTICAST_DISABLE
#define L3_MULTICAST_DISABLE
#define WRED_ENABLE
#define WRED_DROP_ENABLE
#define MIRROR_ACL_ENABLE
#define MIRROR_ACL_STATS_ENABLE
#define ACL_SWAP
#define REWRITE_SWAP
#define STP_DISABLE

#if defined(MSDC_PROFILE) \
    || defined(MSDC_LEAF_DTEL_INT_PROFILE) || defined(MSDC_SPINE_DTEL_INT_PROFILE)
// common features for MSDC and MSDC DTel profiles
#define ETYPE_IN_IP_ACL_KEY_ENABLE
#define INGRESS_PORT_IN_EGRESS_SYSTEM_ACL_ENABLE
#define ROCEV2_MIRROR_ENABLE
#define TUNNEL_DISABLE
#define EGRESS_ACL_ENABLE
#define EGRESS_MAC_ACL_DISABLE
#define TRANSIENT_LOOP_PREVENTION
#define DSCP_IN_EGRESS_ACL_KEY_ENABLE
#define DSCP_IN_IP_ACL_KEY_ENABLE
#define MSDC_TABLE_SIZES
#endif

// unique features for each MSDC profile or profile group
#if defined(MSDC_PROFILE)

#elif defined(MSDC_LEAF_DTEL_INT_PROFILE) || defined(MSDC_SPINE_DTEL_INT_PROFILE)
// start of MSDC DTel profiles
#define DTEL_REPORT_LB_ENABLE
#define DTEL_DROP_REPORT_ENABLE
#define DTEL_QUEUE_REPORT_ENABLE

#define STORM_CONTROL_DISABLE

#if defined(MSDC_LEAF_DTEL_INT_PROFILE)
#define INT_ENABLE
#define INT_EP_ENABLE
#define INT_DIGEST_ENABLE
#define INT_OVER_L4_ENABLE
#define DTEL_FLOW_STATE_TRACK_ENABLE
#define IPV6_DISABLE
#define MIRROR_SWAP

#elif defined(MSDC_SPINE_DTEL_INT_PROFILE)
#define INT_ENABLE
#define INT_TRANSIT_ENABLE
#define INT_OVER_L4_ENABLE
#define INT_DIGEST_ENABLE
#define IPV6_DISABLE
#endif

// end of MSDC DTel profiles

#elif defined(MSDC_IPV4_PROFILE)

#define MSDC_IPV4_TABLE_SIZES
#define IPV6_DISABLE
#define INGRESS_UC_SELF_FWD_CHECK_DISABLE
#define TUNNEL_INDEX_BRIDGE_ENABLE
#define NEXTHOP_SCALING
#define TUNNEL_SCALING

#else
//#define FIB_ACL_LABEL_ENABLE
#define RESILIENT_HASH_ENABLE
#define MSDC_L3_TABLE_SIZES
#endif

// end of all MSDC profiles

#elif defined(DC_BASIC_PROFILE)

#define MIN_TABLE_SIZES
#undef QOS_CLASSIFICATION_ENABLE
#undef URPF_DISABLE
#undef NVGRE_DISABLE
#undef GENEVE_DISABLE
#undef MPLS_DISABLE
#undef RACL_DISABLE
#undef FIB_ALPM
#undef EGRESS_QUEUE_STATS_ENABLE
#undef INGRESS_PPG_STATS_ENABLE
#define RACL_STATS_ENABLE
#define PTP_ENABLE
#undef INGRESS_PORT_MIRROR_ENABLE
#endif

#define OUTER_PIM_BIDIR_OPTIMIZATION
#define PIM_BIDIR_OPTIMIZATION

#ifdef MIRROR_DISABLE
#undef INGRESS_PORT_MIRROR_ENABLE
#undef EGRESS_PORT_MIRROR_ENABLE
#undef INGRESS_ACL_ACTION_MIRROR_ENABLE
//#undef EGRESS_ACL_MIRROR_ENABLE
#endif

#ifdef TUNNEL_PARSING_DISABLE
#define TUNNEL_DISABLE
#define MPLS_DISABLE
#define MIRROR_NEXTHOP_DISABLE
#endif

#ifdef MULTICAST_DISABLE
#define L2_MULTICAST_DISABLE
#define L3_MULTICAST_DISABLE
#define TUNNEL_MULTICAST_DISABLE
#endif

#ifdef TUNNEL_DISABLE
#define TUNNEL_MULTICAST_DISABLE
#define IPV4_TUNNEL_DISABLE
#define IPV6_TUNNEL_DISABLE
#undef TUNNEL_NEXTHOP_ENABLE
#else
#define TUNNEL_NEXTHOP_ENABLE
#endif

#ifdef IPV4_DISABLE
#define IPV4_TUNNEL_DISABLE
#define IPV4_L2_MULTICAST_DISABLE
#define IPV4_L3_MULTICAST_DISABLE
#endif

#ifdef IPV6_DISABLE
#define IPV6_TUNNEL_DISABLE
#define IPV6_L2_MULTICAST_DISABLE
#define IPV6_L3_MULTICAST_DISABLE
#endif

#ifdef IPV4_TUNNEL_DISABLE
#define IPV4_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef IPV6_TUNNEL_DISABLE
#define IPV6_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef L2_MULTICAST_DISABLE
#define IPV4_L2_MULTICAST_DISABLE
#define IPV6_L2_MULTICAST_DISABLE
#endif

#ifdef L3_MULTICAST_DISABLE
#define IPV4_L3_MULTICAST_DISABLE
#define IPV6_L3_MULTICAST_DISABLE
#define TUNNEL_MULTICAST_DISABLE
#endif

#ifdef TUNNEL_MULTICAST_DISABLE
#define IPV4_TUNNEL_MULTICAST_DISABLE
#define IPV6_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef L3_DISABLE
#define URPF_DISABLE
#define IPSG_DISABLE
#endif

#if !defined(COPP_METER_DISABLE)
#define COPP_COLOR_DROP_ENABLE
#endif

#ifdef EGRESS_ACL_ENABLE
#define EGRESS_ACL_STATS_ENABLE
#endif

#ifdef QOS_ACL_ENABLE
#define MAC_QOS_ACL_ENABLE
#define IPV4_QOS_ACL_ENABLE
#ifndef IPV6_DISABLE
#define IPV6_QOS_ACL_ENABLE
#endif
#endif

#if defined(DTEL_DROP_REPORT_ENABLE) || defined(DTEL_QUEUE_REPORT_ENABLE)
#define COPP_STATS_ENABLE
#endif

// Defines for switchapi library
#ifdef SRV6_ENABLE
#define P4_SRV6_ENABLE
#endif

#ifdef SFLOW_ENABLE
#define P4_SFLOW_ENABLE
#endif

#ifdef PKTGEN_ENABLE
#define P4_PKTGEN_ENABLE
#endif

#ifdef WCMP_ENABLE
#define P4_WCMP_ENABLE
#endif

#ifdef FLOWLET_ENABLE
#define P4_FLOWLET_ENABLE
#endif

#ifdef RESILIENT_HASH_ENABLE
#define P4_RESILIENT_HASH_ENABLE
#endif

#ifdef FAST_FAILOVER_ENABLE
#define P4_FAST_FAILOVER_ENABLE
#endif

#ifdef WRED_ENABLE
#define P4_WRED_ENABLE
#endif

#ifdef WRED_DROP_ENABLE
#define P4_WRED_DROP_ENABLE
#endif

#ifdef MIRROR_ACL_ENABLE
#define P4_MIRROR_ACL_ENABLE
#endif

#ifdef INGRESS_ACL_ACTION_MIRROR_ENABLE
#define P4_INGRESS_ACL_ACTION_MIRROR_ENABLE
#endif

#ifdef URPF_DISABLE
#define P4_URPF_DISABLE
#endif

#ifdef ILA_ENABLE
#define P4_ILA_ENABLE
#endif

#ifdef IPV6_DISABLE
#define P4_IPV6_DISABLE
#endif

#ifdef MPLS_DISABLE
#define P4_MPLS_DISABLE
#endif

#ifdef MPLS_UDP_ENABLE
#define P4_MPLS_UDP_ENABLE
#endif

#ifdef NAT_DISABLE
#define P4_NAT_DISABLE
#endif

#ifdef MULTICAST_DISABLE
#define P4_MULTICAST_DISABLE
#endif

#ifdef L2_MULTICAST_DISABLE
#define P4_L2_MULTICAST_DISABLE
#endif

#ifdef L3_MULTICAST_DISABLE
#define P4_L3_MULTICAST_DISABLE
#endif

#ifdef TUNNEL_MULTICAST_DISABLE
#define P4_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef TUNNEL_DISABLE
#define P4_TUNNEL_DISABLE
#endif

#ifdef IPV4_TUNNEL_DISABLE
#define P4_IPV4_TUNNEL_DISABLE
#endif

#ifdef IPV6_TUNNEL_DISABLE
#define P4_IPV6_TUNNEL_DISABLE
#endif

#ifdef IPV4_TUNNEL_MULTICAST_DISABLE
#define P4_IPV4_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef IPV6_TUNNEL_MULTICAST_DISABLE
#define P4_IPV6_TUNNEL_MULTICAST_DISABLE
#endif

#ifdef NVGRE_DISABLE
#define P4_NVGRE_DISABLE
#endif

#ifdef GENEVE_DISABLE
#define P4_GENEVE_DISABLE
#endif

#ifdef STORM_CONTROL_DISABLE
#define P4_STORM_CONTROL_DISABLE
#endif

#ifdef IPSG_DISABLE
#define P4_IPSG_DISABLE
#endif

#ifdef ACL_DISABLE
#define P4_ACL_DISABLE
#endif

#ifdef RACL_DISABLE
#define P4_RACL_DISABLE
#endif

#ifdef QOS_CLASSIFICATION_ENABLE
#define P4_QOS_CLASSIFICATION_ENABLE
#endif

#ifdef STP_DISABLE
#define P4_STP_DISABLE
#endif

#ifdef L2_DISABLE
#define P4_L2_DISABLE
#endif

#ifdef L3_DISABLE
#define P4_L3_DISABLE
#endif

#ifdef IPV4_DISABLE
#define P4_IPV4_DISABLE
#endif

#ifndef EGRESS_ACL_ENABLE
#define EGRESS_ACL_RANGE_DISABLE
#endif

#ifdef OUTER_MULTICAST_BRIDGE_DISABLE
#define P4_OUTER_MULTICAST_BRIDGE_DISABLE
#endif

#ifdef RACL_REASON_CODE_DISABLE
#define P4_RACL_REASON_CODE_DISABLE
#endif

#ifdef DOUBLE_TAGGED_DISABLE
#define P4_DOUBLE_TAGGED_DISABLE
#endif

#ifdef ACL_QOS_ENABLE
#define P4_ACL_QOS_ENABLE
#endif

#ifdef QOS_METERING_ENABLE
#define P4_QOS_METERING_ENABLE
#endif

#ifdef QOS_MARKING_ENABLE
#define P4_QOS_MARKING_ENABLE
#undef REWRITE_SWAP
#endif

#ifdef SS_QOS_CLASSIFICATION_ENABLE
#define P4_SS_QOS_CLASSIFICATION_ENABLE
#endif

#ifdef STATS_DISABLE
#define P4_STATS_DISABLE
#endif

#ifdef RACL_STATS_ENABLE
#define P4_RACL_STATS_ENABLE
#endif

#ifdef EGRESS_ACL_STATS_ENABLE
#define P4_EGRESS_ACL_STATS_ENABLE
#endif

#ifdef EGRESS_FILTER
#define P4_EGRESS_FILTER
#endif

#ifdef COPP_METER_DISABLE
#define P4_COPP_METER_DISABLE
#endif

#ifdef MIRROR_DISABLE
#define P4_MIRROR_DISABLE
#endif

#ifdef EGRESS_ACL_ENABLE
#define P4_EGRESS_ACL_ENABLE
#endif

#ifdef INGRESS_MAC_ACL_DISABLE
#define P4_INGRESS_MAC_ACL_DISABLE
#endif

#ifdef EGRESS_MAC_ACL_DISABLE
#define P4_EGRESS_MAC_ACL_DISABLE
#endif

#ifdef INGRESS_ACL_RANGE_DISABLE
#define P4_INGRESS_ACL_RANGE_DISABLE
#endif

#ifdef EGRESS_ACL_RANGE_DISABLE
#define P4_EGRESS_ACL_RANGE_DISABLE
#endif

#ifdef INT_DEBUG
#define P4_INT_DEBUG
#endif

#ifdef BFD_OFFLOAD_ENABLE
#define P4_BFD_OFFLOAD_ENABLE
#endif

#ifdef INT_ENABLE
#define P4_INT_ENABLE
#ifndef INT_L45_MARKER_ENABLE
#define INT_L45_DSCP_ENABLE
#endif
#endif

#ifdef INT_EP_ENABLE
#define P4_INT_EP_ENABLE
#define DTEL_REPORT_ENABLE
#endif

#ifdef INT_TRANSIT_ENABLE
#define P4_INT_TRANSIT_ENABLE
#define DTEL_REPORT_ENABLE
#endif

#ifdef INT_OVER_L4_ENABLE
#define P4_INT_OVER_L4_ENABLE
#endif

#ifdef INT_L45_DSCP_ENABLE
#define P4_INT_L45_DSCP_ENABLE
#endif

#ifdef INT_L45_MARKER_ENABLE
#define P4_INT_L45_MARKER_ENABLE
#endif

#ifdef POSTCARD_ENABLE
#define P4_POSTCARD_ENABLE
#define DTEL_REPORT_ENABLE
#endif

#ifdef DTEL_DROP_REPORT_ENABLE
#define P4_DTEL_DROP_REPORT_ENABLE
#define DTEL_REPORT_LB_ENABLE
#define DTEL_REPORT_ENABLE
#endif

#ifdef DTEL_REPORT_ENABLE
#define P4_DTEL_REPORT_ENABLE
#endif

#ifdef DTEL_FLOW_STATE_TRACK_ENABLE
#define P4_DTEL_FLOW_STATE_TRACK_ENABLE
#ifdef INT_EP_ENABLE
#define INT_DIGEST_ENABLE
#endif
#endif

#ifdef INT_DIGEST_ENABLE
#define P4_INT_DIGEST_ENABLE
#endif

#ifdef DTEL_QUEUE_REPORT_ENABLE
#define P4_DTEL_QUEUE_REPORT_ENABLE
#endif

#ifdef DTEL_REPORT_LB_ENABLE
#define P4_DTEL_REPORT_LB_ENABLE
#endif

#ifdef DTEL_WATCH_INNER_ENABLE
#define P4_DTEL_WATCH_INNER_ENABLE
#endif

#ifdef INGRESS_PORT_MIRROR_ENABLE
#define P4_INGRESS_PORT_MIRROR_ENABLE
#endif

#ifdef EGRESS_PORT_MIRROR_ENABLE
#define P4_EGRESS_PORT_MIRROR_ENABLE
#endif

#ifdef FABRIC_ENABLE
#define P4_FABRIC_ENABLE
#endif

#ifdef COPP_COLOR_DROP_ENABLE
#define P4_COPP_COLOR_DROP_ENABLE
#endif

#ifdef EGRESS_OUTER_BD_STATS_ENABLE
#define P4_EGRESS_OUTER_BD_STATS_ENABLE
#endif

#ifdef INGRESS_UC_SELF_FWD_CHECK_DISABLE
#define P4_INGRESS_UC_SELF_FWD_CHECK_DISABLE
#endif

#ifdef TUNNEL_INDEX_BRIDGE_ENABLE
#define P4_TUNNEL_INDEX_BRIDGE_ENABLE
#endif

#ifdef TUNNEL_V4_VXLAN_ONLY
#define P4_TUNNEL_V4_VXLAN_ONLY
#endif

#ifdef MIRROR_ACL_STATS_ENABLE
#define P4_MIRROR_ACL_STATS_ENABLE
#endif

#ifdef TUNNEL_NEXTHOP_ENABLE
#define P4_TUNNEL_NEXTHOP_ENABLE
#endif

#ifdef MAC_QOS_ACL_ENABLE
#define P4_MAC_QOS_ACL_ENABLE
#endif

#ifdef IPV4_QOS_ACL_ENABLE
#define P4_IPV4_QOS_ACL_ENABLE
#endif

#ifdef IPV6_QOS_ACL_ENABLE
#define P4_IPV6_QOS_ACL_ENABLE
#endif

#ifdef QOS_ACL_ENABLE
#define P4_QOS_ACL_ENABLE
#endif

#ifdef PTP_ENABLE
#define P4_PTP_ENABLE
#endif

#ifdef TUNNEL_PARSING_DISABLE
#define P4_TUNNEL_PARSING_DISABLE
#endif

#ifdef MIRROR_NEXTHOP_DISABLE
#define P4_MIRROR_NEXTHOP_DISABLE
#endif

#ifdef INGRESS_PORT_IN_EGRESS_SYSTEM_ACL_ENABLE
#define P4_INGRESS_PORT_IN_EGRESS_SYSTEM_ACL_ENABLE
#endif

#ifdef HASH_32BIT_ENABLE
#define P4_HASH_32BIT_ENABLE
#endif

#ifdef ERSPAN_REWRITE_MODE_ENABLE
#define P4_ERSPAN_REWRITE_MODE_ENABLE
#endif

#ifdef ETYPE_IN_IP_ACL_KEY_ENABLE
#define P4_ETYPE_IN_IP_ACL_KEY_ENABLE
#endif

#ifdef TRANSIENT_LOOP_PREVENTION
#define P4_TRANSIENT_LOOP_PREVENTION_ENABLE
#endif

#ifdef COPP_STATS_ENABLE
#define P4_COPP_STATS_ENABLE
#endif

#ifdef ECMP_MEMBER_FAST_DEACTIVATION_ENABLE
#define P4_ECMP_MEMBER_FAST_DEACTIVATION_ENABLE
#endif

#ifdef LEARN_INVALIDATE_ENABLE
#define P4_LEARN_INVALIDATE_ENABLE
#endif

#ifdef EGRESS_ACL_STATS_ENABLE
#define P4_EGRESS_ACL_STATS_ENABLE
#endif

#ifdef MLAG_ENABLE
#define P4_MLAG_ENABLE
#endif /* MLAG_ENABLE */

#ifdef ETHERNET_ZERO_MAC_CHECK_DISABLE
#define P4_ETHERNET_ZERO_MAC_CHECK_DISABLE
#endif

#ifdef IPV4_4_TUPLE_IN_SYSTEM_ACL_KEY_ENABLE
#define P4_IPV4_4_TUPLE_IN_SYSTEM_ACL_KEY_ENABLE
#endif

#ifdef CPU_TX_YID_REWRITE_ENABLE
#define P4_CPU_TX_YID_REWRITE_ENABLE
#endif

#ifdef EGRESS_QUEUE_STATS_ENABLE
#define P4_EGRESS_QUEUE_STATS_ENABLE
#endif

#ifdef INGRESS_PPG_STATS_ENABLE
#define P4_INGRESS_PPG_STATS_ENABLE
#endif

#ifdef IPV4_4_TUPLE_IN_SYSTEM_ACL_KEY_ENABLE
#define P4_IPV4_4_TUPLE_IN_SYSTEM_ACL_KEY_ENABLE
#endif

#ifdef GLOBAL_TC_ICOS_QUEUE_TABLE
#define P4_GLOBAL_TC_ICOS_QUEUE_TABLE
#endif

#ifdef QINQ_ENABLE
#define P4_QINQ_ENABLE
#endif

#ifdef DSCP_IN_IP_ACL_KEY_ENABLE
#define P4_DSCP_IN_IP_ACL_KEY_ENABLE
#endif

