#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main()
{
	int se_socket,cl_socket;
	struct sockaddr_in se_addr,cl_addr;	
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(8080);
	se_addr.sin_addr.s_addr=0;
	se_socket=socket(AF_INET,SOCK_STREAM,0);
	if(se_socket<0)
	{
		printf("socket fail");
		exit(0);
	}
	if(bind(se_socket,(void*)&se_addr,sizeof(se_addr))==-1)
	{
		printf("bind fail");
		exit(0);
	}
	listen(se_socket,5);
	char buf[110];
	int len=sizeof(cl_addr);
	while(1)
	{
		cl_socket=accept(se_socket,(void*)&cl_addr,&len);
//		cl_socket=accept(se_socket,NULL,NULL);
		 int r=read(cl_socket,buf,sizeof(buf));
    	 printf("%d\n%d\n",r,cl_socket);
	   	printf("%s\n",buf);
 		write(cl_socket,buf,110);
		
	}
	close(cl_socket);
	close(se_socket);

}


























