#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVICE_PORT 4547
#define BUFSIZE 5000

int receiveUDP(void* arg)
{
	int sock, length, n;
	socklen_t remAddrlen;
	struct sockaddr_in myAddr;
	struct sockaddr_in remAddr;
	unsigned char buffer[BUFSIZE];

	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock <0)
	{
		perror("Opening socket");
                exit(-1);
	}
	
	length = sizeof(myAddr);
	bzero(&myAddr,length);
	myAddr.sin_family=AF_INET;
	myAddr.sin_addr.s_addr=INADDR_ANY;
	myAddr.sin_port=htons(atoi(argv[1]));
	if (bind(sock,(struct sockaddr *)&myAddr,length)<0)
	{
		perror("binding");
                exit(-2);
	}
	remAddrlen=sizeof(struct sockaddr_in);

	while(1)
	{
		n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&remAddr,&remAddrlen);
		if (n<0)
		{
			perror("recvfrom");
                        exit(-3);
		}
		write(1,"Received a datagram: ",21);
		write(1,buffer,n);
/*n= sendto(sock, "Got your message\n",17,0,(struct sockaddr *)&remAddr,remAddrlen);
		if(n<0)
		{
			error("sendto");
			}*/
	}
        return 0;
}
