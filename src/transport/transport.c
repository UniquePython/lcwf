#include "private/memory.h"
#include "private/status.h"
#include "private/transport/transport.h"

bool LCWF_CreateTransport(LCWF_Transport **out, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (out == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    LCWF_Transport *transport;
    if (!LCWF_AllocAuto(&transport))
    {
        LCWF_SetStatus(LCWF_STATUS_ALLOC_FAILED, status);
        return false;
    }

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

bool LCWF_RegisterTransportContext(LCWF_Transport *transport, void *context, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    transport->context = context;
    return true;
}

bool LCWF_RegisterTransportReadFn(LCWF_Transport *transport, LCWF_TransportReadFn const fn, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    transport->read = fn;
    return true;
}

bool LCWF_RegisterTransportWriteFn(LCWF_Transport *transport, LCWF_TransportWriteFn const fn, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    transport->write = fn;
    return true;
}

bool LCWF_TransportRead(LCWF_Transport *transport, void *destination, size_t maxLength, size_t *written, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL || destination == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (transport->read == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_CALLABLE, status);
        return false;
    }

    return transport->read(transport->context, destination, maxLength, written, status);
}

bool LCWF_TransportWrite(LCWF_Transport *transport, const void *source, size_t length, size_t *written, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL || (source == NULL && length > 0))
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (transport->write == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_CALLABLE, status);
        return false;
    }

    return transport->write(transport->context, source, length, written, status);
}

bool LCWF_TransportWriteAll(LCWF_Transport *transport, const void *source, size_t length, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (transport == NULL || (source == NULL && length > 0))
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    if (transport->write == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_CALLABLE, status);
        return false;
    }

    size_t totalWritten = 0;

    while (totalWritten < length)
    {
        size_t written = 0;

        if (!LCWF_TransportWrite(transport, (const unsigned char *)source + totalWritten, length - totalWritten, &written, status))
            return false;

        if (written == 0 || written > length - totalWritten)
        {
            LCWF_SetStatus(LCWF_STATUS_WRITE_FAILED, status);
            return false;
        }

        totalWritten += written;
    }

    return true;
}
