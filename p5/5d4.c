#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
	FILE *fp;
	char name[L_tmpnam], line[MAXLINE];

	printf("%s\n",tmpnam(NULL));
		
	tmpnam(name);

	printf("%s\n",name);

	sleep(5);	
	if((fp = tmpfile()) == NULL){
		printf("tmpfile error!\n");
		exit(-1);
	}

	fputs("one line of output!\n", fp);

	rewind(fp);

	fgets(line, sizeof(line), fp);

	printf("line:%s", line);
	sleep(5);	

	return 0;
}
