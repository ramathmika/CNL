#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 10200


int main(){
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(10200);
	int len=sizeof(address);

	int s[2],a[10],t;

	printf("Value for m & n\n");
	scanf("%d%d",&s[0],&s[1]);
	t=sendto(sd,&s,sizeof(s),0,(struct sockaddr*)&address,len);
	
	for (int i = 0; i < s[0]; ++i)
	{
		printf("Enter array %d\n",i+1);
		for (int j = 0; j < s[1]; ++j)
			scanf("%d",&a[j]);
		t=sendto(sd,&a,sizeof(a),0,(struct sockaddr*)&address,len);
	}
	int res[10][10];
	int n=recvfrom(sd,&res,sizeof(res),0,(struct sockaddr*)&address,&len);
	printf("\n\nMatrix:\n");
	for (int i = 0; i < s[0]; ++i)
	{
		for (int j = 0; j < s[1]; ++j)
			printf("%d\t",res[i][j]);
		printf("\n");
	}
	return 0;
}