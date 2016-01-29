/*
 * signalPass.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: daslabasus1
 */

#include "signalPass.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define MAX_IO_ATTEMPTS 1000000

static int fd = 0;
static struct termios myTermios;

/**
 * Opens and configures UART
 *
 *returns:
 *	 0			no error
 *	-1			open uart fails
 *	-2			getting current terminal device settings fails
 *	-3			setting RX baud rate fails
 *	-4			setting TX baud rate fails
 */
int SigPass_init(char* UART_Path){

	if ((fd = open(UART_Path, O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0) {
		return -1;
	}

	if (tcgetattr(fd, &myTermios) != 0) { /* Obtain current terminal device settings in order to modify them at a later time. */
		return -2;
	}

	if (cfsetispeed(&myTermios, B115200) < 0) {//RX speed
		return -3;
	}

	if (cfsetospeed(&myTermios, B115200) < 0) {//TX speed
		return -4;
	}

	/*
	myTermios.c_oflag &= ~OPOST; //raw (unprocessed) output
	myTermios.c_cflag |= (CLOCAL | CREAD);   // Enable the receiver and set local mode
	myTermios.c_cflag &= ~CSTOPB;            // 1 stop bit
	myTermios.c_cflag &= ~CRTSCTS;           // Disable hardware flow control (e.g. CTS and RTS signals)
	myTermios.c_cflag &= ~CSIZE; // Mask the character size bits
	myTermios.c_cflag |= CS8;    // Select 8 data bits
	myTermios.c_cflag &= ~PARENB;//set no parity
	myTermios.c_iflag &= ~(INPCK | ISTRIP);
	myTermios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //raw input is unprocessed
	myTermios.c_iflag &= ~(IXON | IXOFF | IXANY); //ignore character meaning (e.g. CTRL+C , etc.)
	myTermios.c_cc[VMIN] = 0; // read minimum 0 char
	myTermios.c_cc[VTIME] = 2;  //Timeout after 200 ms.
    */

	myTermios.c_iflag = 0;
	myTermios.c_oflag = 0;
	myTermios.c_lflag = 0;

	tcsetattr(fd, TCSANOW, &myTermios);  //Set newly-modified attributes

	char buf [10000];
	int n;
	do {
		n = read (fd, buf, sizeof( buf));
	} while (n > 0);


	return 0;
}

/**
 *Reads a numBytes length packet from the UART
 *
 *returns:
 *	 0			no error
 *	-1			numBytes bytes have been read without reading the header byte
 *	-2			header byte read fails
 *	-3			payload read fails
 *	-4			payload read timeout
 */
int SigPass_receivePacket(uint8_t* buf, size_t numBytes){

	int i = 0;
	int ret;
	int bytesLeft = numBytes - 1;  //account for extracted start byte

	do{
	        if(i >= numBytes){  //read everything from buf without receiving a byte (start_byte)
			return -1;
		}

		ret = read(fd, (void*) buf, 1);   //read 1 byte into buf from fd

		if(ret < -1)  //read fail
			return -2;

		++i;  //increment
		if(ret <= 0) //eof or 0 bytes read: start over
			--i;
	}
	while(ret != 1 || buf[0] != SIGNAL_PASS_START_BYTE); //grab start byte in buf[0]

	i = 0;

	do{
	  ret = read(fd, (void*)(&buf[numBytes - bytesLeft]), bytesLeft);  //try to grab bytes left and place in buf after bytes already written

		if(ret == -1) //read failed try again
			++ret;

		if(ret < 0)  //? how does this happen
			return -3;

		bytesLeft -= ret;  //decrement bytes left by ammt of bytes xferd

		++i; //iterator for max attempts
	}
	while(bytesLeft && i < MAX_IO_ATTEMPTS);//try to get the rest of the bytes

	if(i >= MAX_IO_ATTEMPTS) //hit max attempts before all bytes transferred
		return -4;

	return 0;
}

/**
 * Writes a numBytes length packet to the UART
 *
 *returns:
 *	 0			no error
 *	-1			writing packet fails
 *	-2			writing packet takes too long
 */
int SigPass_sendPacket(uint8_t* buf, size_t numBytes){

	int ret, i;
	int bytesLeft = numBytes;

	for(i = 1;i<numBytes;++i){
		if(buf[i] == SIGNAL_PASS_START_BYTE)
		        buf[i]--;  //locate start byte ? decrement
	}

	i = 0;

	do{
	        ret = write(fd, (void*)(&buf[numBytes - bytesLeft]), bytesLeft); //attempt to send bytes

		if(ret < 0)      //send byte failed
			return -1;

		bytesLeft -= ret;  //subtract ammount left by what was sent
		++i;
	}
	while(bytesLeft && i < MAX_IO_ATTEMPTS);  //while there are bytes left and haven't hit max

	if(i >= MAX_IO_ATTEMPTS)  //hit max attempts before all bytes sent
		return -2;

	return 0;
}

/**
 * Closes the UART file handle
 */
void SigPass_close(){
	close(fd);
}

