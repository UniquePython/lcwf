#ifndef LCWF_TRANSPORT_H_
#define LCWF_TRANSPORT_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "lcwf/status.h"

typedef struct LCWF_Transport LCWF_Transport;

bool LCWF_CreateTransport(LCWF_Transport **out, LCWF_Status *status);
void LCWF_DestroyTransport(LCWF_Transport **transport);

typedef bool (*LCWF_TransportReadFn)(void *, void *, size_t, size_t *, LCWF_Status *);
typedef bool (*LCWF_TransportWriteFn)(void *, const void *, size_t, size_t *, LCWF_Status *);

bool LCWF_RegisterTransportContext(LCWF_Transport *transport, void *context, LCWF_Status *status);
bool LCWF_RegisterTransportReadFn(LCWF_Transport *transport, LCWF_TransportReadFn const fn, LCWF_Status *status);
bool LCWF_RegisterTransportWriteFn(LCWF_Transport *transport, LCWF_TransportWriteFn const fn, LCWF_Status *status);

bool LCWF_TransportRead(LCWF_Transport *transport, void *destination, size_t maxLength, size_t *written, LCWF_Status *status);
bool LCWF_TransportWrite(LCWF_Transport *transport, const void *source, size_t length, size_t *written, LCWF_Status *status);
bool LCWF_TransportWriteAll(LCWF_Transport *transport, const void *source, size_t length, LCWF_Status *status);

#endif
