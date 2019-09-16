#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

struct sockaddr_in seraddr,cliaddr;

int CreateServerSocket(){
	int sockfd;

	sockfd  =socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("172.16.57.227");
	seraddr.sin_port = htons(PORTNO);
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	listen(sockfd,5);

	return sockfd;
}

void PerformServerTask(int sockfd){
	int clilen,newsockfd,n=1;
	char buf[256];

	while(1){
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);

		if(fork()==0){
			n = read(newsockfd,buf,sizeof(buf));
			printf("\nMessage from CLient %s\n",buf);
			n = write(newsockfd,buf,sizeof(buf));
			close(newsockfd);
			exit(0);
		}
		else
			close(newsockfd);
	}
}

void TerminateSocket(int sockfd){
	int result = close(sockfd);
	if(result<1)
		printf("Error");
}

int main(){
	int sockfd = CreateServerSocket();
	PerformServerTask(sockfd);
	TerminateSocket(sockfd);
}