#include "apueerror.h"
#include <sys/wait.h>


void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status %d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnomal termination, exit status %d%s\n", 
		WTERMSIG(status), 
	#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
	#else
		"");
	#endif

	else if(WIFSTOPPED(status))
		printf("chiled stopped, signal number = %d\n",WSTOPSIG(status));
}


int main(void)
{
	int status;
	pid_t pid;

	printf("before fork\n");

	/*normal*/
	if((pid = fork()) < 0)
		err_sys("fork error\n");
	else if(pid == 0)
		exit(7);

	if(wait(&status) != pid)
		err_sys("wait error\n");
	pr_exit(status);

	/*abort*/
	if((pid = fork()) < 0)
		err_sys("fork error\n");
	else if(pid == 0)
		abort();

	if(wait(&status) != pid)
		err_sys("wait error\n");
	pr_exit(status);

	/*divide by 0*/
	if((pid = fork()) < 0)
		err_sys("fork error\n");
	else if(pid == 0)
		status /= 0;

	if(wait(&status) != pid)
		err_sys("wait error\n");
	pr_exit(status);

	return 0;
}
