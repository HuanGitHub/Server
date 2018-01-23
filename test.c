#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
pthread_t tcp_connect;
pthread_t tcp_server;
void *Tcp_client()
{/*{{{*//*{{{*//*}}}*//*{{{*//*}}}*/
	int se_socket;
	struct sockaddr_in se_addr;
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(19537);
	se_addr.sin_addr.s_addr=inet_addr("192.168.120.104");
	se_socket=socket(AF_INET,SOCK_STREAM,0);
	
	int con=connect(se_socket,(void*)&se_addr,sizeof(struct sockaddr_in));
	if(con==-1)
	{
		printf("Connect Tcp server fail\n");
		exit(0);
	}	
	char *str=(char *)malloc(10);
	char *t="0";
	while(1)
	{
	scanf("%s",str);
	if(t==0){
		free(str);
		close(se_socket);
		printf("Tcp client over");
		exit(0);
	}else{
		write(se_socket,str,sizeof(str));
		}
	}	
	close(se_socket);
	
}/*}}}*/
void *Tcp_server()
{/*{{{*/
	int se_socket,cl_socket;
	struct sockaddr_in se_addr,cl_addr;	
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(8080);
	se_addr.sin_addr.s_addr=inet_addr("192.168.120.105");
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
	char buf[110];
	int len=sizeof(cl_addr);
	time_t rawtime;
	struct tm *timeinfo;
	char *str=(char *)malloc(10);
	while(1)
	{
		cl_socket=accept(se_socket,(void*)&cl_addr,&len);
		printf("%u\n",ntohl(cl_addr.sin_addr.s_addr));
		time(&rawtime);
		timeinfo=localtime(&rawtime);
		printf("Have Tcp client connect\n");
		printf("\007the current time is: %s",asctime(timeinfo));
//		read(cl_socket,buf,sizeof(buf));
//	   	printf("ESO8266 send data: %s\n",buf);
//		printf("Please input char\n");
//		scanf("%s",str);
//		printf("Input char is:%s\n",str);
 //		write(cl_socket,str,10);	
// 		write(cl_socket,"test",10);	
	}
	close(cl_socket);
	close(se_socket);	
}/*}}}*/
int main()
{
		pthread_create(&tcp_connect,NULL,Tcp_client,NULL);
		pthread_create(&tcp_server,NULL,Tcp_server,NULL);
		while(1);
}


























