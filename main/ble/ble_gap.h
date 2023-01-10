#ifndef __ble_gap_h
#define __ble_gap_h

#ifdef __cplusplus
extern "C" {
#endif

#include <merry/object/object.h>

extern int BLE_GAP_EVENT_1;

typedef struct ble_event_set_adv_data_complete
{
    ble_event base;
} ble_event_set_adv_data_complete;

typedef struct ble_gap
{
    object base;
} ble_gap;

ble_gap *ble_gap_create();

#ifdef __cplusplus
}
#endif

#endif