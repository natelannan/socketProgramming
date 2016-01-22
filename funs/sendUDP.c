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

int sendUDP(void* arg)
{
	int sock, n;
	socklen_t length;
	struct sockaddr_in remAddr, myAddr;
	struct hostent *hp;
	unsigned char buffer[BUFSIZE];

	/*if (argc !=3 )
	{	
		printf("Usage: server port\n");
		return(1);
	}*/
		
	sock= socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
	{
		perror("Opening socket");
		return(-1);
	}

	remAddr.sin_family = AF_INET;
	//hp = gethostbyname(argv[1]);
	remAddr.sin_addr.s_addr = inet_addr((char*)arg);
	/*if (hp==0)
	{
		error("Unknown host");
	}*/

	//bcopy((char *)hp->h_addr, (char *)&remAddr.sin_addr, hp->h_length);
	remAddr.sin_port = htons(SERVICE_PORT);
	length=sizeof(struct sockaddr_in);

	printf("Please enter the message: ");

	bzero(buffer,BUFSIZE);
	fgets((char*)buffer,BUFSIZE-1,stdin);
	n=sendto(sock,buffer,strlen((char*)buffer),0,(struct sockaddr *) &remAddr,length);
	if(n<0)
	{
	        perror("Sending message");
		return(-2);
	}
	
	/*n=recvfrom(sock,buffer,256,0, (struct sockaddr *)&myAddr,&length);
	if (n<0)
	{
		error("recvfrom");
	}
	write(1,"Got an ack: ",12);
	write(1,buffer,n);
	*/
	return 0;
}

