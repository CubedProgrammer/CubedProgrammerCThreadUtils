#ifndef __cplusplus
#ifndef Included_cpctu_pool_h
#define Included_cpctu_pool_h
#include<cpctu_thread_struct.h>
#include<cpctu_condvar.h>
#define CPCTU_SMALL_POOL_SIZE 16

typedef struct cpctu_pool
{
	union
	{
		cpctu_thread small[CPCTU_SMALL_POOL_SIZE];
		cpctu_thread *big;
	}th;
	union
	{
		cpctu_condition_variable small[CPCTU_SMALL_POOL_SIZE];
		cpctu_condition_variable *big;
	}cv;
	union
	{
		cpctu_mutex small[CPCTU_SMALL_POOL_SIZE];
		cpctu_mutex *big;
	}m;
	union
	{
		unsigned short small;
		unsigned char *big;
	}fini;
	cpctu_condition_variable runcv;
	cpctu_mutex runm;
	unsigned cnt;
}cpctu_pool;

typedef void(*cpctu_pool_func)(cpctu_arg_type, unsigned);

int cpctu_init_pool(cpctu_pool *pool, unsigned cnt);
void cpctu_destroy_pool(cpctu_pool *pool);
void cpctu_run_pool(cpctu_pool *pool, cpctu_pool_func f, cpctu_arg_type arg);
void cpctu_join_pool(cpctu_pool *pool);

#endif
#endif
