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
	char buf[1024];
	struct sockaddr_in se_addr;
	se_addr.sin_family=AF_INET;
	se_addr.sin_port=htons(8080);
	se_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	se_socket=socket(AF_INET,SOCK_STREAM,0);
		
	int con=connect(se_socket,(void*)&se_addr,sizeof(struct sockaddr_in));
//	printf("%d\n",con);
	if(con!=0)
			{
				printf("Connect TCP server fail\n");
				return -1;
			}else
					printf("Connect TCP server successful\n");
	char *str=(char *)malloc(10);
	while(1){
			scanf("%s",str);
			write(se_socket,str,sizeof(str));
		//	char buf[100];
			read(se_socket,buf,1024);
			printf("%s\n",buf);
		}
	close(se_socket);
	return 0;
}


