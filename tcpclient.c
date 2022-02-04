#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#define PORT 6000
int main()
{
	int socket_desc,valread;
	char *hello="Hello from Client";
	char buffer[1024]={0};
	struct sockaddr_in server;
	
	//create a socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc==-1)
	{
		printf("Could Not Create Scoket");
		exit(1);
	}
	//Bind address and port no to socket with sockaddr_in structure
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("10.0.2.15");

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Connection Failed");
		exit(1);		
	}
	

	//now send and receive msg from client
	send(socket_desc,hello,strlen(hello),0);
	printf("Hello Message Sent\n");
	valread=read(socket_desc,buffer,1024);
	printf("Server:%s\n",buffer);
	
	return 0;	
}
