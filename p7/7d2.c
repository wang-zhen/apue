#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	atexit(my_exit2);
	atexit(my_exit1);
	atexit(my_exit1);

	printf("main is done\n");

	//_exit(2);
	return 0;
}

static void my_exit1(void)
{
	printf("first exit handler!\n");
}

static void my_exit2(void)
{
	printf("second exit handler!\n");
}
