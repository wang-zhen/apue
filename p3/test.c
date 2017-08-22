#include "apue.h"
#include <fcntl.h>  
  

int main(void)
{
	int fd;
	pid_t pd;
	char *path = "/dev/null";
	
	fd = open(path, O_RDONLY);

	printf("new fd id:%d\n",fd);
	
	pd = fork();
	if(pd < 0){
		perror("fork error!")
		exit(-1);
	}else if(pd < 0){
		printf()
	}

	wait();

	return 0;
}
