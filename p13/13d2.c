#include "apueerror.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/file.h>
#include <sys/types.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int lockfile(int);
void daemonize(const char *);
int already_running(void);

int main(int argc, char *argv[])
{
    char *cmd;

    printf("wang %s\n",argv[0]);
    if((cmd = strrchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else    
        cmd++;

	daemonize(cmd);
	if(already_running()){
		syslog(LOG_ERR, "daemon already runing");
		exit(1);
	}

	sleep(100);
	return 0;
}

/*
 *On success, zero is returned.On success, zero is returned.
 * */
int lockfile(int fd)
{	
	return flock(fd, LOCK_EX|LOCK_NB);
}

int already_running(void)
{
	int fd;
	char buf[16] = {0,};

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0){
		syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	if(lockfile(fd)){
		if(errno == EACCES || errno == EAGAIN){
			close(fd);
			return 1;
		}
		syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
		return -1;
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf));
	return 0;
}

void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0);

	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can't get file limit", cmd);

	if((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if(pid != 0)
		exit(0);
	setsid();

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if(sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP");
	if((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if(pid != 0)
		exit(0);
	
	if(chdir("/") < 0)
		err_quit("%s: can't change directory to /", cmd);

	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;

	for(i=0; i < rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(fd0);
	fd2 = dup(fd0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2){
		syslog(LOG_ERR, "unexpected file discriptors %d %d %d",
				fd0, fd1, fd2);
		exit(1);
	}
}

