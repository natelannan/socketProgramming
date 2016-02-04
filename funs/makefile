all: driverSend driverReceive

driverSend: driverSend.c sendTCP.c sendUDP.c
	gcc -Wall driverSend.c sendTCP.c sendUDP.c -o driverSend

driverReceive: driverReceive.c receiveTCP.c receiveUDP.c
	gcc -Wall driverReceive.c receiveTCP.c receiveUDP.c -o driverReceive

clean:
	rm  driverSend driverReceive
