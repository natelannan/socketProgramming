#include <string.h>
#include <stdio.h>

#include "sendUDP.h"
#include "sendTCP.h"

int sendUDP(void *);
//int sendTCP(void *);


int main (){
        int n;
        char ipAddr[15];
	strcpy(ipAddr,"192.168.1.4");
	
	n=sendUDP(ipAddr);
	
	if(n!=0){
		printf("UDP splat!\n");
	}

	/*	n=sendTCP(ipAddr);

	if(n!=0){
		printf("TCP splat!\n");
		}*/
	return 0;
}
