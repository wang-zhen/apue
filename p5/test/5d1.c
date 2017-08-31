#include "apue.h"

void pr_stdio(const char *, FILE *);
void mysetbuf(FILE *, char *);

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];

	fputs("enter any character\n",stdout);
	if(getchar() == EOF)
		perror("getchar error!\n");
		
	fputs("one line to standard error\n",stderr);

	pr_stdio("stdout",stdout);

	mysetbuf(stdout, buf);
	pr_stdio("stdout",stdout);

	return 0;
}

void mysetbuf(FILE * fp, char *buf)
{
	if(fp == NULL)
		return;

	if(buf == NULL)
		setvbuf(fp, NULL, _IONBF, 0);

	setvbuf(fp, buf, _IOFBF, BUFSIZ);
}

void pr_stdio(const char *name, FILE *fp)
{
	printf("stream = %s, ", name);
	
	if(fp->_IO_file_flags & _IO_UNBUFFERED)
		printf("unbuffered");
	else if(fp->_IO_file_flags & _IO_LINE_BUF)
		printf("line buffered");
	else
		printf("full buffered");
	
	printf(", buffer size = %ld\n", fp->_IO_buf_end - fp->_IO_buf_base);
}
