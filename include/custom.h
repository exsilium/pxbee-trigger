/*
 * Write here your custom declarations.
 *
 * They will be included automatically in
 * the project.
 *
 */
#include <zigbee/zdo.h>

extern wpan_ep_state_t zdo_ep_state;
#define ZIGBEE_ZDO_VERBOSE

#define CUSTOM_ENDPOINT     0xEA
#define CUSTOM_EP_PROFILE   0x0104

 /* With this macro the prototypes of clusters' callbacks and extern variables are included in endpoints.c
  * Array custom_ep_data_clusters[] is declared in main.c
  * Function custom_ep_default_cluster() is implemented in main.c */
#define EP_INCLUDE_DECLARATIONS extern const wpan_cluster_table_entry_t custom_ep_clusters[];  \
                                int custom_ep_default_cluster(const wpan_envelope_t FAR *, void FAR *);

 /* This is a wpan_endpoint_table_entry_t structure, see its declaration in aps.h, the '{}' are because they
  * will be included in endpoints_table[] in endpoints.c */
#define ADDITIONAL_ENDPOINTS {CUSTOM_ENDPOINT, CUSTOM_EP_PROFILE, custom_ep_default_cluster, NULL, 0x0000, 0x00, custom_ep_clusters}, \
                             ZDO_ENDPOINT(zdo_ep_state)

 /* This macro is automatically defined if Process Incoming frames, Node Discovery Support or Over-the-Air
  * Firmware Update are enabled, otherwise it should be defined so the library handles frames */
#define ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES
