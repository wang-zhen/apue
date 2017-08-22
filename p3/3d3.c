#include "apue.h"
#include <fcntl.h>

#define BUFDIZE 8096

/*
 *3d3 <inputfile >outputfile
 * */

void set_fl(int fd, int flag)
{
    int val;
    
    if((val = fcntl(fd, F_GETFL, 0)) < 0 ) 
        perror("fcntl f_getfl error");

    val |= flag;

    if(fcntl(fd, F_SETFL, val) < 0)
        perror("fcntl f_setfl error");
}

void clr_fl(int fd, int flag)
{
    int val;
    
    if((val = fcntl(fd, F_GETFL, 0)) < 0 ) 
        perror("fcntl f_getfl error");

    val &= ~flag;

    if(fcntl(fd, F_SETFL, val) < 0)
        perror("fcntl f_setfl error");
}

int main(void)
{
	int len,i=0;
	char buf[BUFDIZE];

	set_fl(STDOUT_FILENO, O_FSYNC);
	while((len = read(STDIN_FILENO, buf, BUFDIZE)) > 0){
		if(write(STDOUT_FILENO, buf, len) != len){
			perror("write error!");
			break;
		}
		i++;
	}

	printf("count:%d\n",i);
	return 0;
}
