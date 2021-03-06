################################################################################
# BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
#
# Copyright (c) 2015-2016 Barefoot Networks, Inc.

# All Rights Reserved.
#
# NOTICE: All information contained herein is, and remains the property of
# Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
# technical concepts contained herein are proprietary to Barefoot Networks,
# Inc.
# and its suppliers and may be covered by U.S. and Foreign Patents, patents in
# process, and are protected by trade secret or copyright law.
# Dissemination of this information or reproduction of this material is
# strictly forbidden unless prior written permission is obtained from
# Barefoot Networks, Inc.
#
# No warranty, explicit or implicit is provided, unless granted under a
# written agreement with Barefoot Networks, Inc.
#
# $Id: $
#
###############################################################################
"""
Thrift API interface ACL tests
"""

import switchapi_thrift

import time
import sys
import logging

import unittest
import random
import pdb

import pd_base_tests
try:
    import pltfm_pm_rpc
    from pltfm_pm_rpc.ttypes import *
except ImportError:
    pass
import ptf.dataplane as dataplane

from ptf import config
from ptf.testutils import *
from ptf.thriftutils import *

import os

from switchapi_thrift.switch_api_headers import *
from switchapi_thrift.ttypes import *

from erspan3 import *

this_dir = os.path.dirname(os.path.abspath(__file__))

sys.path.append(os.path.join(this_dir, '../../base'))
from common.utils import *
from common.api_utils import *
sys.path.append(os.path.join(this_dir, '../../base/api-tests'))
import api_base_tests

device=0
cpu_port=64
swports = []
for device, port, ifname in config["interfaces"]:
    swports.append(port)

if swports == []:
    swports = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
invalid_hdl = 0

###############################################################################
@group('sflow')
@group('ent')
class TestSflow_session(api_base_tests.ThriftInterfaceDataPlane):
    def runTest(self):
        print "Create/Delete sflow sessions Test"
        s_hdls = []
        # create 16 sessions (max allowed = 16)
        for s in range(0, 16):
            print "Create sflow session ", s
            sflow_info1 = switcht_sflow_info_t(
                timeout_usec=100,
                sample_rate=100 + s,  #5
                extract_len=80,
                collector_type=0,  #CPU
                egress_port_hdl=cpu_port)

            sf_hdl = self.client.switch_api_sflow_session_create(device,
                                                                 sflow_info1)
            assert (sf_hdl != invalid_hdl)
            print "hdl = ", sf_hdl
            s_hdls.append(sf_hdl)
        # create 17th session - should fail
        sflow_info1 = switcht_sflow_info_t(
            timeout_usec=100,
            sample_rate=1000,
            extract_len=80,
            collector_type=0,  #CPU
            egress_port_hdl=cpu_port)
        sf_hdl = self.client.switch_api_sflow_session_create(device,
                                                             sflow_info1)
        print "hdl = ", sf_hdl
        assert (sf_hdl == invalid_hdl)

        # delete 2 sessions, create 2 sessions
        print "Delete a few sessions"
        self.client.switch_api_sflow_session_delete(device, s_hdls[0], 0)
        self.client.switch_api_sflow_session_delete(device, s_hdls[7], 0)
        print "Re-create a few sessions"
        s_hdls[0] = self.client.switch_api_sflow_session_create(device,
                                                                sflow_info1)
        assert (s_hdls[0] != invalid_hdl)
        s_hdls[7] = self.client.switch_api_sflow_session_create(device,
                                                                sflow_info1)
        assert (s_hdls[7] != invalid_hdl)

        # delete all sessions
        for s in range(0, 16):
            self.client.switch_api_sflow_session_delete(device, s_hdls[s], 0)
        print "Done"


