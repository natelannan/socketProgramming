#ifndef RECEIVETCP_H
#define RECEIVETCP_H


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERVICE_PORT 4547

int receiveTCP(uint8_t*,size_t);

#endif
