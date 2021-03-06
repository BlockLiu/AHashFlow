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
/*
 * Nexthop related processing
 */

/*
 * nexthop metadata
 */
header_type nexthop_metadata_t {
    fields {
        nexthop_type : 1;                        /* final next hop index type */
        nexthop_glean : 1;                       /* Glean adjacency */
#ifdef TRANSIENT_LOOP_PREVENTION
        nexthop_offset : 8;			 /* Offset next group */
#endif
    }
}

#ifdef ENT_DC_GENERAL_PROFILE
@pragma pa_container_size ingress ig_intr_md_for_tm.disable_ucast_cutthru 8
#endif /* ENT_DC_GENERAL_PROFILE */

metadata nexthop_metadata_t nexthop_metadata;

/*****************************************************************************/
/* Forwarding result lookup and decisions                                    */
/*****************************************************************************/
action set_l2_redirect() {
#ifdef TRANSIENT_LOOP_PREVENTION
    add(l3_metadata.nexthop_index, l2_metadata.l2_nexthop, nexthop_metadata.nexthop_offset);
#else
    modify_field(l3_metadata.nexthop_index, l2_metadata.l2_nexthop);
#endif
    modify_field(nexthop_metadata.nexthop_type, l2_metadata.l2_nexthop_type);
    modify_field(ingress_metadata.egress_ifindex, 0);
    invalidate(ig_intr_md_for_tm.mcast_grp_b);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_acl_redirect() {
#ifdef TRANSIENT_LOOP_PREVENTION
    add(l3_metadata.nexthop_index, acl_metadata.acl_nexthop, nexthop_metadata.nexthop_offset);
#else
    modify_field(l3_metadata.nexthop_index, acl_metadata.acl_nexthop);
#endif
    modify_field(nexthop_metadata.nexthop_type, acl_metadata.acl_nexthop_type);
    modify_field(ingress_metadata.egress_ifindex, 0);
    invalidate(ig_intr_md_for_tm.mcast_grp_b);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_racl_redirect() {
#ifdef TRANSIENT_LOOP_PREVENTION
    add(l3_metadata.nexthop_index, acl_metadata.racl_nexthop, nexthop_metadata.nexthop_offset);
#else
    modify_field(l3_metadata.nexthop_index, acl_metadata.racl_nexthop);
#endif
    modify_field(nexthop_metadata.nexthop_type, acl_metadata.racl_nexthop_type);
    modify_field(l3_metadata.routed, TRUE);
    modify_field(ingress_metadata.egress_ifindex, 0);
    invalidate(ig_intr_md_for_tm.mcast_grp_b);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_fib_redirect() {
#ifdef TRANSIENT_LOOP_PREVENTION
    add(l3_metadata.nexthop_index, l3_metadata.fib_nexthop, nexthop_metadata.nexthop_offset);
#else
    modify_field(l3_metadata.nexthop_index, l3_metadata.fib_nexthop);
#endif
    modify_field(nexthop_metadata.nexthop_type, l3_metadata.fib_nexthop_type);
    modify_field(l3_metadata.routed, TRUE);
    invalidate(ig_intr_md_for_tm.mcast_grp_b);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_nat_redirect() {
#ifdef TRANSIENT_LOOP_PREVENTION
    add(l3_metadata.nexthop_index, nat_metadata.nat_nexthop, nexthop_metadata.nexthop_offset);
#else
    modify_field(l3_metadata.nexthop_index, nat_metadata.nat_nexthop);
#endif
    modify_field(nexthop_metadata.nexthop_type, nat_metadata.nat_nexthop_type);
    modify_field(l3_metadata.routed, TRUE);
    invalidate(ig_intr_md_for_tm.mcast_grp_b);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_cpu_redirect(cpu_ifindex) {
    modify_field(l3_metadata.routed, FALSE);
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, cpu_ifindex);
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, 0);
#endif /* FABRIC_ENABLE */
}

action set_rmac_non_ip_drop() {
    modify_field(ingress_metadata.drop_flag, TRUE);
    modify_field(ingress_metadata.drop_reason, DROP_RMAC_HIT_NON_IP);
}

action set_multicast_route() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
    modify_field(ig_intr_md_for_tm.mcast_grp_b,
                 multicast_metadata.multicast_route_mc_index);
    modify_field(l3_metadata.routed, TRUE);
    modify_field(l3_metadata.same_bd_check, 0xFFFF);
}

action set_multicast_rpf_fail_bridge() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
    modify_field(ig_intr_md_for_tm.mcast_grp_b,
                 multicast_metadata.multicast_bridge_mc_index);
    modify_field(multicast_metadata.mcast_rpf_fail, TRUE);
}

action set_multicast_rpf_fail_flood_to_mrouters() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, IFINDEX_FLOOD);
    modify_field(multicast_metadata.mcast_rpf_fail, TRUE);
    modify_field(multicast_metadata.flood_to_mrouters, TRUE);
}

