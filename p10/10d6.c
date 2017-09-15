#include "apueerror.h"
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf env_alrm;
static void sig_alrm(int signo);
static void sig_int(int signo);
static unsigned int sleep2(unsigned int);

int main(void)
{
	unsigned int unslept;

	if(signal(SIGINT, sig_int) == SIG_ERR){
		err_sys("signal error");
	}

	unslept = sleep2(3);
	printf("sleep2 returnd: %u \n", unslept);
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

static void sig_int(int signo)
{
	int i,j;
	volatile int k;

	printf("\nsig_int starting\n");
	for(i=0; i < 3000000; i++)
		for(j=0; j < 40000; j++)
			k += i*j;
	printf("sig_int finished\n");
}

