#include "string_buffer.h"
#include <stdlib.h>
#include <string.h>

static void string_buffer_dealloc(string_buffer *obj);

void string_buffer_init(string_buffer *obj)
{
    object_init(&obj->base);
    obj->base.dealloc = (object_dealloc)string_buffer_dealloc;
    obj->ptr = malloc(1);
    obj->len = 0;
}

void string_buffer_deinit(string_buffer *obj)
{
    if (obj->ptr) {
        free(obj->ptr);
        obj->ptr = NULL;
    }
    obj->len = 0;
}

string_buffer *string_buffer_create()
{
    string_buffer *obj = malloc(sizeof(string_buffer));
    string_buffer_init(obj);
    return obj;
}

static void string_buffer_dealloc(string_buffer *obj)
{
    string_buffer_deinit(obj);
    free(obj);
}

void string_buffer_ncat(string_buffer *obj, const char *str, const int len)
{
    if (len == 0) return;

    char *ptr = realloc(obj->ptr, obj->len + len + 1);
    if (ptr) {
        obj->ptr = ptr;
        memcpy(obj->ptr + obj->len, str, len);
        obj->len += len;
        obj->ptr[obj->len] = '\0';
    }
}

void string_buffer_cat(string_buffer *obj, const char *str)
{
    string_buffer_ncat(obj, str, strlen(str));
}

void string_buffer_cat_string_buffer(string_buffer *obj, const string_buffer *src)
{
    string_buffer_ncat(obj, src->ptr, src->len);
}