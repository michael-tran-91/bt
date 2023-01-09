#ifndef __object_h
#define __object_h

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*object_dealloc)(void *);

typedef struct object
{
    volatile int cnt;
    object_dealloc dealloc;
} object;

void object_init(object *obj);
void retain(object *obj);
void release(object *obj);

#ifdef __cplusplus
}
#endif

#endif