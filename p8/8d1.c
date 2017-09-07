#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;

	var = 88;

	if(write(STDOUT_FILENO, buf, strlen(buf)) != strlen(buf)){
		perror("write to stdout error!\n");
		exit(-1);
	}
	printf("before fork\n");

	if((pid = fork()) < 0){
		perror("fork error\n");
		exit(pid);
	}else if(pid == 0){
		glob++;
		var++;
	}else{
		sleep(2);
	}

	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
	return 0;
}

/*
 *1. strlen替换了sizeof sizeof编译是确定值，strlen是实时的
 *2. ./8d1  >tmp cat tmp 会有两次输出"before fork",原因是
 * 当其标准输出指向终端时是行缓冲，但指向文件时是全缓冲的
 *所以父进程 只是将"before fork"放到了缓冲区，此时执行fork
 * 的话，子进程会复制这个缓冲区，父子进程在退出时会刷新缓
 * 冲区。
 *
 * */
