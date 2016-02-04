#ifndef RECEIVEUDP_H
#define RECEIVEUDP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERVICE_PORT 4547


int receiveUDP(uint8_t*, size_t);

#endif
