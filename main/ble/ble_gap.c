#include "ble_gap.h"
#include <stdlib.h>

int BLE_GAP_EVENT_1;

typedef struct ble_gap_t
{
    ble_gap base;
} ble_gap_t;

static void ble_gap_t_init(ble_gap_t *obj);
static void ble_gap_t_deinit(ble_gap_t *obj);
static void ble_gap_t_dealloc(ble_gap_t *obj);

static void ble_gap_t_init(ble_gap_t *obj)
{
    object_init(&obj->base.base);
    obj->base.base.dealloc = (object_dealloc) ble_gap_t_dealloc;
}

static void ble_gap_t_deinit(ble_gap_t *obj)
{

}

static void ble_gap_t_dealloc(ble_gap_t *obj)
{
    ble_gap_t_deinit(obj);
    free(obj);
}

ble_gap *ble_gap_create()
{
    ble_gap_t *p = (ble_gap_t *)malloc(sizeof(ble_gap_t));
    ble_gap_t_init(p);

    return &p->base;
}