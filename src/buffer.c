#include <stdint.h>
#include <string.h>

#include "private/buffer.h"
#include "private/memory.h"
#include "private/status.h"

#define LCWF_DEFAULT_INITIAL_CAPACITY 8

bool LCWF_BufferCreate(size_t initialCapacity, LCWF_Buffer *out, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (out == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    size_t capacity = initialCapacity == 0 ? LCWF_DEFAULT_INITIAL_CAPACITY : initialCapacity;

    if (!LCWF_Alloc(capacity, &out->contents))
    {
        LCWF_SetStatus(LCWF_STATUS_ALLOC_FAILED, status);
        return false;
    }

    out->size = 0;
    out->capacity = capacity;

    return true;
}

void LCWF_BufferDestroy(LCWF_Buffer *buffer)
{
    if (buffer == NULL)
        return;

    LCWF_Dealloc(&buffer->contents);
    buffer->size = 0;
    buffer->capacity = 0;
}

bool LCWF_BufferClear(LCWF_Buffer *buffer, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (buffer == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    buffer->size = 0;

    return true;
}

bool LCWF_BufferAppend(LCWF_Buffer *buffer, const char *data, size_t length, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (buffer == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (length == 0)
        return true;

    if (data == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (buffer->size > SIZE_MAX - length)
    {
        LCWF_SetStatus(LCWF_STATUS_OVERFLOW, status);
        return false;
    }

    size_t requiredCapacity = buffer->size + length;

    if (requiredCapacity > buffer->capacity)
    {
        size_t newCapacity = buffer->capacity;

        if (newCapacity == 0)
            newCapacity = LCWF_DEFAULT_INITIAL_CAPACITY;

        while (newCapacity < requiredCapacity)
        {
            if (newCapacity > SIZE_MAX / 2)
            {
                newCapacity = requiredCapacity;
                break;
            }

            newCapacity *= 2;
        }

        if (!LCWF_Realloc(newCapacity, &buffer->contents))
        {
            LCWF_SetStatus(LCWF_STATUS_ALLOC_FAILED, status);
            return false;
        }

        buffer->capacity = newCapacity;
    }

    memcpy(buffer->contents + buffer->size, data, length);
    buffer->size = requiredCapacity;

    return true;
}

bool LCWF_BufferAppendCstr(LCWF_Buffer *buffer, const char *text, LCWF_Status *status)
{
    if (text == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    return LCWF_BufferAppend(buffer, text, strlen(text), status);
}
