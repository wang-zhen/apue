#include "apue.h"
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

int main(void){return 0;}
