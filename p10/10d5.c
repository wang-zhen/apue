#include "apueerror.h"
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf env_alrm;
static void sig_alrm(int signo);
static unsigned int sleep2(unsigned int);

int main(void)
{
	while(1){
		sleep2(1);
		printf("wangzhen \n");
	}
	return 0;
}

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}

static unsigned int sleep2(unsigned int nsecs)
{
	if(signal(SIGALRM, sig_alrm) == SIG_ERR){
		err_sys("signal error");
	}
	if(setjmp(env_alrm) == 0){
		alarm(nsecs);
		pause();
	}
	return alarm(0);
}
