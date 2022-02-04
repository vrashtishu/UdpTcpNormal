#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("Please Send Message for sending and port Number\n");
		exit(1);	
	}
	int socket_desc,valread;
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
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=inet_addr("10.0.2.15");

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
		printf("Connection Failed");
		exit(1);		
	}
	

	//now send and receive msg from client
	send(socket_desc,argv[2],strlen(argv[2]),0);
	printf("Message Sending Successfully");
	
	return 0;	
}
