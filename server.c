#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
void get_HTTP_File_name(char *buf,int buflen,char *file_name,char *type);
void get_HTTP_File_name(char *buf,int buflen,char *file_name,char *type);
#define Loca_IP "192.168.0.111"
#define Loca_Prot 8080
int main()
{
	int Over=0;
	int read_len;
	char *http = " /index.html HTTP";
	int se_socket,cl_socket;
	struct sockaddr_in se_addr,cl_addr;	
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(Loca_Prot);
	se_addr.sin_addr.s_addr=inet_addr(Loca_IP);
	se_socket=socket(AF_INET,SOCK_STREAM,0);
	if(se_socket<0)
	{/*{{{*/
		printf("socket fail");
		exit(0);
	}/*}}}*/
	if(bind(se_socket,(void*)&se_addr,sizeof(se_addr))==-1)
	{/*{{{*/
		printf("bind fail");
		exit(0);
	}/*}}}*/
	listen(se_socket,5);
	char buf[2048];
	int len=sizeof(cl_addr);
	char *str=(char *)malloc(10);
	while(!Over)
	{/*{{{*/
		cl_socket=accept(se_socket,(void*)&cl_addr,&len);
			read_len = read(cl_socket,buf,sizeof(buf));

		   	printf(" %d\r\n,%s\n",read_len, buf);		

	}/*}}}*/
	close(cl_socket);
	close(se_socket);

}


























