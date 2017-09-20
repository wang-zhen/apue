#include "apueerror.h"
#include <sys/wait.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmaek, oldmask, zeromask;

void charatatime(const char *);

int main(void)
{
	pid_t pid;

	TELL_WAIT();

	for(;;){
		printf("--main--\n");
		sigsuspend(&zeromask);
	}
	return 0;
}

void charatatime(const char *str)
{
	const char *ptr;
	setbuf(stdout, NULL);

	for(ptr = str; *ptr != 0; ptr++){
		putchar(*ptr);
	}
}


static void sig_usr(int signo)
{
	printf("revived signal %d\n",signo);
	sigflag = 1;
}

void TELL_WAIT(void)
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");

	sigemptyset(&newmaek);
	sigemptyset(&zeromask);
	sigaddset(&newmaek, SIGUSR1);	
	sigaddset(&newmaek, SIGUSR2);

	if(sigprocmask(SIG_BLOCK, &newmaek, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
}

void WAIT_PARENT(void)
{
	while(sigflag == 0)
		sigsuspend(&zeromask);

	sigflag = 0;

	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error\n");
}

void TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1);
}
