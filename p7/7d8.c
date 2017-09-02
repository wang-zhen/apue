#include "apue.h"
#include <setjmp.h>
#include <sys/resource.h>

#define FMT "%-12ld"
#define doit(name) pr_limit(#name, name)
static void pr_limit(char *, int);

int main(int argc, char *argv[])
{
	doit(RLIMIT_AS);
	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);
	doit(RLIMIT_NOFILE);
	doit(RLIMIT_NPROC);
	return 0;
}

static void pr_limit(char *name, int resource)
{
	struct rlimit limit;

	if(getrlimit(resource, &limit) != 0){
		perror("getrlimit error!\n");
		return;
	}

	printf("%-14s",name);

	if(limit.rlim_cur == RLIM_INFINITY)
		printf("(infinity)  ");
	else
		printf(FMT, limit.rlim_cur);

	if(limit.rlim_max == RLIM_INFINITY)
		printf("(infinity)  ");
	else
		printf(FMT, limit.rlim_max);

	printf("\n");
}
