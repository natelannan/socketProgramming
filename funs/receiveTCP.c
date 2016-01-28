/*
 *  receiveTCP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERVICE_PORT 4547
#define BUFSIZE 5000

/**
 *Receives TCP message from any valid inet address
 *
 *returns:
 *	 0			No error
 *	-1			Error opening socket
 *	-2			Error in binding
 *      -3                      Error accepting connection
 *      -4                      Error reading from socket
 *      -5                      Error writing to socket
 */
int receiveTCP()
{
	int sockfd, newsockfd;
	socklen_t remAddrLen;
	char buffer[BUFSIZE];
	struct sockaddr_in myAddr, remAddr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) {
	        printf("Socket error: %s\n", strerror(errno));
		//perror("ERROR opening socket");
                return(-1);
	}

	bzero((char*) &myAddr, sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = INADDR_ANY;
	myAddr.sin_port = htons(SERVICE_PORT);
	
	if(bind(sockfd, (struct sockaddr *) &myAddr, sizeof(myAddr)) < 0){
	        printf("Bind error: %s\n", strerror(errno));
		//perror("ERROR on binding");
                return(-2);
	}

	listen(sockfd, 5);
	remAddrLen = sizeof(remAddr);

	newsockfd = accept(sockfd, (struct sockaddr *) &remAddr, &remAddrLen);

	if (newsockfd < 0){
	        printf("Accept error: %s\n", strerror(errno));
		//perror("ERROR on accept");
                return(-3);
	}

	bzero(buffer, BUFSIZE);
	
	n = read(newsockfd, buffer, BUFSIZE-1);

	if (n < 0){
	        printf("Read error: %s\n", strerror(errno));
		//perror("ERROR reading from socket");
                return(-4);
	}

	printf("Here is the message: %s\n", buffer);

	n = write(newsockfd, "I got your message",18);

	if (n < 0){
	        printf("Write error: %s\n", strerror(errno));
		//perror("ERROR writing to socket");
                return(-5);
	}	
	return 0;
} 
