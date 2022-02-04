#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 6000

int main()
{
	int socket_desc,n,valread;
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
	
	n=sizeof(client);
	
	while(1)
	{
		valread=recvfrom(socket_desc,(char *)buffer,1024,0,(struct sockaddr *)&client,&n);
		if(valread<0)
		{
			printf("Error in Receiving\n");
			exit(1);
		}
		
		printf("Received a datagram:\n");
		printf("%s\n",buffer);
	}
	close(socket_desc);
	return 0;	
}
