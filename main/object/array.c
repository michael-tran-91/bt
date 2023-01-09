#include "array.h"
#include <stdlib.h>
#include <string.h>

static void array_dealloc(array *p);

void array_init(array *p)
{
    object_init(&p->base);
    p->base.dealloc = (object_dealloc)array_dealloc;
    p->ptr = NULL;
    p->len = 0;
}

void array_deinit(array *p)
{
    for (int i = 0; i < p->len; ++i) {
        release(p->ptr[i]);
    }
    if (p->ptr) {
        free(p->ptr);
        p->ptr = NULL;
    }
    p->len = 0;
}

array *array_create()
{
    array *p = (array *)malloc(sizeof(array));
    array_init(p);
    return p;
}

void array_dealloc(array *p)
{
    array_deinit(p);
    free(p);
}

void array_push_back(array *p, object *obj)
{
    object **ptr = realloc(p->ptr, sizeof(object *) * (p->len + 1));
    if (ptr) {
        p->ptr = ptr;
        p->ptr[p->len] = obj;
        p->len++;
        retain(obj);
    }
}

object *array_get(array *p, int index)
{
    if (index < 0 || index >= p->len) return NULL;
    return p->ptr[index];
}

void array_remove_index(array *p, int index)
{
    if (index < 0 || index >= p->len) return;

    object *o = p->ptr[index];
    p->ptr[index] = p->ptr[p->len - 1];
    p->len--;
    release(o);
}