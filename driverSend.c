
#include "sendUDP.h"
#include "sendTCP.h"


int main (){
	ipAddr = "192.168.1.4";
	
	n=sendUDP(ipAddr);
	
	if(n!=0){
		printf("UDP splat!\n");
	}

	n=sendTCP(ipaAddr);

	if(n!=0){
		printf("TCP splat!\n");
	}
	return 0;
}