###############################################################################
@group('sflow')
@group('ent')
class TestSflow_ingress_port(pd_base_tests.ThriftInterfaceDataPlane,
                             api_base_tests.ThriftInterfaceDataPlane):
    def __init__(self):
        pd_base_tests.ThriftInterfaceDataPlane.__init__(self, ["switch"],
                                                        ["dc"])

    def runTest(self):
        print "Test sflow based on ingress port using packet on port %d" % swports[
            1], "  -> port %d" % swports[
                2], "  (192.168.0.1 -> 172.16.0.1 [id = 101])"

        pd_base_tests.ThriftInterfaceDataPlane.setUp(self)
        devport = []
        devport.append(swport_to_devport(self, swports[0]))
        devport.append(swport_to_devport(self, swports[1]))
        devport.append(swport_to_devport(self, swports[2]))
        cpu_port = get_cpu_port(self)

        api_base_tests.ThriftInterfaceDataPlane.setUp(self)
        vrf = self.client.switch_api_vrf_create(0, 2)

        rmac = self.client.switch_api_router_mac_group_create(
            device, SWITCH_RMAC_TYPE_INNER)
        self.client.switch_api_router_mac_add(0, rmac, '00:77:66:55:44:33')

        port1 = self.client.switch_api_port_id_to_handle_get(device, swports[1])
        port2 = self.client.switch_api_port_id_to_handle_get(device, swports[2])

        rif_info = switcht_rif_info_t(
            rif_type=SWITCH_RIF_TYPE_INTF,
            vrf_handle=vrf,
            rmac_handle=rmac,
            v4_unicast_enabled=True)
        rif1 = self.client.switch_api_rif_create(0, rif_info)
        rif2 = self.client.switch_api_rif_create(0, rif_info)

        i_info1 = switcht_interface_info_t(
            handle=port1, type=SWITCH_INTERFACE_TYPE_PORT, rif_handle=rif1)
        if1 = self.client.switch_api_interface_create(0, i_info1)
        i_ip1 = switcht_ip_addr_t(ipaddr='192.168.0.2', prefix_length=16)
        self.client.switch_api_l3_interface_address_add(0, rif1, vrf, i_ip1)

        i_info2 = switcht_interface_info_t(
            handle=port2, type=SWITCH_INTERFACE_TYPE_PORT, rif_handle=rif2)
        if2 = self.client.switch_api_interface_create(0, i_info2)
        i_ip2 = switcht_ip_addr_t(ipaddr='172.16.0.2', prefix_length=16)
        self.client.switch_api_l3_interface_address_add(0, rif2, vrf, i_ip2)

        # Add a static route
        i_ip3 = switcht_ip_addr_t(ipaddr='172.20.10.1', prefix_length=32)
        nhop, neighbor = switch_api_l3_nhop_neighbor_create(self, device, rif2, i_ip3, '00:11:22:33:44:55')
        self.client.switch_api_l3_route_add(0, vrf, i_ip3, nhop)

        # create an sflow session
        print "Create sflow session"
        sflow_info1 = switcht_sflow_info_t(
            timeout_usec=100,
            sample_rate=1,
            extract_len=0,
            collector_type=0,  #CPU
            egress_port_hdl=cpu_port)

        sflow1 = self.client.switch_api_sflow_session_create(device,
                                                             sflow_info1)

        # attach sflow session to ingress port 1
        # create kvp to match ingress port
        print "Attach sflow session to port 1"
        kvp = []
        kvp_val = switcht_acl_value_t(value_num=port1)
        kvp_mask = switcht_acl_value_t(value_num=0xffffffff)
        kvp.append(switcht_acl_key_value_pair_t(0, kvp_val, kvp_mask))
        flow_hdl1 = self.client.switch_api_sflow_session_attach(device, sflow1,
                                                                1, 0, 0, kvp)

        print "Attach sflow session to port 2"
        kvp = []
        kvp_val = switcht_acl_value_t(value_num=port2)
        kvp_mask = switcht_acl_value_t(value_num=0xffffffff)
        kvp.append(switcht_acl_key_value_pair_t(0, kvp_val, kvp_mask))
        flow_hdl2 = self.client.switch_api_sflow_session_attach(device, sflow1,
                                                                1, 0, 0, kvp)

        # create and send the test packet(s)
        pkt = simple_tcp_packet(
            pktlen=100,
            eth_dst='00:77:66:55:44:33',
            eth_src='00:22:22:22:22:22',
            ip_dst='172.20.10.1',
            ip_src='192.168.0.1',
            ip_id=105,
            ip_ttl=64)

        exp_pkt = simple_tcp_packet(
            pktlen=100,
            eth_dst='00:11:22:33:44:55',
            eth_src='00:77:66:55:44:33',
            ip_dst='172.20.10.1',
            ip_src='192.168.0.1',
            ip_id=105,
            ip_ttl=63)

        sflow_sid = sflow1 & 0x03FFFFFF  # handle_to_id
        flow_id = flow_hdl1 & 0x03FFFFFF
        print "sflow sid = %d, flow_id %d" % (sflow_sid, flow_id)
        ingress_ifindex = self.client.switch_api_interface_ifindex_get(device,
                                                                       if1)
        exp_pkt_sflow = simple_cpu_packet(
            ingress_ifindex=ingress_ifindex,
            ingress_bd=0,
            ingress_port=devport[1],
            reason_code=0x4,
            sflow_sid=sflow_sid,
            inner_pkt=pkt)

        for i in range(0, 1):
            send_packet(self, swports[1], str(pkt))
            verify_packet(self, exp_pkt, swports[2])
            verify_packet(
                self, cpu_packet_mask_ingress_bd(exp_pkt_sflow), cpu_port)

        print "Detach sflow Session"
        self.client.switch_api_sflow_session_detach(device, sflow1, flow_hdl1)
        # make sure pkts are not sent to cpu anymore
        send_packet(self, swports[1], str(pkt))
        verify_packet(self, exp_pkt, swports[2])
        verify_no_other_packets(self)

        print "Delete sflow Session"
        print "Attach more sflow sessions before deletion"
        kvp = []
        kvp_val = switcht_acl_value_t(value_num=port1)
        kvp_mask = switcht_acl_value_t(value_num=0xffffffff)
        kvp.append(switcht_acl_key_value_pair_t(0, kvp_val, kvp_mask))
        flow_hdl1 = self.client.switch_api_sflow_session_attach(device, sflow1,
                                                                1, 0, 0, kvp)

        self.client.switch_api_sflow_session_delete(device, sflow1, 1)
        #cleanup
        self.client.switch_api_neighbor_delete(0, neighbor)
        self.client.switch_api_nhop_delete(0, nhop)
        self.client.switch_api_l3_route_delete(0, vrf, i_ip3, if2)

        self.client.switch_api_l3_interface_address_delete(0, rif1, vrf, i_ip1)
        self.client.switch_api_l3_interface_address_delete(0, rif2, vrf, i_ip2)

        self.client.switch_api_interface_delete(0, if1)
        self.client.switch_api_interface_delete(0, if2)

        self.client.switch_api_rif_delete(0, rif1)
        self.client.switch_api_rif_delete(0, rif2)

        self.client.switch_api_router_mac_delete(0, rmac, '00:77:66:55:44:33')
        self.client.switch_api_router_mac_group_delete(0, rmac)
        self.client.switch_api_vrf_delete(0, vrf)


###############################################################################
