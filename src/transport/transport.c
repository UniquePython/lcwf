#include <limits.h>

#include "private/memory.h"
#include "private/transport/transport.h"

bool LCWF_CreateTransport(LCWF_Transport **out)
{
    if (out == NULL)
        return false;

    *out = NULL;

    LCWF_Transport *transport;
    if (!LCWF_Alloc(&transport))
        return false;

    transport->context = NULL;
    transport->read = NULL;
    transport->write = NULL;

    *out = transport;
    return true;
}

void LCWF_DestroyTransport(LCWF_Transport **transport)
{
    LCWF_Dealloc(transport);
}

bool LCWF_RegisterTransportContext(LCWF_Transport *transport, void *context)
{
    if (transport == NULL)
        return false;

    transport->context = context;
    return true;
}

bool LCWF_RegisterTransportReadFn(LCWF_Transport *transport, LCWF_TransportReadFn const fn)
{
    if (transport == NULL)
        return false;

    transport->read = fn;
    return true;
}

bool LCWF_RegisterTransportWriteFn(LCWF_Transport *transport, LCWF_TransportWriteFn const fn)
{
    if (transport == NULL)
        return false;

    transport->write = fn;
    return true;
}

ssize_t LCWF_TransportRead(LCWF_Transport *transport, void *destination, size_t maxLength)
{
    if (transport == NULL)
        return -2;

    if (transport->read == NULL)
        return -3;

    if (destination == NULL)
        return -4;

    return transport->read(transport->context, destination, maxLength);
}
ssize_t LCWF_TransportWrite(LCWF_Transport *transport, const void *source, size_t length)
{
    if (transport == NULL)
        return -2;

    if (transport->write == NULL)
        return -3;

    if (source == NULL)
        return -4;

    return transport->write(transport->context, source, length);
}

ssize_t LCWF_TransportWriteAll(LCWF_Transport *transport, const void *source, size_t length)
{
    if (transport == NULL)
        return -2;

    if (transport->write == NULL)
        return -3;

    if (source == NULL)
        return -4;

    if (length > (size_t)SSIZE_MAX)
        return -5;

    size_t totalWritten = 0;

    while (totalWritten < length)
    {
        ssize_t written = LCWF_TransportWrite(transport, (const unsigned char *)source + totalWritten, length - totalWritten);

        if (written < 0)
            return totalWritten > 0 ? (ssize_t)totalWritten : written;

        if (written == 0)
            return totalWritten > 0 ? (ssize_t)totalWritten : -5;

        totalWritten += (size_t)written;
    }

    return (ssize_t)totalWritten;
}
