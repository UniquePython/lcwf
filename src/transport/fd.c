#include <unistd.h>

#include "private/memory.h"
#include "private/transport/fd.h"

static ssize_t LCWF_FdTransportReadFn(void *context, void *destination, size_t maxLength)
{
    LCWF_FdTransport *transport = context;
    return read((int)transport->fd, destination, maxLength);
}

static ssize_t LCWF_FdTransportWriteFn(void *context, const void *source, size_t length)
{
    LCWF_FdTransport *transport = context;
    return write((int)transport->fd, source, length);
}

bool LCWF_CreateFdTransport(int fd, LCWF_FdTransport **out)
{
    if (fd < 0 || out == NULL)
        return false;

    *out = NULL;

    LCWF_FdTransport *transport;
    if (!LCWF_Alloc(&transport))
        return false;

    transport->fd = (unsigned int)fd;
    transport->transport = NULL;

    if (!LCWF_CreateTransport(&transport->transport))
    {
        LCWF_Dealloc(&transport);
        return false;
    }

    if (!LCWF_RegisterTransportContext(transport->transport, transport) ||
        !LCWF_RegisterTransportReadFn(transport->transport, LCWF_FdTransportReadFn) ||
        !LCWF_RegisterTransportWriteFn(transport->transport, LCWF_FdTransportWriteFn))
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
