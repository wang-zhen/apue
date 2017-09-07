#include "apueerror.h"
#include <sys/wait.h>

int main(void)
{
	int status;
	pid_t pid;

	/*first fork*/
	if((pid = fork()) < 0)
		err_sys("parent fork error\n");
	else if(pid == 0){
		if((pid = fork()) < 0)
			err_sys("child fork error\n");
		else if(pid > 0)
			exit(0);

		sleep(10);
		printf("seconed chiled, parent id = %d\n", getppid());
		return 0;
	}

	if((waitpid(pid, &status, 0)) != pid)
		err_sys("waitpid error\n");

/*
	int status;
	pid_t pid1;
	pid_t pid2;

	if((pid1 = fork()) < 0)
		err_sys("parent fork error\n");
	else if(pid1 == 0){
		if((pid2 = fork()) < 0)
			err_sys("child fork error\n");
		else if(pid2 > 0)
			exit(0);
		
		sleep(10);
		printf("chiled error\n");
		return 0;
	}

	waitpid(pid1, &status, 0);
*/
	return 0;
}

/*
 *示例中的代码是正确的的，因为pid已经在子
 *进程中被复制，所以pid不会被改变.
 *
 * */
