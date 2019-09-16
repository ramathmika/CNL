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
	int sd,t;
	struct sockaddr_in sadd,cadd;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	sadd.sin_port=htons(10200);
	int result=bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
	int len=sizeof(cadd);
	int s[2],a[10],res[10][10];
	t=recvfrom(sd,&s,sizeof(s),0,(struct sockaddr*)&cadd,&len);
	for (int i = 0; i < s[0]; ++i)
	{
		t=recvfrom(sd,&a,sizeof(a),0,(struct sockaddr*)&cadd,&len);
		for (int j = 0; j < s[1]; ++j)
		{
			printf("%d\t",a[j]);
			res[i][j]=a[j];
		}
		printf("\n");
	}
	t=sendto(sd,&res,sizeof(res),0,(struct sockaddr*)&cadd,len);
	return 0;
}