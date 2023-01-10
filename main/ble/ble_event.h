#ifndef __ble_event_h
#define __ble_event_h

#ifdef __cplusplus
extern "C" {
#endif

#include <merry/object/object.h>

typedef struct ble_event
{
    object base;
    void *(*type)(struct ble_event *obj);
} ble_event;

#ifdef __cplusplus
}
#endif

#endif