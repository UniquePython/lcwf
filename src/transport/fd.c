#include <errno.h>
#include <limits.h>
#include <unistd.h>

#include "private/memory.h"
#include "private/transport/fd.h"

static bool LCWF_FdTransportReadFn(void *context, void *destination, size_t maxLength, size_t *written, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (context == NULL || (destination == NULL && maxLength > 0))
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    LCWF_FdTransport *transport = context;

    size_t request = maxLength;
    if (request > (size_t)SSIZE_MAX)
        request = (size_t)SSIZE_MAX;

    ssize_t result;

    do
    {
        result = read((int)transport->fd, destination, request);
    } while (result < 0 && errno == EINTR);

    if (result < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_READ_FAILED, status);
        return false;
    }

    if (written != NULL)
        *written = (size_t)result;

    return true;
}

static bool LCWF_FdTransportWriteFn(void *context, const void *source, size_t length, size_t *written, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (context == NULL || (source == NULL && length > 0))
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    LCWF_FdTransport *transport = context;

    size_t request = length;
    if (request > (size_t)SSIZE_MAX)
        request = (size_t)SSIZE_MAX;

    ssize_t result;

    do
    {
        result = write((int)transport->fd, source, request);
    } while (result < 0 && errno == EINTR);

    if (result < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_WRITE_FAILED, status);
        return false;
    }

    if (written != NULL)
        *written = (size_t)result;

    return true;
}

bool LCWF_CreateFdTransport(unsigned int fd, LCWF_FdTransport **out, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (out == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    LCWF_FdTransport *transport;
    if (!LCWF_AllocAuto(&transport))
    {
        LCWF_SetStatus(LCWF_STATUS_ALLOC_FAILED, status);
        return false;
    }

    transport->fd = fd;
    transport->transport = NULL;

    if (!LCWF_CreateTransport(&transport->transport, status))
    {
        LCWF_Dealloc(&transport);
        return false;
    }

    if (!LCWF_RegisterTransportContext(transport->transport, transport, status) ||
        !LCWF_RegisterTransportReadFn(transport->transport, LCWF_FdTransportReadFn, status) ||
        !LCWF_RegisterTransportWriteFn(transport->transport, LCWF_FdTransportWriteFn, status))
    {
        LCWF_DestroyTransport(&transport->transport);
        LCWF_Dealloc(&transport);
        return false;
    }

    *out = transport;
    return true;
}

void LCWF_DestroyFdTransport(LCWF_FdTransport **transport)
{
    if (transport == NULL || *transport == NULL)
        return;

    LCWF_DestroyTransport(&(*transport)->transport);
    LCWF_Dealloc(transport);
}

LCWF_Transport *LCWF_FdTransportGetTransport(LCWF_FdTransport *transport)
{
    if (transport == NULL)
        return NULL;

    return transport->transport;
}
