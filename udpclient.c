#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<string.h>
#define PORT 6000

int main()
{
	int socket_desc,n,valread;
	char *hello="Hello from Client";
	char buffer[1024]={0};
	struct sockaddr_in server;
	
	//create a socket
	socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(socket_desc==-1)
	{
		printf("Could Not Create Scoket");
		exit(1);
	}
	//Bind address and port no to socket with sockaddr_in structure
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("10.0.2.15");

	n=sizeof(server);
	
	//now send and receive msg from client
	sendto(socket_desc,(const char *)hello,strlen(hello),0,(const struct sockaddr *) &server,n);
	printf("Hello Message Sent\n");
	valread=recvfrom(socket_desc,(char *)buffer,1024,0,(struct sockaddr *)&server,&n);
	buffer[valread]='\0';
	printf("Server:%s\n",buffer);
	
	
	close(socket_desc);
	return 0;	
}
