#include "apueerror.h"
#include <pthread.h>

#define NHASH 29
#define HASH(fp) (((unsigned int)fp)%NHASH)
struct foo *fh[NHASH]

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int f_count;
	pthread_mutex_t f_lock;
	struct foo *f_next;
	int f_id;
};

struct foo *foo_alloc(void)
{
	struct foo *fp;
	int idx;

	if((fp = malloc(sizeof(struct foo))) == NULL)
		err_sys("malloc error");

	fp->f_count = 1;
	idx = HASH(fp);
	pthread_mutex_lock(&hashlock);
	fp->f_next = fh[idx];
	fh[idx] = fp;
	pthread_mutex_lock(&fp->f_lock);
	pthread_mutex_unlock(&hashlock);
	pthread_mutex_unlock(&fp->f_lock);

	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_find(int id)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if(fp->f_count-- == 0){
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}else
		pthread_mutex_unlock(&fp->f_lock);

}

int main(void)
{
	return 0;
}
