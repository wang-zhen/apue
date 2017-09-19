#include "apueerror.h"
#include <error.h>
#include <signal.h>

static void sig_int(int);

int main(void)
{
	sigset_t newmask, oldmask, waitmask;

	pr_mask("programe start: ");
	if(signal(SIGINT, sig_int) < 0)
		err_sys("signal(SIGINT) error");
	
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");

	pr_mask("in critical region: ");

	if(sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error\n");

	pr_mask("after return from sigsuspend: ");

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	pr_mask("program exit: ");

	return 0;
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");	
}

void pr_mask(const char *str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0){
		err_sys("sigprocmask error\n");
	}
	
	printf("%s",str);

	if(sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if(sigismember(&sigset, SIGQUIT)) printf("SIGQUIT ");
	if(sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if(sigismember(&sigset, SIGALRM)) printf("SIGALRM ");

	printf("\n");

	errno = errno_save;
}
