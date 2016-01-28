/*
 *  sendTCP.c
 *
 *  Created on: Jan 14, 2016
 *      Author: Nate Lannan
 */

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
#define BUFSIZE 5000
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
int sendTCP(void* arg)
{
        int sockfd, n, s;
	char buffer[BUFSIZE];
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

	printf("Please enter message: ");
	bzero(buffer, BUFSIZE);
        fgets((char*)buffer, BUFSIZE-1, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if (n<0){
	        printf("Write error: %s\n", strerror(errno));
		//perror("ERROR writing to socket");
                return(-4);
	}

	bzero(buffer, BUFSIZE);
	n = read(sockfd, buffer, BUFSIZE-1);
	if (n < 0){
	        printf("Read error: %s\n", strerror(errno));
		//perror("ERROR reading from socket");
                return(-5);
	}
	
	printf("%s\n", buffer);
	
	return 0;
}	
