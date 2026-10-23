#ifndef LCWF_TRANSPORT_H_
#define LCWF_TRANSPORT_H_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef struct LCWF_Transport LCWF_Transport;

bool LCWF_CreateTransport(LCWF_Transport **out);
void LCWF_DestroyTransport(LCWF_Transport **transport);

typedef ssize_t (*LCWF_TransportReadFn)(void *, void *, size_t);
typedef ssize_t (*LCWF_TransportWriteFn)(void *, const void *, size_t);

bool LCWF_RegisterTransportContext(LCWF_Transport *transport, void *context);
bool LCWF_RegisterTransportReadFn(LCWF_Transport *transport, LCWF_TransportReadFn const fn);
bool LCWF_RegisterTransportWriteFn(LCWF_Transport *transport, LCWF_TransportWriteFn const fn);

ssize_t LCWF_TransportRead(LCWF_Transport *transport, void *destination, size_t maxLength);
ssize_t LCWF_TransportWrite(LCWF_Transport *transport, const void *source, size_t length);
ssize_t LCWF_TransportWriteAll(LCWF_Transport *transport, const void *source, size_t length);

#endif
