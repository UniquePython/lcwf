#ifndef PRIVATE_FD_TRANSPORT_H_
#define PRIVATE_FD_TRANSPORT_H_

#include "private/transport/transport.h"

typedef struct LCWF_FdTransport
{
    LCWF_Transport *transport;
    unsigned int fd;

} LCWF_FdTransport;

bool LCWF_CreateFdTransport(int fd, LCWF_FdTransport **out);
void LCWF_DestroyFdTransport(LCWF_FdTransport **transport);

LCWF_Transport *LCWF_FdTransportGetTransport(LCWF_FdTransport *transport);

#endif
