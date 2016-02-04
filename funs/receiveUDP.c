/*
 *  receiveUDP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

#include "receiveUDP.h"

/**
 *Receives UDP messages from any valid inet address
 *
 *returns:
 *	 0			No error
 *	-1			Error opening socket
 *	-2			Error in binding
 *      -3                      Error receiving message
 */
int receiveUDP(uint8_t* buf, size_t numBytes)
{
        int sock, length, n, i;
	socklen_t remAddrLen;
	struct sockaddr_in myAddr;
	struct sockaddr_in remAddr;
	//unsigned char buffer[BUFSIZE];

	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock <0)
	{
	        printf("Socket error: %s\n", strerror(errno));
		//perror("Opening socket");
                return(-1);
	}
	length = sizeof(myAddr);
	bzero(&myAddr,length);
	myAddr.sin_family=AF_INET;
	myAddr.sin_addr.s_addr=INADDR_ANY;
        myAddr.sin_port=htons(SERVICE_PORT);
	if (bind(sock,(struct sockaddr *)&myAddr,length)<0)
	{
	        printf("Bind error: %s\n", strerror(errno));
		//perror("binding");
                return(-2);
	}
	remAddrLen=sizeof(struct sockaddr_in);

	while(1)
	{
		n = recvfrom(sock,buf,numBytes,0,(struct sockaddr *)&remAddr,&remAddrLen);
		if (n<0)
		{		  
	                printf("Receive error: %s\n", strerror(errno));
		        //perror("recvfrom");
                        return(-3);
		}
		//write(1,"Received a datagram: ",21);
		//write(1,buf,n);
		printf("Contents of buffer: \n");
		for (i=0; i<numBytes; i++)
	                printf("\tbuf[%d]: %2x\n", i, buf[i]);
	}
        return 0;
}
