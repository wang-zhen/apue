#include "../apue.h"
#include <fcntl.h>

char *path = "./file";

int main(void)
{
	int fd, len;

	fd = open(path, O_RDWR|O_APPEND);
	//fd = open(path, O_RDWR);
	if(fd == -1)
		perror("open error");

	lseek(fd, 0, SEEK_SET);

	len = write(fd, "test\n", 5);
	if(len != 5)
		perror("write error");

	return 0;
}
