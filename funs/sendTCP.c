/*
 *  sendTCP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

#include "sendTCP.h"

/**
 *Sends TCP message to arg inet address
 *
 *returns:
 *	 0			no error
 *	-1			Error opening socket
 *	-2			Error locating host 
 *      -3                      Error connecting to host
 *      -4                      Error writing to socket
 *      -5                      Error reading from socket
 */
int sendTCP(void* arg, uint8_t* buf, size_t numBytes)
{
        int sockfd, n, s;
	char ack[ACKSIZE];
	struct sockaddr_in remAddr;
	struct hostent *remHost;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
	        printf("Socket error: %s\n", strerror(errno));
		//perror("ERROR opening socket");
                return(-1);
	}

        remHost = gethostbyname((char*)arg);
	if (remHost == NULL){
	        printf("Host error: %s\n", strerror(errno));
                //perror("ERROR, no such host");
		return(-2);	
	}

	bzero((char *) &remAddr, sizeof(remAddr));
	remAddr.sin_family = AF_INET;

	bcopy((char *) remHost->h_addr, (char*) &remAddr.sin_addr.s_addr,remHost->h_length);

	remAddr.sin_port = htons(SERVICE_PORT);

	s= connect(sockfd,(struct sockaddr*)&remAddr, sizeof(remAddr));
	if (s < 0){
	        printf("Connection error: %s\n", strerror(errno));
                return(-3);
	}

	//printf("Please enter message: ");
	//bzero(buffer, BUFSIZE);
        //fgets((char*)buffer, BUFSIZE-1, stdin);
	n = write(sockfd, buf, numBytes);
	if (n<0){
	        printf("Write error: %s\n", strerror(errno));
		//perror("ERROR writing to socket");
                return(-4);
	}

	bzero(ack, ACKSIZE);
	n = read(sockfd, ack, ACKSIZE-1);
	if (n < 0){
	        printf("Read error: %s\n", strerror(errno));
		//perror("ERROR reading from socket");
                return(-5);
	}
	
	printf("ACK:  %s\n", ack);
	
	return 0;
}	
