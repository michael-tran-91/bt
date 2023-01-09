#include "object.h"
#include <stdlib.h>

void object_init(object *obj)
{
    obj->cnt = 1;
    obj->dealloc = NULL;
}

void retain(object *obj)
{
    __sync_fetch_and_add(&obj->cnt, 1);
}

void release(object *obj)
{
    int c = __sync_fetch_and_sub(&obj->cnt, 1);
    if (c == 1) {
        if (obj->dealloc) obj->dealloc((void *)obj);
    }
}