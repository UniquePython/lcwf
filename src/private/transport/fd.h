#ifndef PRIVATE_TRANSPORT_FD_TRANSPORT_H_
#define PRIVATE_TRANSPORT_FD_TRANSPORT_H_

#include "lcwf/transport/fd.h"
#include "private/transport/transport.h"

struct LCWF_FdTransport
{
    LCWF_Transport *transport;
    unsigned int fd;
};

#endif
