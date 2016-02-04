#ifndef SENDTCP_H
#define SENDTCP_H


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERVICE_PORT 4547
#define ACKSIZE 80

int sendTCP(void *arg, uint8_t*, size_t);

#endif
