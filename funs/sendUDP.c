/*
 *  sendUDP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

#include "sendUDP.h"


/**
 *Sends UDP message to arg inet address
 *
 *returns:
 *	 0			no error
 *	-1			Error opening socket
 *	-2			Error in sending message
 */
int sendUDP(void* ipAddr, uint8_t* buf, size_t numBytes)
{
	int sock, n;
	socklen_t length;
	struct sockaddr_in remAddr;
	//unsigned char buffer[BUFSIZE];

	sock= socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
	{
	        printf("Socket error: %s\n", strerror(errno));
		//perror("Opening socket");
		return(-1);
	}

	remAddr.sin_family = AF_INET;
	remAddr.sin_addr.s_addr = inet_addr((char*)ipAddr);
	remAddr.sin_port = htons(SERVICE_PORT);
	length=sizeof(struct sockaddr_in);

	//printf("Please enter the message: ");

	//bzero(buffer,BUFSIZE);
	//fgets((char*)buffer,BUFSIZE-1,stdin);
	n=sendto(sock,buf,numBytes,0,(struct sockaddr *) &remAddr,length);
	if(n<0)
	{
	        printf("Send error: %s\n", strerror(errno));
	        //perror("Sending message");
		return(-2);
	}
	
	return 0;
}

