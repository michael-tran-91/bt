#ifndef __ble_gap_h
#define __ble_gap_h

#ifdef __cplusplus
extern "C" {
#endif

#include <merry/object/object.h>

typedef struct ble_gap
{
    object base;

    void(*handle)();
} ble_gap;

#ifdef __cplusplus
}
#endif

#endif