action set_multicast_bridge() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
    modify_field(ig_intr_md_for_tm.mcast_grp_b,
                 multicast_metadata.multicast_bridge_mc_index);
}

action set_multicast_miss_flood() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, IFINDEX_FLOOD);
}

action set_multicast_drop() {
    modify_field(ingress_metadata.drop_flag, TRUE);
    modify_field(ingress_metadata.drop_reason, DROP_MULTICAST_SNOOPING_ENABLED);
}

action set_multicast_miss_flood_to_mrouters() {
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
    modify_field(ingress_metadata.egress_ifindex, IFINDEX_FLOOD);
    modify_field(multicast_metadata.flood_to_mrouters, TRUE);
}

#ifdef L3_HEAVY_INT_LEAF_PROFILE
@pragma stage 6
#endif
table fwd_result {
    reads {
        l2_metadata.l2_redirect : ternary;
        acl_metadata.acl_redirect : ternary;
        acl_metadata.racl_redirect : ternary;
        l3_metadata.rmac_hit : ternary;
        l3_metadata.fib_hit : ternary;
#ifndef NAT_DISABLE
        nat_metadata.nat_hit : ternary;
#endif /* NAT_DISABLE */
        l2_metadata.lkp_pkt_type : ternary;
        l3_metadata.lkp_ip_type : ternary;
        multicast_metadata.igmp_snooping_enabled : ternary;
#ifndef IPV6_DISABLE
        multicast_metadata.mld_snooping_enabled : ternary;
#endif /* IPV6_DISABLE */
        multicast_metadata.mcast_route_hit : ternary;
        multicast_metadata.mcast_bridge_hit : ternary;
        multicast_metadata.mcast_rpf_group : ternary;
        multicast_metadata.mcast_mode : ternary;
        nexthop_metadata.nexthop_type : ternary; // only for ecmp group add
#if !defined(L2_MULTICAST_DISABLE) || !defined(L3_MULTICAST_DISABLE)
        l3_metadata.lkp_ip_llmc : ternary;
        l3_metadata.lkp_ip_mc : ternary;
#endif /* !defined(L2_MULTICAST_DISABLE) || !defined(L3_MULTICAST_DISABLE) */
    }
    actions {
        nop;
        set_l2_redirect;
        set_fib_redirect;
        set_cpu_redirect;
        set_acl_redirect;
#ifndef RACL_DISABLE
        set_racl_redirect;
#endif
	set_rmac_non_ip_drop;
#ifndef NAT_DISABLE
        set_nat_redirect;
#endif /* NAT_DISABLE */
#ifndef MULTICAST_DISABLE
        set_multicast_route;
        set_multicast_rpf_fail_bridge;
        set_multicast_rpf_fail_flood_to_mrouters;
        set_multicast_bridge;
        set_multicast_miss_flood;
        set_multicast_miss_flood_to_mrouters;
        set_multicast_drop;
#endif /* MULTICAST_DISABLE */
    }
    size : FWD_RESULT_TABLE_SIZE;
}

control process_fwd_results {
    if (not (BYPASS_ALL_LOOKUPS)) {
        apply(fwd_result);
    }
}


/*****************************************************************************/
/* ECMP lookup                                                               */
/*****************************************************************************/
/*
 * If dest mac is not know, then unicast packet needs to be flooded in
 * egress BD
 */
action set_ecmp_nexthop_details_for_post_routed_flood(bd, uuc_mc_index,
                                                      nhop_index) {
    modify_field(ig_intr_md_for_tm.mcast_grp_b, uuc_mc_index);
    modify_field(l3_metadata.nexthop_index, nhop_index);
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
}

