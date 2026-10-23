#ifndef LCWF_LISTENER_H_
#define LCWF_LISTENER_H_

#include <stdbool.h>
#include <stdint.h>

bool LCWF_GetServerFd(const char *address, uint16_t port, unsigned int backlog, unsigned int *outFd);

#endif
