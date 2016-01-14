#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "sendUDP.h"
//void error(char *);

#define SERVICE_PORT	4547
#define BUFSIZE 41

void *sendUDP(void* arg)
{
	int sock, n;
	socklen_t length;
	struct sockaddr_in sendTo, from;
	struct hostent *hp;
	unsigned char buffer[BUFSIZE];

	/*if (argc !=3 )
	{	
		printf("Usage: server port\n");
		exit(1);
	}*/
		
	sock= socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
	{
		perror("Openeing socket");
		exit(1);
	}

	sendTo.sin_family = AF_INET;
	//hp = gethostbyname(argv[1]);
	sendTo.sin_addr.s_addr = inet_addr((char)&arg);
	/*if (hp==0)
	{
		error("Unknown host");
	}*/

	//bcopy((char *)hp->h_addr, (char *)&sendTo.sin_addr, hp->h_length);
	sendTo.sin_port = htons(SERVICE_PORT);
	length=sizeof(struct sockaddr_in);

	printf("Please enter the message: ");

	bzero(buffer,BUFSIZE);
	fgets(buffer,BUFSIZE-1,stdin);
	n=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *) &sendTo,length);
	if(n<0)
	{
		perror("Sending message")
		exit(2);
	}
	
	/*n=recvfrom(sock,buffer,256,0, (struct sockaddr *)&from,&length);
	if (n<0)
	{
		error("recvfrom");
	}
	write(1,"Got an ack: ",12);
	write(1,buffer,n);
	*/
}

