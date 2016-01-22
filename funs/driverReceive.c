#include <stdio.h>

#include "receiveUDP.h"
#include "receiveTCP.h"

//int receiveUDP();
int receiveTCP();

int main (){
        int n;
	/*
	n=receiveUDP();
	
	if(n!=0){
		printf("UDP splat!\n");
	}
	*/
	n=receiveTCP();

	if(n!=0){
		printf("TCP splat!\n");
	}
	return 0;
}
