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
	int socket_desc,n;
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
	bzero((char *)&server,sizeof(server));

	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("10.0.2.15");

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Connection Failed\n");
		exit(1);		
	}

	
	//now send and receive msg from client
	while(1)
	{
		fgets(buffer,1024,stdin);		
		n=write(socket_desc,buffer,strlen(buffer));
		if(n<0)
		{
			printf("Error on Writing\n");
			exit(1);
		}
		bzero(buffer,1024);
		n=read(socket_desc,buffer,1024);
		if(n<0)
		{
			printf("Error on reading\n");
			exit(1);
		}
		printf("Server:%s\n",buffer);
		
		
		int i=strncmp("bye",buffer,3);
		if(i==0)
			break;
	}
	
	close(socket_desc);
	return 0;	
}
