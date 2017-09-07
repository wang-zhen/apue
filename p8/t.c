#include "apue.h"

int main(int argc, char *argv[])
{
	int i;
	for(i=0; i < 10; i++){
		printf("test %s\n", argv[1]);
		sleep(1);
	}

	return 0;
}