action set_ecmp_nexthop_details(ifindex, port_lag_index, bd, nhop_index, tunnel) {
    modify_field(ingress_metadata.egress_ifindex, ifindex);
    modify_field(ingress_metadata.egress_port_lag_index, port_lag_index);
    modify_field(l3_metadata.nexthop_index, nhop_index);
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
    bit_xor(l2_metadata.same_if_check, l2_metadata.same_if_check, ifindex);
#ifndef TUNNEL_DISABLE
    bit_xor(tunnel_metadata.tunnel_if_check,
	    tunnel_metadata.tunnel_terminate, tunnel);
#endif
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
    bit_and(ig_intr_md_for_tm.disable_ucast_cutthru,
            l2_metadata.non_ip_packet, tunnel);
}

action set_ecmp_nexthop_details_with_tunnel(bd, tunnel_dst_index, tunnel) {
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
#ifndef TUNNEL_DISABLE
    bit_xor(tunnel_metadata.tunnel_if_check,
            tunnel_metadata.tunnel_terminate, tunnel);
#endif
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
    modify_field(tunnel_metadata.tunnel_dst_index, tunnel_dst_index);
    modify_field(ingress_metadata.egress_ifindex, 0x0);
    bit_and(ig_intr_md_for_tm.disable_ucast_cutthru,
            l2_metadata.non_ip_packet, tunnel);
}

action set_wcmp() {
}

field_list l3_hash_fields {
#if defined(RESILIENT_HASH_ENABLE)
#ifndef HASH_32BIT_ENABLE
    hash_metadata.hash2;
    hash_metadata.hash1;
#endif
    hash_metadata.hash2;
#endif /* RESILIENT_HASH_ENABLE */
    hash_metadata.hash1;
#ifdef FLOWLET_ENABLE
    flowlet_metadata.id;
#endif /* FLOWLET_ENABLE */
}

field_list_calculation ecmp_hash {
    input {
        l3_hash_fields;
    }
#if defined(RESILIENT_HASH_ENABLE)
    algorithm {
	identity;
	crc_64;
    }
    output_width : 52;
#elif defined(FLOWLET_ENABLE)
    algorithm {
	crc_16;
	identity;
    }
    output_width : 14;
#else
    algorithm {
    	identity;
	crc_16_dect;
    }
    output_width : 14;
#endif /* RESILIENT_HASH_ENABLE */
}

action_selector ecmp_selector {
    selection_key : ecmp_hash;
#ifdef RESILIENT_HASH_ENABLE
    selection_mode : resilient;
#else
    selection_mode : fair;
#endif /* RESILIENT_HASH_ENABLE */
}

action_profile ecmp_action_profile {
    actions {
        nop;
        set_ecmp_nexthop_details;
        set_ecmp_nexthop_details_with_tunnel;
        set_ecmp_nexthop_details_for_post_routed_flood;
#ifdef WCMP_ENABLE
        set_wcmp;
#endif /* WCMP_ENABLE */
    }
    size : ECMP_SELECT_TABLE_SIZE;
    dynamic_action_selection : ecmp_selector;
}

table ecmp_group {
    reads {
        l3_metadata.nexthop_index : exact;
    }
    action_profile: ecmp_action_profile;
    size : ECMP_GROUP_TABLE_SIZE;
}

/*****************************************************************************/
/* WCMP lookup                                                               */
/*****************************************************************************/
#ifdef WCMP_ENABLE
action set_wcmp_nexthop_details(ifindex, port_lag_index, bd, nhop_index, tunnel) {
    modify_field(ingress_metadata.egress_ifindex, ifindex);
    modify_field(ingress_metadata.egress_port_lag_index, port_lag_index);
    modify_field(l3_metadata.nexthop_index, nhop_index);
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
    bit_xor(l2_metadata.same_if_check, l2_metadata.same_if_check, ifindex);
    bit_xor(tunnel_metadata.tunnel_if_check,
            tunnel_metadata.tunnel_terminate, tunnel);
    bit_and(ig_intr_md_for_tm.disable_ucast_cutthru,
            l2_metadata.non_ip_packet, tunnel);
}

table wcmp_group {
    reads {
        l3_metadata.nexthop_index : exact;
        hash_metadata.hash1 mask 0x00ff : range;
    }
    actions {
        set_wcmp_nexthop_details;
    }
    size : WCMP_GROUP_TABLE_SIZE;
}
#endif /* WCMP_ENABLE */

