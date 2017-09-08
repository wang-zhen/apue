#include "apueerror.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *cmd);

int main(int argc, char *argv[])
{
	int i;

	setbuf(stdout, NULL);
	for(i=1; i < argc; i++){
		do_cmd(argv[i]);
	}

	return 0;
}

static void do_cmd(char *cmd)
{
	struct tms tmsstart, tmsend;
	clock_t start, end;
	
	printf("command:%s\n",cmd);

	if((start = times(&tmsstart)) < 0)
		err_sys("times error\n");

	if(system(cmd) < 0)
		err_sys("system cmd error,%s\n",cmd);
	
	if((end = times(&tmsend)) < 0)
		err_sys("times error\n");

	pr_times(end - start, &tmsstart, &tmsend);
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
	static long clktck;

	if(clktck == 0)
		if((clktck = sysconf(_SC_CLK_TCK)) < 0)
			err_sys("sysconf error\n");

	printf("  real:%7.2lf\n", real / (double)clktck);
	printf("  user:%7.2lf\n", 
		(tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
	printf("  sys :%7.2lf\n", 
		(tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
	printf("  child user:%7.2lf\n", 
		(tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
	printf("  child sys :%7.2lf\n", 
		(tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
}
