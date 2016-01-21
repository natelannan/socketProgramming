#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVICE_PORT 4547
#define BUFSIZE 5000

int receiveTCP()
{
	int sockfd, newsockfd, portno;
	socklen_t remAddrLen;
	char buffer[BUFSIZE];
	struct sockaddr_in myAddr, remAddr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) {
		perror("ERROR opening socket");
                exit(-1);
	}

	bzero((char*) &myAddr, sizeof(myAddr));
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = INADDR_ANY;
	myAddr.sin_port = htons(SERVICE_PORT);
	
	if(bind(sockfd, (struct sockaddr *) &myAddr, sizeof(myAddr)) < 0){
		perror("ERROR on binding");
                exit(-2);
	}

	listen(sockfd, 5);
	remAddrLen = sizeof(remAddr);

	newsockfd = accept(sockfd, (struct sockaddr *) &remAddr, &remAddrLen);

	if (newsockfd < 0){
		perror("ERROR on accept");
                exit(-3);
	}

	bzero(buffer, BUFSIZE);
	
	n = read(newsockfd, buffer, BUFSIZE-1);

	if (n < 0){
		perror("ERROR reading from socket");
                exit(-4);
	}

	printf("Here is the message: %s\n", buffer);

	n = write(newsockfd, "I got your message",18);

	if (n < 0){
		perror("ERROR writing to socket");
                exit(-5);
	}	
	return 0;
} 
