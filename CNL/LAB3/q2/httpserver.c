#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 10200

struct serverPacket{
	char statusLine[30];
	char headerLine[30];
	char Body[30];
};

struct clientPacket{
	char requestLine[30];
	char headerLine[30];
	char Body[30]; 
};

typedef struct serverPacket SP;
typedef struct clientPacket CP;

int main(){
		
	int sd;
	struct sockaddr_in sadd,cadd;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	sadd.sin_port=htons(10200);
	int result=bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
	int len=sizeof(cadd);
	SP s={"status Line","header line","body"};
	CP c;
	int m=recvfrom(sd,&c,sizeof(c),0,(struct sockaddr*)&cadd,&len);
	printf("%s\t%s\t%s\n",c.requestLine,c.headerLine,c.Body);
	int n=sendto(sd,&s,sizeof(s),0,(struct sockaddr*)&cadd,len);
	return 0;
}