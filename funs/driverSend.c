#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "sendUDP.h"
#include "sendTCP.h"

#define BUFSIZE 10

//int sendUDP(void *, uint8_t*, size_t);
//int sendTCP(void *);


int main (int argc, char* argv[]){
        int n, i;
        int udp = 1;
	uint8_t buf[BUFSIZE];

	
        if (argc < 2){
              printf("Usage:  driverSend <ip address> -t\n");
	      printf("\tip address:  ipv4 address of device to send message to\n");
              printf("\t-t:  option for tcp mode\n"); 
	      return 0;
	}
        char* ipAddr = argv[1];
        if (argc == 3){
              udp = 0;
        }
	
	for (i=0; i<BUFSIZE; i++)
	      buf[i] = i+160;
        if(udp){
              printf("UDP\n");
	      n=sendUDP(ipAddr, buf, sizeof(buf));
	      if(n!=0){
                   printf("sendUDP error %d\n", n);
	      }
        }

	else {
              printf("TCP\n");
              n=sendTCP(ipAddr, buf, sizeof(buf));
	      if(n!=0){
                   printf("sendTCP error %d\n", n);
	      }
        }
	return 0;
}
