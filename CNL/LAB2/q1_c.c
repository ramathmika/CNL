#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

struct sockaddr_in address;

int CreateClientSocket(){
	int sockfd,len,result;

	sockfd  =socket(AF_INET,SOCK_STREAM,0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("172.16.57.227");
	address.sin_port = htons(PORTNO);
	len = sizeof(address);

	result = connect(sockfd,(struct sockaddr*)&address,len);
	if(result == -1){
		perror("\nClient Error");
		exit(1);
	}

	return sockfd;
}

void PerformClientTask(int sockfd){
	int result,n=1;
	char ch[256],buf[256];

	printf("Enter String: \n");
	gets(ch);
	ch[strlen(ch)] = '\0';
	write(sockfd,ch,strlen(ch));
	printf("String sent back from the server is: \n");
	while(n){
		n = read(sockfd,buf,sizeof(buf));
		puts(buf);
	}
}

void TerminateSocket(int sockfd){
	int result = close(sockfd);
	if(result<1)
		printf("Error");
}

int main(){
	int sockfd = CreateClientSocket();
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}