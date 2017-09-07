#include "apueerror.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i;
	char **ptr;
	extern char **environ;

	for(i=0; i< argc; i++){
		printf("argv[%d] %s\n", i, argv[i]);
	}

	
	for(ptr=environ; *ptr != NULL; ptr++){
		printf("%s\n", *ptr);
	}

	return 0;
}

