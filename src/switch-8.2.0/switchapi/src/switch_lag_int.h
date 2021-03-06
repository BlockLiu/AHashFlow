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

#ifndef __SWITCH_LAG_INT_H__
#define __SWITCH_LAG_INT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** maximum lag members */
#define MAX_LAG_GROUP_SIZE (64)

/** maximum lag groups */
#define SWITCH_API_MAX_LAG 256

/** lag handle wrappers */
#define switch_lag_handle_create(_device) \
  switch_handle_create(                   \
      _device, SWITCH_HANDLE_TYPE_LAG, sizeof(switch_lag_info_t))

#define switch_lag_handle_delete(_device, _handle) \
  switch_handle_delete(_device, SWITCH_HANDLE_TYPE_LAG, _handle)

#define switch_lag_get(_device, _handle, _info) \
  switch_handle_get(_device, SWITCH_HANDLE_TYPE_LAG, _handle, (void **)_info)

/** lag member handle wrappers */
#define switch_lag_member_handle_create(_device) \
  switch_handle_create(                          \
      _device, SWITCH_HANDLE_TYPE_LAG_MEMBER, sizeof(switch_lag_member_t))

#define switch_lag_member_handle_delete(_device, _handle) \
  switch_handle_delete(_device, SWITCH_HANDLE_TYPE_LAG_MEMBER, _handle)

#define switch_lag_member_get(_device, _handle, _info) \
  switch_handle_get(                                   \
      _device, SWITCH_HANDLE_TYPE_LAG_MEMBER, _handle, (void **)_info)

/** lag member info */
typedef struct switch_lag_member_s {
  /** list node */
  switch_node_t node;

  /** port handle */
  switch_handle_t port_handle;

  /** lag member handle - self pointer */
  switch_handle_t lag_member_handle;

  /** lag handle - parent pointer */
  switch_handle_t lag_handle;

  /** direction - ingress/egress */
  switch_direction_t direction;

  /** action profile hardware handle */
  switch_pd_mbr_hdl_t mbr_hdl;

  /** peer_link table hardware handle */
  switch_pd_hdl_t peer_link_hw_entry;

  /** active member for failover */
  bool active;

  /** peer-link between a pair of mLAG switches */
  bool peer_link;

  /** mLAG member */
  bool mlag;

} switch_lag_member_t;

typedef struct switch_lag_hostifs_s {
  /** list node */
  switch_node_t node;
  switch_handle_t hostif_handle;
  switch_handle_t tx_filter_handle;
  switch_handle_t tx_filter_handle_internal;
} switch_lag_hostif_t;

/** LAG Information */
typedef struct switch_lag_info_s {
  /** lag type - simple/weighted */
  switch_lag_type_t type;

  /** lag port_lag_index */
  switch_port_lag_index_t port_lag_index;

  /** list of interfaces created on the lag */
  switch_array_t intf_array;

  /** list of lag members */
  switch_list_t members;

  /** number of lag members */
  switch_size_t member_count;

  /** ingress lag pruning index */
  switch_yid_t yid;

  /** ingress acl port lag label */
  switch_port_lag_label_t ingress_port_lag_label;

  /** egress acl port lag label */
  switch_port_lag_label_t egress_port_lag_label;

  /** peer-link between a pair of mLAG switches */
  bool peer_link;

  /** mLAG member */
  bool mlag;

  /** hostif handle */
  switch_handle_t hostif_handle;

  switch_pd_hdl_t hw_entry;

  switch_pd_hdl_t pd_group_hdl;

  /** ingress acl group handle */
  switch_handle_t ingress_acl_group_handle;

  /** egress acl group handle */
  switch_handle_t egress_acl_group_handle;

  switch_port_bind_mode_t bind_mode;

  /** list of hostif associated with this lag */
  switch_list_t hostifs;

  /** lag member handle - designated member for hostif tx packets */
  switch_handle_t designated_lag_member_handle;

  /** drop untagged packet */
  bool drop_untagged_packet;

  /** drop tagged packet */
  bool drop_tagged_packet;

  /** native vlan_id */
  switch_vlan_t vlan_id;

} switch_lag_info_t;

/* lag device context */
typedef struct switch_lag_context_s {
  /** peer_link lag handle */
  switch_handle_t peer_link_lag_hdl;

} switch_lag_context_t;

switch_status_t switch_lag_init(switch_device_t device);

switch_status_t switch_lag_free(switch_device_t device);

switch_status_t switch_lag_default_entries_add(switch_device_t device);

switch_status_t switch_lag_default_entries_delete(switch_device_t device);

switch_status_t switch_lag_acl_group_set(switch_device_t device,
                                         switch_handle_t lag_handle,
                                         switch_direction_t direction,
                                         switch_handle_t acl_group);

switch_status_t switch_lag_peer_link_prune_mask_table_update(
    switch_device_t device,
    switch_handle_t lag_handle,
    switch_dev_port_t dev_port,
    bool add_port);

switch_status_t switch_lag_hostif_designated_port_update(
    switch_device_t device, switch_handle_t lag_handle);

switch_status_t switch_lag_hostif_add(switch_device_t device,
                                      switch_handle_t lag_handle,
                                      switch_handle_t hostif_handle);

switch_status_t switch_lag_hostif_delete(switch_device_t device,
                                         switch_handle_t lag_handle,
                                         switch_handle_t hostif_handle);

switch_status_t switch_lag_hostif_tx_filter_add(
    switch_device_t device,
    switch_handle_t lag_handle,
    switch_handle_t tx_filter_handle);

switch_status_t switch_lag_hostif_tx_filter_delete(
    switch_device_t device,
    switch_handle_t lag_handle,
    switch_handle_t tx_filter_handle);

switch_status_t switch_lag_hostif_designated_port_handle_get(
    switch_device_t device,
    switch_handle_t lag_handle,
    switch_handle_t *port_handle);

#ifdef __cplusplus
}
#endif

#endif /* __SWITCH_LAG_INT_H__ */
