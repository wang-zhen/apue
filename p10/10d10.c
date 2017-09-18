#include "apueerror.h"
#include <error.h>
#include <signal.h>

int main(void)
{
	return 0;
}

void pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0){
		err_sys("sigprocmask error\n");
	}
	
	printf("%s\n",str);

	if(sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM)) printf("SIGALRM ");

	printf("\n");

	errno = errno_save;
}
