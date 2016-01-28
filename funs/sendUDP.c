/*
 *  sendUDP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "sendUDP.h"


#define SERVICE_PORT	4547
#define BUFSIZE 41

/**
 *Sends UDP message to arg inet address
 *
 *returns:
 *	 0			no error
 *	-1			Error opening socket
 *	-2			Error in sending message
 */
int sendUDP(void* arg)
{
	int sock, n;
	socklen_t length;
	struct sockaddr_in remAddr;
	unsigned char buffer[BUFSIZE];

	sock= socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
	{
	        printf("Socket error: %s\n", strerror(errno));
		//perror("Opening socket");
		return(-1);
	}

	remAddr.sin_family = AF_INET;
	remAddr.sin_addr.s_addr = inet_addr((char*)arg);
	remAddr.sin_port = htons(SERVICE_PORT);
	length=sizeof(struct sockaddr_in);

	printf("Please enter the message: ");

	bzero(buffer,BUFSIZE);
	fgets((char*)buffer,BUFSIZE-1,stdin);
	n=sendto(sock,buffer,strlen((char*)buffer),0,(struct sockaddr *) &remAddr,length);
	if(n<0)
	{
	        printf("Send error: %s\n", strerror(errno));
	        //perror("Sending message");
		return(-2);
	}
	
	return 0;
}

