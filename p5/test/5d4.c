#include "apue.h"

int main(int argc, char *argv[])
{
	int c;

	while((c = getchar()) != EOF ){
		if(putchar(c) == EOF)
			break;
	}
	return 0;
}
