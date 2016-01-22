#include <string.h>
#include <stdio.h>

#include "sendUDP.h"
#include "sendTCP.h"

//int sendUDP(void *);
int sendTCP(void *);


int main (int argc, char* argv[]){
        int n;
        char* ipAddr = argv[1];
	
	//strcpy(ipAddr,"192.168.1.4");
	/*
	n=sendUDP(ipAddr);
	
	if(n!=0){
		printf("UDP splat!\n");
	}*/

	n=sendTCP(ipAddr);
	//printf("n: %d\n",n);

	if(n!=0){
		printf("TCP splat!\n");
	}
	return 0;
}
