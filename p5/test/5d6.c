#include "apue.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	int fd;
	char *path = "/home/wang/p5/test/a.txt";
	char buf[MAXLINE];

	fp = fopen(path, "r");
	if(fp == NULL){
		printf("fopen error!\n");
		exit(-1);
	}

	if(fgets(buf, MAXLINE, fp) == NULL){
		printf("fgets error!\n");
		exit(-1);
	}

	if(fputs(buf, stdout) == EOF){
		printf("fputs error!\n");
		exit(-1);
	}

	fflush(stdout);
	fd = fileno(fp);
	printf("fd=%d\n",fd);
	fsync(fd);

	return 0;
}

/**
 *先调用fflush刷新标准io的缓冲区到内核，再调用fileno获取流
 *的文件描述符，然后调用fsync刷新内核缓冲区到磁盘，确保数
 *据已到达磁盘。
 **/

