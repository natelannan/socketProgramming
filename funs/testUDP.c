#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "sendUDP.h"
#include "receiveUDP.h"
#define BUFSIZE 1

int main(int argc, char* argv[]){
	int err;
	uint8_t buf[BUFSIZE];

    if (argc < 2){
      printf("Usage:  testUDP <ip address> <option>\n");
      printf("\tip address:  ipv4 address of device to send message to\n");
      printf("\t<option>:  if anything is passed, this instance will initiate test by passing first 2 bytes\n");
      return 0;
    }
	char* ipAddr = argv[1];

	if(argc>2){
		buf[0]=160;
		printf("Sending: \n");
	    printf("\tbuf[0]: %2x\n", buf[0]);
	    err=sendUDP(ipAddr, buf, sizeof(buf));
	    if(err!=0){
	    	printf("sendUDP error %d\n", err);
	    }
	}
	while(1){
		if(receiveUDP(buf, sizeof(buf))==0){
			printf("Received: \n");
		    printf("\tbuf[0]: %2x\n", buf[0]);
			buf[0]=buf[0]+1;
			printf("Sending: \n");
		    printf("\tbuf[0]: %2x\n", buf[0]);
		    err=sendUDP(ipAddr, buf, sizeof(buf));
		    if(err!=0){
		    	printf("sendUDP error %d\n", err);
		    }
		}
		else
			printf("receiveUDP error\n");
	}

	return 0;
}
