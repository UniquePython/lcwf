#ifndef LCWF_TRANSPORT_H_
#define LCWF_TRANSPORT_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "lcwf/status.h"

typedef struct LCWF_Transport LCWF_Transport;

bool LCWF_CreateTransport(LCWF_Transport **out, LCWF_Status *status);
#define LCWF_CreateTransportSimple(out) LCWF_CreateTransport((out), NULL)

void LCWF_DestroyTransport(LCWF_Transport **transport);

typedef bool (*LCWF_TransportReadFn)(void *, void *, size_t, size_t *, LCWF_Status *);
typedef bool (*LCWF_TransportWriteFn)(void *, const void *, size_t, size_t *, LCWF_Status *);

bool LCWF_RegisterTransportContext(LCWF_Transport *transport, void *context, LCWF_Status *status);
#define LCWF_RegisterTransportContextSimple(transport, context) LCWF_RegisterTransportContext((transport), (context), NULL)

bool LCWF_RegisterTransportReadFn(LCWF_Transport *transport, LCWF_TransportReadFn const fn, LCWF_Status *status);
#define LCWF_RegisterTransportReadFnSimple(transport, fn) LCWF_RegisterTransportReadFn((transport), (fn), NULL)

bool LCWF_RegisterTransportWriteFn(LCWF_Transport *transport, LCWF_TransportWriteFn const fn, LCWF_Status *status);
#define LCWF_RegisterTransportWriteFnSimple(transport, fn) LCWF_RegisterTransportWriteFn((transport), (fn), NULL)

bool LCWF_TransportRead(LCWF_Transport *transport, void *destination, size_t maxLength, size_t *written, LCWF_Status *status);
#define LCWF_TransportReadSimple(transport, destination, maxLength, written) LCWF_TransportRead((transport), (destination), (maxLength), (written), NULL)

bool LCWF_TransportWrite(LCWF_Transport *transport, const void *source, size_t length, size_t *written, LCWF_Status *status);
#define LCWF_TransportWriteSimple(transport, source, length, written) LCWF_TransportWrite((transport), (source), (length), (written), NULL)

bool LCWF_TransportWriteAll(LCWF_Transport *transport, const void *source, size_t length, LCWF_Status *status);
#define LCWF_TransportWriteAllSimple(transport, source, length) LCWF_TransportWriteAll((transport), (source), (length), NULL)

#endif
