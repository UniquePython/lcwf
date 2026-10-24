#ifndef PRIVATE_SERVER_H_
#define PRIVATE_SERVER_H_

#include <stdbool.h>
#include <stdint.h>

#include "private/status.h"

bool LCWF_GetServerFd(const char *address, uint16_t port, unsigned int backlog, unsigned int *outFd, LCWF_Status *status);
bool LCWF_AcceptClient(unsigned int serverFd, unsigned int *clientFd, LCWF_Status *status);

#endif
