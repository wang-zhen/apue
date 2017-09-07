#include "apueerror.h"
#include <sys/wait.h>

char *eve_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0)
		err_sys("parent fork error\n");
	else if(pid == 0){
		if(execle("/home/wang/p8/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, eve_init) == -1)
			err_sys("execl error\n");
	}

	if(waitpid(pid, NULL, 0) < 0)
		err_sys("waitpid error\n");

	if((pid = fork()) < 0)
		err_sys("parent fork error\n");
	else if(pid == 0){
		if(execlp("echoall", "echoall", "only 1 arg1", (char *)0) == -1)
			err_sys("execl error\n");
	}

	if(waitpid(pid, NULL, 0) < 0)
		err_sys("waitpid error\n");

	return 0;
}

