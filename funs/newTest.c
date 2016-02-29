#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>//use select() for multiplexing
#include <sys/fcntl.h> // for non-blocking
#define MAX_LENGTH 1024
    /* Select() params
     * int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
     * FD_SET(int fd, fd_set *set);
     * FD_CLR(int fd, fd_set *set);
     * FD_ISSET(int fd, fd_set *set);
     * FD_ZERO(fd_set *set);
    */
void error(char *message)
{
      perror(message);
      exit(1);
}
int main(int argc, char* argv[])
{
      fd_set readfds;
      fd_set writefds;
      struct timeval tv;
      int numfd;
      int socket_fd, bytes_read, bytes_sent;
      unsigned int address_length;
      char receive_data[1],send_data[1];
      struct sockaddr_in myAddress , remAddress;

      if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
      {
          error("socket()");
      }
      
      int flags = fcntl(socket_fd, F_GETFL);
      flags |= O_NONBLOCK;
      fcntl(socket_fd, F_SETFL, flags);
      //fcntl(socket_fd, F_SETFL, O_NONBLOCK); //set socket to non-blocking
      // clear the set ahead of time
      FD_ZERO(&readfds);
      FD_ZERO(&writefds);

      FD_SET(socket_fd, &readfds); //get ready to read
      numfd = socket_fd + 1;
      
      // wait until socket has data ready to be received (timeout 10.5 secs)
      tv.tv_sec = 10;
      tv.tv_usec = 500000;
      myAddress.sin_family = AF_INET;
      myAddress.sin_port = htons(4547);
      myAddress.sin_addr.s_addr = INADDR_ANY;

      remAddress.sin_family = AF_INET;
      remAddress.sin_port = htons(4547);
      remAddress.sin_addr.s_addr = inet_addr((char*)argv[1]);
      bzero(&(myAddress.sin_zero),8);
      if (bind(socket_fd,(struct sockaddr *)&myAddress, sizeof(struct sockaddr)) == -1)
      {
          error("bind()");
      }
      address_length = sizeof(struct sockaddr);
     
      if(argc>2){//primer
	send_data[0]=160;
	printf("Sending: \n");
	printf("\tbuf[0]: %2x\n", send_data[0]);
	FD_CLR(socket_fd,&writefds);
        sendto(socket_fd,send_data,strlen(send_data),0,(struct sockaddr *)&remAddress, sizeof(struct sockaddr));
      }
	
      while (1)
      {
        int recieve = select(numfd, &readfds, &writefds,/*NULL,*/ NULL, &tv);
        if (recieve == -1) 
        {
          perror("select"); // error occurred in select()
        } 
        else if (recieve == 0) 
        {
          printf("Timeout occurred!  No data after 10.5 seconds.\n");
        } 
        else 
        {
            // one or both of the descriptors have data
            if (FD_ISSET(socket_fd, &readfds)) //if set to read
            { 
              FD_CLR(socket_fd, &readfds);
              bytes_read = recvfrom(socket_fd,receive_data,MAX_LENGTH,0,(struct sockaddr *)&remAddress, &address_length); 
	      if(bytes_read < 0){
		printf("poo\n");
		exit(1);
	      }  
	      send_data[0]=receive_data[0]+1;
	      printf("Received: \n");
	      printf("\tbuf[0]: %2x\n", receive_data[0]);
	      FD_SET(socket_fd, &writefds);
            }
            else if (FD_ISSET(socket_fd/*0*/, &writefds)) //if set to write
            {
              FD_CLR(socket_fd/*0*/, &writefds);
              bytes_sent=sendto(socket_fd,send_data,strlen(send_data),0,(struct sockaddr *)&remAddress, sizeof(struct sockaddr));
	      if(bytes_sent < 0){
		printf("poo\n");
		exit(1);
	      } 
	      printf("Sending: \n");
	      printf("\tbuf[0]: %2x\n", send_data[0]);
	      FD_SET(socket_fd, &readfds);
            }
            else printf("\nOOPS! What happened?\n");
        } //end else
      }//end while
      close (socket_fd);
      return 0;
    }
