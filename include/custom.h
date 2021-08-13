/*
 *
 * Write here your custom declarations.
 *
 * They will be included automatically in
 * the project.
 *
 */
 
/* Additional XBee settings for SmartThings compatibility */
#define XBEE_PARAM_ZS       2
#define XBEE_PARAM_NJ       0xFF
#define XBEE_PARAM_NH       0x1E
#define XBEE_PARAM_NO       0
#define XBEE_PARAM_AP       1
#define XBEE_PARAM_EE       1
#define XBEE_PARAM_EO       1
#define XBEE_PARAM_KY       "5A6967426565416C6C69616E63653039"

/* Reported manufacturer and model in basic cluster
 *
 * For SmartThings local execution without custom device handler, set the following:
 * - ZCL_MANUFACTURER "Leviton"
 * - ZCL_MODEL        "ZSS-10"
 */
#define ZCL_MANUFACTURER    "PXBee"
#define ZCL_MODEL           "Trigger"

/* Ignore On command received via Broadcast message */
#define PXBEE_TRIGGER_IGNORE_BROADCAST

/* How long a relay should be activated upon trigger (in microseconds) */
#define RELAY_TIMER         125000

/* Status Interval Timer (in microseconds) - 4 seconds */
#define STATUS_TIMER        4000000

/* Status Oscillation count before setting state operating (Counting both slopes) */
#define STATUS_OSC_COUNT    4

/* Settings END */
 
#include <zigbee/zdo.h>
#include <zigbee/zcl_client.h>

extern wpan_ep_state_t zdo_ep_state;
extern wpan_ep_state_t custom_ha_ep_state;
extern wpan_ep_state_t custom_ha_ep2_state;
extern wpan_ep_state_t custom_ha_ep3_state;
extern wpan_ep_state_t custom_ha_ep4_state;
extern wpan_ep_state_t custom_ha_ep5_state;

#define CUSTOM_ENDPOINT     0xEA
#define CUSTOM_ENDPOINT2    0xEB
#define CUSTOM_ENDPOINT3    0xEC
#define CUSTOM_ENDPOINT4    0xED
#define CUSTOM_ENDPOINT5    0xEE
#define CUSTOM_EP_PROFILE   0x0104

 /* With this macro the prototypes of clusters' callbacks and extern variables are included in endpoints.c
  * Array custom_ep_data_clusters[] is declared in main.c
  * Function custom_ep_basic_cluster() is implemented in main.c */
#define EP_INCLUDE_DECLARATIONS extern const wpan_cluster_table_entry_t custom_ep_clusters[];  \
                                extern const wpan_cluster_table_entry_t custom_ep2_clusters[]; \
                                extern const wpan_cluster_table_entry_t custom_ep3_clusters[]; \
                                extern const wpan_cluster_table_entry_t custom_ep4_clusters[]; \
                                extern const wpan_cluster_table_entry_t custom_ep5_clusters[]; \
                                int custom_ep_basic_cluster(const wpan_envelope_t FAR *, void FAR *);

 /* This is a wpan_endpoint_table_entry_t structure, see its declaration in aps.h, the '{}' are because they
  * will be included in endpoints_table[] in endpoints.c */
#define ADDITIONAL_ENDPOINTS {CUSTOM_ENDPOINT, CUSTOM_EP_PROFILE, custom_ep_basic_cluster, &custom_ha_ep_state, 0x0002, 0x00, custom_ep_clusters}, \
                             {CUSTOM_ENDPOINT2, CUSTOM_EP_PROFILE, custom_ep_basic_cluster, &custom_ha_ep2_state, 0x0002, 0x00, custom_ep2_clusters}, \
                             {CUSTOM_ENDPOINT3, CUSTOM_EP_PROFILE, custom_ep_basic_cluster, &custom_ha_ep3_state, 0x0002, 0x00, custom_ep3_clusters}, \
                             {CUSTOM_ENDPOINT4, CUSTOM_EP_PROFILE, custom_ep_basic_cluster, &custom_ha_ep4_state, 0x0002, 0x00, custom_ep4_clusters}, \
                             {CUSTOM_ENDPOINT5, CUSTOM_EP_PROFILE, custom_ep_basic_cluster, &custom_ha_ep5_state, 0x0002, 0x00, custom_ep5_clusters}, \
                             ZDO_ENDPOINT(zdo_ep_state)

 /* This macro is automatically defined if Process Incoming frames, Node Discovery Support or Over-the-Air
  * Firmware Update are enabled, otherwise it should be defined so the library handles frames */
#define ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES
