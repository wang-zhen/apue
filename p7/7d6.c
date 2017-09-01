#include "apue.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

/*
 *./7d4 1;2;3;4
 * */

jmp_buf jmpbuffer;
static int globval;

int main(int argc, char *argv[])
{
	int autoval;
	register int regival;
	volatile int volaval;
	static int statval;

	globval = 1; autoval = 2; regival = 3; volaval = 4; statval =5;

	if(setjmp(jmpbuffer) != 0){
		printf("after longjmp:\n");
		printf("globval=%d, autoval:%d, regival=%d, volaval=%d, statval=%d\n",globval, autoval, regival, volaval, statval);
		exit(0);
	}

	globval = 95; autoval = 96; regival = 97; volaval = 98; statval = 99;
	
	f1(autoval, regival, volaval, statval);
	return 0;
}

void f1(int autoval, int regival, int volaval, int statval)
{
	printf("in f1():\n");
	printf("globval=%d, autoval:%d, regival=%d, volaval=%d, statval=%d\n",globval, autoval, regival, volaval, statval);
	f2();
}

void f2(void)
{
	longjmp(jmpbuffer, 1);
}
