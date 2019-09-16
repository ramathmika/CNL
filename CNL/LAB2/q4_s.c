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
	int clilen,newsockfd,n=1,n1[1],n2[1],res[1];
	char op[1];

	while(1){
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);

		if(fork()==0){
			n = recv(newsockfd,n1,sizeof(n1),0);
			n = recv(newsockfd,n2,sizeof(n2),0);
			n = recv(newsockfd,op,sizeof(op),0);

			switch(op[0]){
				case '+': res[0] = n1[0] + n2[0];
						  break;
				case '-': res[0] = n1[0] - n2[0];
						  break;
				case '*': res[0] = n1[0] * n2[0];
						  break;
				case '/': res[0] = n1[0] / n2[0];
						  break;
			}			
			n = send(newsockfd,res,sizeof(res),0);
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