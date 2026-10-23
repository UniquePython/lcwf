#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "lcwf/server.h"

bool LCWF_GetServerFd(const char *address, uint16_t port, unsigned int backlog, unsigned int *outFd)
{
    if (address == NULL || outFd == NULL)
        return false;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        return false;

    int enable = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
        goto cleanup;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    if (inet_pton(AF_INET, address, &addr.sin_addr) != 1)
        goto cleanup;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
        goto cleanup;

    if (listen(fd, (int)backlog) != 0)
        goto cleanup;

    *outFd = (unsigned int)fd;
    return true;

cleanup:
    close(fd);
    return false;
}
