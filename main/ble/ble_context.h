#ifndef __ble_context_h
#define __ble_context_h

#ifdef __cplusplus
extern "C" {
#endif

#include <merry/object/object.h>

typedef struct ble_context
{
    object base;

    void (*setup)(struct ble_context *obj);

} ble_context;

ble_context *ble_context_create();

#ifdef __cplusplus
}
#endif

#endif