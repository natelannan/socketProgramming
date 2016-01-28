#include <stdio.h>
#include <stdlib.h>

#include "receiveUDP.h"
#include "receiveTCP.h"

int receiveUDP();
int receiveTCP();

int main (int argc, char* argv[]){
        int n;
        int udp = 1;
	if (argc == 2){
	     udp = 0;
	}
	if(udp){
	     printf("UDP\n");	
	     n=receiveUDP();
	
	     if(n!=0){
	          printf("receiveUDP error %d\n", n);
	     }
        }
        else{
	     printf("TCP\n");
	     n=receiveTCP();

	     if(n!=0){
	          printf("receiveTCP error %d\n", n);
	     }
	}
	return 0;
}
