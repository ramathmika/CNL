#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define PORTNO 10200

int main(){
	int server_sockfd, client_sockfd, server_len, client_len, result;
	struct sockaddr_in server_address, client_address;
	fd_set readfds, testfds;

	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("172.16.57.227");
	server_address.sin_port = htons(PORTNO);
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

	listen(server_sockfd,5);

	FD_ZERO(&readfds);
	FD_SET(server_sockfd,&readfds);

	while(1){
		char ch;
		int fd,nread;
		testfds = readfds;
		printf("Server Waiting.\n");
		result = select(FD_SETSIZE,&testfds,(fd_set *)0,(fd_set *)0,(struct timeval *)0);

		if(result<1){
			perror("Server Error");
			exit(1);
		}

		for(fd=0;fd<FD_SETSIZE;fd++){
			if(FD_ISSET(fd,&testfds)){
				if(fd == server_sockfd){
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
					FD_SET(client_sockfd,&readfds);
					printf("Adding Client on fd %d\n",client_sockfd);			
				}
				else{
					ioctl(fd,FIONREAD,&nread);
					if(nread==0){
						close(fd);
						FD_CLR(fd,&readfds);
						printf("Removing CLient on fd %d\n",fd);
					}
					else{
						read(fd,&ch,1);
						sleep(5);
						printf("Serving CLient on fd %d\n",fd);
						ch++;
						write(fd,&ch,1);
					}
				}
			}
		}
	}
}