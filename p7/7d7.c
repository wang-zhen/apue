#include "apue.h"
#include <setjmp.h>

#define DATAFILE "datafile"

FILE *open_data(void)
{
	FILE *fp;

	char buf[BUFSIZ];

	if((fp = fopen(DATAFILE, "r+")) == NULL){
		printf("fopen error!\n");
		return NULL;
	}

	if(setvbuf(fp, buf, _IOLBF, BUFSIZ) != 0){
		printf("setvbuf error!\n");
		return NULL;
	}

	return fp;
}

int main(int argc, char *argv[])
{
	FILE *fp = open_data();
	if(fp == NULL)
		return -1;

	return 0;
}
