#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int c;

	while((c = getc(stdin)) != EOF){
		if(putc(c, stdout) == EOF)
			break;
	}
	
	if(ferror(stdin))
		fprintf(stdout, "input error!\n");

	return 0;
}
