#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVICE_PORT 4547
#define BUFSIZE 5000

int sendTCP(void* arg)
{
	int sockfd, portno, n;
	char buffer[BUFSIZE];
	struct sockaddr_in remAddr;
	struct hostent *remHost;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
                exit(-1);
	}

        remHost = gethostbyname((char*)arg);
	if (remHost == NULL){
                perror("ERROR, no such host");
		exit(-2);	
	}

	bzero((char *) &remAddr, sizeof(remAddr));
	remAddr.sin_family = AF_INET;

	bcopy((char *) remHost->h_addr, (char*) &remAddr.sin_addr.s_addr,remHost->h_length);

	remAddr.sin_port = htons(SERVICE_PORT);

	if (connect(sockfd,(struct sockaddr*)&remAddr, sizeof(remAddr)) < 0){
		perror("ERROR connecting");
                exit(-3);
	}

	printf("Please enter message: ");
	bzero(buffer, BUFSIZE);
        fgets((char*)buffer, BUFSIZE-1, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if (n<0){
		perror("ERROR writing to socket");
                exit(-4);
	}

	bzero(buffer, BUFSIZE);
	n = read(sockfd, buffer, BUFSIZE-1);
	if (n < 0){
		perror("ERROR reading from socket");
                exit(-5);
	}
	
	printf("%s\n", buffer);
	
	return 0;
}	