/*****************************************************************************/
/* Nexthop lookup                                                            */
/*****************************************************************************/
/*
 * If dest mac is not know, then unicast packet needs to be flooded in
 * egress BD
 */
action set_nexthop_details_for_post_routed_flood(bd, uuc_mc_index) {
    modify_field(ig_intr_md_for_tm.mcast_grp_b, uuc_mc_index);
    modify_field(ingress_metadata.egress_ifindex, 0);
    modify_field(ingress_metadata.egress_port_lag_index, 0);
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
#ifdef FABRIC_ENABLE
    modify_field(fabric_metadata.dst_device, FABRIC_DEVICE_MULTICAST);
#endif /* FABRIC_ENABLE */
}

action set_nexthop_details(ifindex, port_lag_index, bd, tunnel) {
    modify_field(ingress_metadata.egress_ifindex, ifindex);
    modify_field(ingress_metadata.egress_port_lag_index, port_lag_index);
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
    bit_xor(l2_metadata.same_if_check, l2_metadata.same_if_check, ifindex);
#ifndef TUNNEL_DISABLE
    bit_xor(tunnel_metadata.tunnel_if_check,
            tunnel_metadata.tunnel_terminate, tunnel);
#endif
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
}

action set_nexthop_details_with_tunnel(bd, tunnel_dst_index, tunnel) {
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
#ifndef TUNNEL_DISABLE
    bit_xor(tunnel_metadata.tunnel_if_check,
            tunnel_metadata.tunnel_terminate, tunnel);
#endif
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, bd);
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
    bit_and(ig_intr_md_for_tm.disable_ucast_cutthru,
            l2_metadata.non_ip_packet, tunnel);
    modify_field(tunnel_metadata.tunnel_dst_index, tunnel_dst_index);
    modify_field(ingress_metadata.egress_ifindex, 0x0);
}

action set_nexthop_details_for_glean(ifindex) {
    modify_field(ingress_metadata.egress_ifindex, ifindex);
    modify_field(nexthop_metadata.nexthop_glean, TRUE);
#ifndef INGRESS_UC_SELF_FWD_CHECK_DISABLE
    bit_xor(l3_metadata.same_bd_check, ingress_metadata.bd, 0x3FFF);
#endif /* INGRESS_UC_SELF_FWD_CHECK_DISABLE */
}

action set_nexthop_details_for_drop() {
    modify_field(ingress_metadata.drop_flag, TRUE);
    modify_field(ingress_metadata.drop_reason, DROP_NHOP);
}

#ifdef L3_HEAVY_INT_LEAF_PROFILE
@pragma stage 8
#endif
table nexthop {
    reads {
        l3_metadata.nexthop_index : exact;
    }
    actions {
        nop;
        set_nexthop_details;
        set_nexthop_details_with_tunnel;
        set_nexthop_details_for_post_routed_flood;
	set_nexthop_details_for_glean;
        set_nexthop_details_for_drop;
    }
    size : NEXTHOP_TABLE_SIZE;
}

#ifdef TRANSIENT_LOOP_PREVENTION
action set_nexthop_group(group_id) {
    modify_field(nexthop_metadata.nexthop_offset, group_id);
}

table neighbor_detect {
    reads {
        ig_intr_md.ingress_port : ternary;
        ethernet.srcAddr : ternary;
    }
    actions {
        nop;
        set_nexthop_group;
    }
    size : 512; // NEIGHBOR_NUM_TABLE_SIZE;
}
#endif

control process_nexthop {
    if (nexthop_metadata.nexthop_type == NEXTHOP_TYPE_ECMP) {
#ifdef FAST_FAILOVER_ENABLE
        if (valid(pktgen_recirc)) {
            apply(ecmp_failover);
            apply(ecmp_failover_recirc);
        } else {
#endif
        /* resolve ecmp */
#ifdef WCMP_ENABLE
            apply(ecmp_group) {
                set_wcmp {
                    /* resolve wcmp */
                    apply(wcmp_group);
                }
            }
#else
            apply(ecmp_group);
#endif /* WCMP_ENABLE */

#ifdef FAST_FAILOVER_ENABLE
        }
#endif /* FAST_FAILOVER_ENABLE */

    } else {
        /* resolve nexthop */
        apply(nexthop);
    }
}
