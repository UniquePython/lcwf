#ifndef LCWF_TRANSPORT_FD_TRANSPORT_H_
#define LCWF_TRANSPORT_FD_TRANSPORT_H_

#include <stdbool.h>

#include "lcwf/transport/transport.h"

typedef struct LCWF_FdTransport LCWF_FdTransport;

bool LCWF_CreateFdTransport(int fd, LCWF_FdTransport **out);
void LCWF_DestroyFdTransport(LCWF_FdTransport **transport);

LCWF_Transport *LCWF_FdTransportGetTransport(LCWF_FdTransport *transport);

#endif
