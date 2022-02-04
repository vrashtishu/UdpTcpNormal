#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 6000

int main()
{
	int socket_desc,new_socket,n,valread;
	char *hello="Hello from Server";
	char buffer[1024]={0};
	struct sockaddr_in server,client;
	
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
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Bind Failed");
		exit(1);		
	}
	printf("Bind Done Successfully\n");
	
	//Start Listening for connections
	if(listen(socket_desc,3)<0)
	{
		printf("Listen Failed\n");
		exit(1);		

	}
	
	//Now Accept connections
	n=sizeof(client);
	new_socket=accept(socket_desc,(struct sockaddr *)&client,(socklen_t *)&n);
	if(new_socket<0)
	{
		printf("Accept Failed");
		exit(1);
	}
	
	//now send and receive msg from client
	valread=read(new_socket,buffer,1024);
	printf("Client:%s\n",buffer);
	send(new_socket,hello,strlen(hello),0);
	printf("Hello Message Sent\n");
	return 0;	
}
