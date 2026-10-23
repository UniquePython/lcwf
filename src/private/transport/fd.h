#ifndef PRIVATE_FD_TRANSPORT_H_
#define PRIVATE_FD_TRANSPORT_H_

#include "private/status.h"
#include "private/transport/transport.h"

typedef struct LCWF_FdTransport
{
    LCWF_Transport *transport;
    unsigned int fd;

} LCWF_FdTransport;

bool LCWF_CreateFdTransport(unsigned int fd, LCWF_FdTransport **out, LCWF_Status *status);
void LCWF_DestroyFdTransport(LCWF_FdTransport **transport);

LCWF_Transport *LCWF_FdTransportGetTransport(LCWF_FdTransport *transport);

#endif
