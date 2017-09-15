#include "apueerror.h"
#include <pwd.h>
#include <sys/wait.h>

static void sig_chld(int signo);

int main(void)
{
	pid_t pid;

	if(signal(SIGCLD, sig_chld) == SIG_ERR){
		err_sys("signal error");
	}

	if((pid = fork()) <0)
		err_sys("fork error!\n");
	else if(pid == 0){
		printf("chiled!\n");
		sleep(2);
		_exit(0);	
	}

	pause();
	return 0;
}

static void sig_chld(int signo)
{
	pid_t pid;
	int status;

	printf("SIGCLD received\n");
	if(signal(SIGCLD, sig_chld) == SIG_ERR){
		err_sys("signal error");
	}
	
	if((pid = wait(&status)) < 0){
		perror("wait error!");
	}
	printf("pid = %d\n",pid);
}
