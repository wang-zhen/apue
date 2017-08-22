#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flag)
{
	int val;
	
	if((val = fcntl(fd, F_GETFL, 0)) < 0 )
		perror("fcntl f_getfl error");

	val |= flag;

	if(fcntl(fd, F_SETFL, val) < 0)
		perror("fcntl f_setfl error");
}

void clr_fl(int fd, int flag)
{
	int val;
	
	if((val = fcntl(fd, F_GETFL, 0)) < 0 )
		perror("fcntl f_getfl error");

	val &= ~flag;

	if(fcntl(fd, F_SETFL, val) < 0)
		perror("fcntl f_setfl error");
}

int main(int argc, char *argv[])
{
	int fd, val;

	if(!argv[1]){
		printf("put error!\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY|O_APPEND);
	if(fd == -1)
		perror("open error");

		printf("fd:%d\n",fd);

	val = write(fd, "wangzhen\n", 9);
	if(val != 9)
		perror("write error");

		printf("val:%d\n",val);

	if((val = fcntl(fd, F_GETFL, 0)) == -1)
		perror("fcntl error");

	switch(val & O_ACCMODE){
	case O_RDONLY:
		printf("read only!\n");
		break;
	case O_WRONLY:
		printf("write only!\n");
		break;
	case O_RDWR:
		printf("read write!\n");
		break;
	default:
		printf("unkown access mode\n");
		break;
	}

	return 0;
}
