#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "receiveUDP.h"
#include "receiveTCP.h"


#define BUFSIZE 10

//int receiveUDP(uint8_t*, size_t);
//int receiveTCP();

int main (int argc, char* argv[]){
        int n;
        int udp = 1;
	uint8_t buf[BUFSIZE];
	if (argc == 2){
	     udp = 0;
	}
	if(udp){
	     printf("UDP\n");	
	     n=receiveUDP(buf, sizeof(buf));
	     if(n!=0){
	          printf("receiveUDP error %d\n", n);
	     }
        }
        else{
	     printf("TCP\n");
	     n=receiveTCP(buf, sizeof(buf));

	     if(n!=0){
	          printf("receiveTCP error %d\n", n);
	     }
	}
	return 0;
}
