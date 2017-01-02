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
	int se_socket;
	struct sockaddr_in se_addr;
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(8080);
	se_addr.sin_addr.s_addr=0;
	se_socket=socket(AF_INET,SOCK_STREAM,0);

	int len=sizeof(se_addr);
	printf("%d\n",len);
	int con=connect(se_socket,(void*)&se_addr,len);
	printf("%d\n",con);
	char *str="hello world";            //output string
	char buf[]="test";
	write(se_socket,buf,sizeof(buf));
	/*char buf[100];
	read(se_socket,buf,100);
	printf("%s\n",buf);
*/



	close(se_socket);
}	

























