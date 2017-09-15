#include "apueerror.h"
#include <pwd.h>
#include <sys/wait.h>

static void sig_alrm(int signo);
static unsigned int sleepl(unsigned int);

int main(void)
{
	while(1){
		sleepl(1);
		printf("wangzhen \n");
	}
	return 0;
}

static void sig_alrm(int signo)
{
	return;
}

static unsigned int sleepl(unsigned int nsecs)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		err_sys("signal error");
	}
	alarm(nsecs);
	pause();
	return alarm(0);
}
