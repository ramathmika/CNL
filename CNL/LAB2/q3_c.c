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
	int result,n=1, arr[100],buf[100],s[1];

	printf("Enter size of array: \n");
	scanf("%d",&s[0]);
	printf("Enter array: \n");
	for(int i=0;i<s[0];i++)
		scanf("%d",&arr[i]);

	int count = send(sockfd,s,sizeof(s),0);

	count = send(sockfd,arr,sizeof(arr),0);
	printf("Sorted array is: \n");
	n = recv(sockfd,buf,sizeof(buf),0);
	for(int i=0;i<s[0];i++)
		printf("%d ",buf[i]);
	printf("\n");
	/*while(n){
		n = recv(sockfd,buf,sizeof(buf),0);
		for(int i=0;i<s[0];i++)
			printf("%d ",buf[i]);
		printf("\n");
	}*/
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