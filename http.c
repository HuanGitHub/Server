#include <string.h>
#include <stdio.h>
char *http = "GET /index.html HTTP";
void get_HTTP_File_name(char *buf,int buflen,char *file_name,char *type)
{
	int length = 0;
	char *begin, *end, *bias;
	begin = strchr(buf,' ');
	begin += 1;
	printf("%s\r\n",begin);
	end = strchr(begin,' ');
	printf("%s\r\n",end);
	bias = strchr(begin,'/');
	length = end - bias;
	printf("%d\r\n",length);
	printf("%s\r\n",bias);
	if(*bias == '/')
	{
		bias++;
		length--;
		printf("%d\r\n",length);
	}
	if(length >0)
	{
		memcpy(file_name,bias,length);
		file_name[length] = 0;
		printf("%s\r\n",file_name);

		begin = strchr(file_name,'.');
		if(begin){
			printf("%s\r\n",begin);
			strcpy(type,begin+1);
			printf("%s\r\n",type);
			
		}
	}
#if 0
#endif
}
int main()
{
	char file_name[256] , file_type[16];
	get_HTTP_File_name(http,sizeof(http),file_name,file_type);
	printf("%s,%s",file_name,file_type);
}
