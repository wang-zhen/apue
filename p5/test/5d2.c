#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

#define MSIZE 5

int main(int argc, char *argv[])
{
	int i=0;
	char buf[MSIZE];

	while(fgets(buf, MSIZE, stdin) != NULL){
		if(strstr(buf, "exit"))
			break;

		if(fputs(buf, stdout) == EOF)
			break;
		i++;
	}
	
	if(ferror(stdin))
		fprintf(stdout, "input error!\n");

	fprintf(stdout, "i = %d\n",i);

	return 0;
}

/**
 *当MSIZE 为5时，fgets也能工作，只不过循环的次数可能
 *比MSIZE大时较多。fgets在指定流中读入 直到遇到换行符
 *或者buf满（包含0字符）。
 **/
