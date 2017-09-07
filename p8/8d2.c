#include "apue.h"

int glob = 6;

int main(void)
{
	int var;
	pid_t pid;

	var = 88;

	printf("before fork\n");

	if((pid = vfork()) < 0){
		perror("fork error\n");
		exit(pid);
	}else if(pid == 0){
		glob++;
		var++;
	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
		_exit(0);
	}

	sleep(1);
	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
	return 0;
}
