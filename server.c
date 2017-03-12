#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
void *pthread_write(void *ad);
void *pthread_read(void *fd);
int main()
{
	int sockfd,nfd;
	pthread_t p_r,p_w;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("creat socket fail");
		return 1;
	}
	struct sockaddr_in addr,naddr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8080);
	addr.sin_addr.s_addr=inet_addr("192.168.120.117");
	if((bind(sockfd,(void*)&addr,sizeof(addr))==-1))
	{
		printf("creat bind fail");
		return 1; 
	}
	int stl,l=0,i=0;
	listen(sockfd,5);
	char ip_addr[1];
	char *ad[5]={0};
	while(1)
	{
		nfd=accept(sockfd,(void*)&naddr,&stl);		
		char *k=inet_ntoa(naddr.sin_addr);
		printf("the client IP:  %s\n",k);
		pthread_create(&p_r,NULL,pthread_read,&nfd);	
		pthread_create(&p_w,NULL,pthread_write,&nfd);
		for(i=0;k!=ad[i]&&i<5;i++)
{		
			ad[i]=k;
			printf("the ad[%d] value: %s\n",i,ad[i]);			
		break;
}
}
		printf("l the valte:%d\n",l);

	close(nfd);
	close(sockfd);

}
void *pthread_read(void *ad)
{	
	char buf[100];	
	int td=*(int *)ad;
	read(td,buf,sizeof(buf));
	printf("%s\n",buf);
	close(td);

}
void *pthread_write(void *ad)
{
	char buf[100];
	int td=*(int *)ad;
	write(td,"zhang",sizeof(buf));
	printf("%s\n",buf);
	close(td);
}
