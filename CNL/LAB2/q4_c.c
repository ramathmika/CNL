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
	int result,n=1, res[1], n1[1], n2[1];
	char op[1];

	printf("Enter the integers: \n");
	scanf("%d%d",&n1[0],&n2[0]);
	printf("Enter operator: \n");
	scanf("%s",&op[0]);

	int count = send(sockfd,n1,sizeof(n1),0);
	count = send(sockfd,n2,sizeof(n2),0);
	count = send(sockfd,op,sizeof(op),0);

	printf("Result is: \n");
	n = recv(sockfd,res,sizeof(res),0);
	printf("%d\n",res[0]);
	
}

void TerminateSocket(int sockfd){
	int result = close(sockfd);
/*	if(result<1)
		printf("Error");*/
}

int main(){
	int sockfd = CreateClientSocket();
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}