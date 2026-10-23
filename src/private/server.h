#ifndef PRIVATE_SERVER_H_
#define PRIVATE_SERVER_H_

#include <stdbool.h>
#include <stdint.h>

bool LCWF_GetServerFd(const char *address, uint16_t port, unsigned int backlog, unsigned int *outFd);

#endif
