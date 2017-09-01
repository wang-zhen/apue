#include "apue.h"

#define TOK_ADD 1
#define TOK_DEL 2
#define TOK_ERR 3

void do_line(char *);
void cmd_add(void);
int get_token(void);

/*
 *./7d4 1;2;3;4
 * */
int main(int argc, char *argv[])
{
	char line[MAXLINE];

	while(fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);

	return 0;
}

char *get_ptr;

void do_line(char *ptr)
{
	int cmd;

	get_ptr = ptr;

	while((cmd = get_token()) > 0){
		switch(cmd){
		case TOK_ADD:
			cmd_add();
			break;
		}
	}
}

void cmd_add(void)
{
	int token;

	token = get_token();
}

int get_token(void)
{
	return 0;
}
