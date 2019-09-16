#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define PORTNO 10200

struct sockaddr_in seraddr,cliaddr;

void sort_array(int a[],int n){
	int i,j;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
			if(a[j]>a[j+1]){
				int  t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
}


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
	int clilen,newsockfd,n=1,s[1];
	int arr[100];

	while(1){
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);

		for(int i=0;i<100;i++)
			arr[i] = 0;

		if(fork()==0){
			n = recv(newsockfd,s,sizeof(s),0);
			
			printf("Size: %d",s[0]);

			n = recv(newsockfd,arr,sizeof(arr),0);
			printf("\nArray is: \n");
			for(int i=0;i<s[0];i++)
				printf("%d ",arr[i]);
			printf("\n");
			sort_array(arr,s[0]);

			n = send(newsockfd,arr,sizeof(arr),0);
			close(newsockfd);
			exit(0);
		}
		else
			close(newsockfd);
	}
}

void TerminateSocket(int sockfd){
	int result = close(sockfd);
	/*if(result<1)
		printf("Error");*/
}

int main(){
	int server_sockfd = CreateServerSocket();
	PerformServerTask(server_sockfd);
	TerminateSocket(server_sockfd);
}