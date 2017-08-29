#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

#define MSIZE 2

int main(int argc, char *argv[])
{
	char buf[MSIZE];

	while(fgets(buf, MSIZE, stdin) != NULL){
		if(fputs(buf, stdout) == EOF)
			break;
	}
	
	if(ferror(stdin))
		fprintf(stdout, "input error!\n");

	return 0;
}
