#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("input error!\n");
		exit(-1);
	}

	if(access(argv[1], R_OK) < 0)
		perror("access error!");
	else
		printf("read access!\n");

	if(open(argv[1], O_RDONLY) < 0)
		perror("open error!");
	else
		printf("open ok!\n");

	return 0;
}
