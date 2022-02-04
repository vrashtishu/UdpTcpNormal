#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#define PORT 6000

int main()
{
	int socket_desc,n,valread;
	char *hello="Hello from Server";
	char buffer[1024]={0};
	struct sockaddr_in server,client;
	
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
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Bind Failed");
		exit(1);		
	}
	
	//Now Accept connections
	n=sizeof(client);
	
	//now send and receive msg from client
	valread=recvfrom(socket_desc,(char *)buffer,1024,0,(struct sockaddr *)&client,&n);
	buffer[valread]='\0';
	printf("Client:%s\n",buffer);
	sendto(socket_desc,(const char *)hello,strlen(hello),0,(const struct sockaddr *) &client,n);
	printf("Hello Message Sent\n");
	close(socket_desc);
	return 0;	
}
