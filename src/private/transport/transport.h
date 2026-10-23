#ifndef PRIVATE_TRANSPORT_TRANSPORT_H_
#define PRIVATE_TRANSPORT_TRANSPORT_H_

#include "lcwf/transport/transport.h"

struct LCWF_Transport
{
    void *context;

    LCWF_TransportReadFn read;
    LCWF_TransportWriteFn write;
};

#endif
