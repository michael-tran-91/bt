#ifndef __array_h
#define __array_h

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

typedef struct array
{
    object base;
    object **ptr;
    int len;
} array;

void array_init(array *p);
void array_deinit(array *p);
array *array_create();
void array_push_back(array *p, object *obj);
object *array_get(array *p, int index);
void array_remove_index(array *p, int index);

#ifdef __cplusplus
}
#endif

#endif