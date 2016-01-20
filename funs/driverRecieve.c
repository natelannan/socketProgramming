
#include "receiveUDP.h"
#include "receiveTCP.h"


int main (){
	ipAddr = "192.168.1.4";
	
	n=receiveUDP(ipAddr);
	
	if(n!=0){
		printf("UDP splat!\n");
	}

	n=receiveTCP(ipAddr);

	if(n!=0){
		printf("TCP splat!\n");
	}
	return 0;
}
