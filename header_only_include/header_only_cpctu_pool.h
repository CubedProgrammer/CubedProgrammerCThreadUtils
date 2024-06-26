#ifndef __cplusplus
#ifndef Included_header_only_cpctu_pool_h
#define Included_header_only_cpctu_pool_h
#include<cpctu_pool.h>

static inline cpctu_thread *cpctu_pool_get_threads(cpctu_pool *pool)
{
	return pool->cnt > CPCTU_SMALL_POOL_SIZE ? pool->th.big : pool->th.small;
}
static inline cpctu_mutex *cpctu_pool_get_mutexes(cpctu_pool *pool)
{
	return pool->cnt > CPCTU_SMALL_POOL_SIZE ? pool->m.big : pool->m.small;
}
static inline cpctu_condition_variable *cpctu_pool_get_cvs(cpctu_pool *pool)
{
	return pool->cnt > CPCTU_SMALL_POOL_SIZE ? pool->cv.big : pool->cv.small;
}
static inline int cpctu_pool_is_finished(const cpctu_pool *pool, unsigned ind)
{
	return pool->cnt > CPCTU_SMALL_POOL_SIZE ? pool->fini.big[ind] : pool->fini.small >> ind & 1;
}
static inline void cpctu_pool_set_finished(cpctu_pool *pool, unsigned ind, int v)
{
	if(pool->cnt > CPCTU_SMALL_POOL_SIZE)
		pool->fini.big[ind] = v != 0;
	else
	{
		unsigned short mask = (v != 0) << ind;
		pool->fini.small = (pool->fini.small | mask) & mask;
	}
}

int cpctu_init_pool(cpctu_pool *pool, unsigned cnt)
{
	cpctu_thread *th;
	cpctu_mutex *m;
	cpctu_condition_variable *cv;
	int big = cnt > CPCTU_SMALL_POOL_SIZE;
	int succ = -1;
	char allsucc = 1;
	pool->runcv = cpctu_create_cv();
	if(pool->runcv == NULL)
		goto final;
	pool->runm = cpctu_create_mutex();
	if(pool->runm == NULL)
		goto penultimate;
	if(big)
	{
		pool->fini.big = malloc(cnt * sizeof(*pool->fini.big));
		allsucc = pool->cv.big != NULL;
	}
	if(!allsucc)
		goto finiarr;
	if(big)
	{
		cv = pool->cv.big = malloc(cnt * sizeof(*pool->cv.big));
		allsucc = pool->cv.big != NULL;
	}
	else
		cv = pool->cv.small;
	for(unsigned i = 0; allsucc && i < cnt; ++i)
	{
		cv[i] = cpctu_create_cv();
		allsucc = cv[i] != NULL;
	}
	if(!allsucc)
		goto cvarr;
	if(big)
	{
		m = pool->m.big = malloc(cnt * sizeof(*pool->m.big));
		allsucc = pool->m.big != NULL;
	}
	else
		m = pool->m.small;
	for(unsigned i = 0; allsucc && i < cnt; ++i)
	{
		m[i] = cpctu_create_mutex();
		allsucc = m[i] != NULL;
	}
	if(!allsucc)
		goto marr;
	if(big)
	{
		th = pool->th.big = malloc(cnt * sizeof(*pool->th.big));
		allsucc = pool->th.big != NULL;
	}
	else
		th = pool->th.small;
	for(unsigned i = 0; allsucc && i < cnt; ++i)
	{
		//th[i] = cpctu_create_thread();
		allsucc = th[i] != NULL;
	}
	if(allsucc)
		succ = 0;
	if(succ)
	{
		for(unsigned i = 0; i < cnt; ++i)
		{
			if(m[i] != NULL)
				cpctu_destroy_mutex(m[i]);
		}
		if(big)
			free(m);
		marr:
		for(unsigned i = 0; i < cnt; ++i)
		{
			if(cv[i] != NULL)
				cpctu_destroy_cv(cv[i]);
		}
		if(big)
			free(cv);
		cvarr:
		if(big)
			free(pool->fini.big);
		finiarr:
		cpctu_destroy_mutex(pool->runm);
		penultimate:
		cpctu_destroy_cv(pool->runcv);
	}
	final:
	return succ;
}

void cpctu_destroy_pool(cpctu_pool *pool)
{
	cpctu_thread *th;
	cpctu_mutex *m;
	cpctu_condition_variable *cv;
	int dealloc = pool->cnt > CPCTU_SMALL_POOL_SIZE;
	if(dealloc)
	{
		th = pool->th.big;
		m = pool->m.big;
		cv = pool->cv.big;
	}
	else
	{
		th = pool->th.small;
		m = pool->m.small;
		cv = pool->cv.small;
	}
	cpctu_notify_all(pool->runcv);
	for(unsigned i = 0; i < pool->cnt; ++i)
	{
		cpctu_join_thread(th[i]);
		cpctu_destroy_mutex(m[i]);
		cpctu_destroy_cv(cv[i]);
	}
	cpctu_destroy_mutex(pool->runm);
	cpctu_destroy_cv(pool->runcv);
	if(dealloc)
	{
		free(th);
		free(m);
		free(cv);
		free(pool->fini.big);
	}
}
void cpctu_run_pool(cpctu_pool *pool, cpctu_pool_func f, cpctu_arg_type arg)
{
}
void cpctu_join_pool(cpctu_pool *pool)
{
	cpctu_mutex *m = cpctu_pool_get_mutexes(pool);
	cpctu_condition_variable *cv = cpctu_pool_get_cvs(pool);
	for(unsigned i = 0; i < pool->cnt; ++i)
	{
		cpctu_lock(m[i]);
		if(!cpctu_pool_is_finished(pool, i))
			cpctu_wait(cv[i], m[i]);
		cpctu_unlock(m[i]);
	}
}

#endif
#endif
