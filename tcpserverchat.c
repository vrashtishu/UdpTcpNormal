#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
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
	bzero((char *)&server,sizeof(server));
	bzero((char *)&client,sizeof(client));

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Bind Failed\n");
		exit(1);		
	}

	//Start Listening for connections
	listen(socket_desc,3);
	
	//Now Accept connections
	n=sizeof(client);
	new_socket=accept(socket_desc,(struct sockaddr *)&client,(socklen_t *)&n);
	if(new_socket<0)
	{
		printf("Accept Failed");
		exit(1);
	}
	
	//now send and receive msg from client
	while(1)
	{
		valread=read(new_socket,buffer,1024);
		if(valread<0)
		{
			printf("Error on reading\n");
			exit(1);
		}
		printf("Client:%s\n",buffer);
		bzero(buffer,1024);
		fgets(buffer,1024,stdin);		
		valread=write(new_socket,buffer,strlen(buffer));
		int i=strncmp("bye",buffer,3);
		if(i==0)
			break;
	}
	close(new_socket);
	close(socket_desc);
	return 0;	
}
