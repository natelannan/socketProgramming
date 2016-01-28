#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sendUDP.h"
#include "sendTCP.h"

int sendUDP(void *);
int sendTCP(void *);


int main (int argc, char* argv[]){
        int n;
        int udp = 1;
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
	
        if(udp){
              printf("UDP\n");
	      n=sendUDP(ipAddr);
	      if(n!=0){
                   printf("sendUDP error %d\n", n);
	      }
        }

	else {
              printf("TCP\n");
              n=sendTCP(ipAddr);
	      if(n!=0){
                   printf("sendTCP error %d\n", n);
	      }
        }
	return 0;
}
