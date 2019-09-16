#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define PORTNO 9734

struct sockaddr_in address;

int CreateClientSocket(){
	int sockfd,status;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.16.58.36");
	address.sin_port = htons(PORTNO);

	status = connect(sockfd,(struct sockaddr *)&address, sizeof(address));
	if(status){
		printf("Connected, %d\n",sockfd);
	}
	/*if(status<0){
		printf("Error");
	}*/
	return sockfd;
}

void PerformClientTask(int sockfd){
	int num=2, n=1,m=1;
	char buf[256];
	printf("Enter the number: \n");
	scanf("%d",&num);
	//printf("%d",sockfd);
	//int count = send(sockfd,num,sizeof(num),0);
	m = write(sockfd,&num,sizeof(num));
	printf("check\n");
	printf("String sent from server:\n");
	n = read(sockfd,buf,sizeof(buf));
	puts(buf);
	/*while(n){
		n = read(sockfd,buf,strlen(buf));
		puts(buf);
	}*/
}

void TerminateSocket(int sockfd){
	int status = close(sockfd);
	/*if(status<0){
		printf("Error");
	}*/
}

void main(){
	int sockfd = CreateClientSocket();
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}