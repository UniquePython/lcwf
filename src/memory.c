#include "private/memory.h"

#include <stdlib.h>

bool LCWF_AllocImpl(size_t size, void **out)
{
    if (size == 0 || out == NULL)
        return false;

    void *ptr = malloc(size);
    if (ptr == NULL)
        return false;

    *out = ptr;
    return true;
}

bool LCWF_ReallocImpl(size_t size, void **out)
{
    if (out == NULL)
        return false;

    if (size == 0)
    {
        LCWF_DeallocImpl(out);
        return true;
    }

    void *ptr = realloc(*out, size);
    if (ptr == NULL)
        return false;

    *out = ptr;
    return true;
}

void LCWF_DeallocImpl(void **ptr)
{
    if (ptr == NULL || *ptr == NULL)
        return;

    free(*ptr);
    *ptr = NULL;
}
