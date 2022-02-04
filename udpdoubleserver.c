#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("Please Give 2 Port Numbers");
		exit(1);
	}
	int socket_desc1,socket_desc2,n,valread,ret;
	char buffer[1024]={0};
	struct sockaddr_in server1,server2,client;
	struct timeval tval;
	fd_set read_set,write_set;
	int maxfd;
	
	//create two socket
	socket_desc1=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(socket_desc1==-1)
	{
		printf("Could Not Create Socket 1");
		exit(1);
	}
	socket_desc2=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(socket_desc2==-1)
	{
		printf("Could Not Create Socket 2");
		exit(1);
	}
	//Bind address and port no to socket with sockaddr_in structure
	server1.sin_family=AF_INET;
	server1.sin_port=htons(atoi(argv[1]));
	server1.sin_addr.s_addr=INADDR_ANY;

	server2.sin_family=AF_INET;
	server2.sin_port=htons(atoi(argv[2]));
	server2.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket_desc1, (struct sockaddr *)&server1, sizeof(server1))<0)
	{
		printf("Bind Failed for socket 1");
		exit(1);		
	}

	if(bind(socket_desc2, (struct sockaddr *)&server2, sizeof(server2))<0)
	{
		printf("Bind Failed for socket 2");
		exit(1);		
	}	
	if(socket_desc1>socket_desc2)
		maxfd=socket_desc1+1;
	else if(socket_desc2>socket_desc1)
		maxfd=socket_desc2+1;
	
	while(1)
	{
		
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);

		FD_SET(socket_desc1, &read_set);
		FD_SET(socket_desc2, &read_set);

		FD_SET(socket_desc1, &write_set);
		FD_SET(socket_desc2, &write_set);
		
		tval.tv_sec=0;
		n=sizeof(client);
		ret=select(maxfd,&read_set,&write_set,NULL,&tval);
		if(ret<0)
		{
			printf("Select Thrown an Exception\n");
			exit(1);
		}		
		else if(FD_ISSET(socket_desc1,&read_set))
		{
			valread=recvfrom(socket_desc1,(char *)buffer,1024,0,(struct sockaddr *)&client,&n);
			if(valread<0)
			{
				printf("Error in Receiving\n");
				exit(1);
			}
			buffer[valread]='\0';
			printf("Received a datagram in port %s:%s\n",argv[1],buffer);
		}
		else if(FD_ISSET(socket_desc2,&read_set))
		{
			valread=recvfrom(socket_desc2,(char *)buffer,1024,0,(struct sockaddr *)&client,&n);
			if(valread<0)
			{
				printf("Error in Receiving\n");
				exit(1);
			}
			buffer[valread]='\0';
			printf("Received a datagram in port %s:%s\n",argv[2],buffer);
		}
	}
	close(socket_desc1);
	close(socket_desc2);
	return 0;	
}
