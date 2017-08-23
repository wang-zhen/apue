#include "apue.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int ret,i;
	struct stat st;

	if(argc < 2){
		printf("input error!\n");
		exit(-1);
	}


	for(i=1; i < argc; i++){
		ret = lstat(argv[i], &st);
		if(ret == -1){
			perror("lstat error!");
			exit(-1);
		}

		printf("%s: ",argv[i]);
		if(S_ISREG(st.st_mode)){
			printf("reguler\n");
		}else if(S_ISDIR(st.st_mode)){
			printf("dir\n");
		}else if(S_ISBLK(st.st_mode)){
			printf("block\n");
		}else if(S_ISCHR(st.st_mode)){
			printf("char\n");
		}else if(S_ISSOCK(st.st_mode)){
			printf("socket\n");
		}else if(S_ISFIFO(st.st_mode)){
			printf("fifo\n");
		}else if(S_ISLNK(st.st_mode)){
			printf("link\n");
		}
	}
	return 0;
}
