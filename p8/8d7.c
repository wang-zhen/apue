#include "apueerror.h"
#include <sys/wait.h>

void charatatime(const char *);

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0)
		err_sys("parent fork error\n");
	else if(pid == 0){
	//	WAIT_PARENT();
		charatatime("output from chiled\n");
		exit(0);
	}else{
		charatatime("output from parnet\n");
//		TELL_CHILD(pid);
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
