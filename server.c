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
#define Loca_IP "192.168.0.101"
#define Loca_Prot 8080
char *http_res = "HTTP/1.1 200 OK\r\nServer:zhanghuan\r\n"
"Accept-Ranges:bytes\r\nContent-Length:1024\r\nConnection:close\r\n"
"Content-Type:text/html\r\n\r\n\
<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
<title>Title of the document</title>\r\n\
</head>\r\n\
<body>\r\n\
The content of the document......\r\n\
<input type = \"text\" name = \"name\">\r\n\
</body>\r\n\
</html>";
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
	time_t rawtime;
	struct tm *timeinfo;
	char *str=(char *)malloc(10);
	while(!Over)
	{/*{{{*/
		cl_socket=accept(se_socket,(void*)&cl_addr,&len);
			read_len = read(cl_socket,buf,sizeof(buf));
		   	printf(" %d\r\n,%s\n",read_len, buf);		
			send(cl_socket,http_res,strlen(http_res)+1,0);
//			send(cl_socket,Sdata,50,0);
			Over = 1;

	}/*}}}*/
	close(cl_socket);
	close(se_socket);

}
void send_HTTP_head(int cl_so,char *buf,int buflen)
{
		
	char finame[256];
	char fitype[16];
	char t_fitype[16] = "text/html";
	int hdr_len,send_len;
	char http_header[1024];
	get_HTTP_File_name(buf,buflen,finame,fitype);
	hdr_len = sprintf(http_header,http_res,1024,t_fitype);
//	send_len = send(cl_so,http_header,hdr_len,0);


}
void get_HTTP_File_name(char *buf,int buflen,char *file_name,char *type)
{
	int length = 0;
	char *begin, *end, *bias;
	begin = strchr(buf,' ');
	begin += 1;
	end = strchr(begin,' ');
	*end = 0;
	bias = strchr(begin,'/');
	length = end - bias;
	if(*bias == '/')
	{
		bias++;
		length--;
	}
	if(length >0)
	{
		memcpy(file_name,bias,length);
		file_name[length] = 0;
		begin = strchr(file_name,'.');
		if(begin)
				strcpy(type,begin+1);
	}
}


























