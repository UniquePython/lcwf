#ifndef PRIVATE_BUFFER_H_
#define PRIVATE_BUFFER_H_

#include <stdbool.h>
#include <stddef.h>

#include "lcwf/status.h"

typedef struct LCWF_Buffer
{
    char *contents;
    size_t size;
    size_t capacity;

} LCWF_Buffer;

bool LCWF_BufferCreate(size_t initialCapacity, LCWF_Buffer *out, LCWF_Status *status);
void LCWF_BufferDestroy(LCWF_Buffer *buffer);

bool LCWF_BufferClear(LCWF_Buffer *buffer, LCWF_Status *status);

bool LCWF_BufferAppend(LCWF_Buffer *buffer, const char *data, size_t length, LCWF_Status *status);
bool LCWF_BufferAppendCstr(LCWF_Buffer *buffer, const char *text, LCWF_Status *status);

#endif
