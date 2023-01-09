#ifndef __string_buffer_h
#define __string_buffer_h

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

typedef struct string_buffer
{
    object base;
    char *ptr;
    int len;
} string_buffer;

void string_buffer_init(string_buffer *obj);
void string_buffer_deinit(string_buffer *obj);
string_buffer *string_buffer_create();
void string_buffer_ncat(string_buffer *obj, const char *str, const int len);
void string_buffer_cat(string_buffer *obj, const char *str);
void string_buffer_cat_string_buffer(string_buffer *obj, const string_buffer *src);

#ifdef __cplusplus
}
#endif

#endif