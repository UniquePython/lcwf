#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "private/server.h"

bool LCWF_GetServerFd(const char *address, uint16_t port, unsigned int backlog, unsigned int *outFd, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (address == NULL || outFd == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    *outFd = 0;

    if (backlog > INT_MAX)
    {
        LCWF_SetStatus(LCWF_STATUS_INVALID_PARAM, status);
        return false;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_SOCKET_FAILED, status);
        return false;
    }

    int enable = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_SOCKET_FAILED, status);
        goto cleanup;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    if (inet_pton(AF_INET, address, &addr.sin_addr) != 1)
    {
        LCWF_SetStatus(LCWF_STATUS_INVALID_ADDRESS, status);
        goto cleanup;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_SOCKET_FAILED, status);
        goto cleanup;
    }

    if (listen(fd, (int)backlog) < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_SOCKET_FAILED, status);
        goto cleanup;
    }

    *outFd = (unsigned int)fd;
    return true;

cleanup:
    close(fd);
    return false;
}

bool LCWF_AcceptClient(unsigned int serverFd, unsigned int *clientFd, LCWF_Status *status)
{
    LCWF_SetStatus(LCWF_STATUS_OK, status);

    if (clientFd == NULL)
    {
        LCWF_SetStatus(LCWF_STATUS_NULL_PARAM, status);
        return false;
    }

    int fd;
    do
    {
        fd = accept((int)serverFd, NULL, NULL);
    } while (fd < 0 && errno == EINTR);

    if (fd < 0)
    {
        LCWF_SetStatus(LCWF_STATUS_ACCEPT_FAILED, status);
        return false;
    }

    *clientFd = (unsigned int)fd;
    return true;
}
