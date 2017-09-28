SRCS =$(wildcard *.c)
OBJS =$(patsubst %.c,%,$(SRCS))

C = gcc
CFLAGS = -lpthread -Wall -O -g -o

.PHONY:all clean

all:$(OBJS)
%:%.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -f $(OBJS)
