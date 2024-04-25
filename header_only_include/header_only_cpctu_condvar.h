#ifndef __cplusplus
#ifndef Included_header_only_cpctu_condvar_h
#define Included_header_only_cpctu_condvar_h
#include<stdlib.h>
#include<cpctu_condvar.h>
cpctu_condition_variable cpctu_create_cv(void)
{
#ifdef _WIN32
#else
	pthread_cond_t cv, *cvp = NULL;
	if(pthread_cond_init(&cv, NULL) == 0)
		cvp = malloc(sizeof(*cvp));
	if(cvp != NULL)
		*cvp = cv;
	return cvp;
#endif
}
void cpctu_destroy_cv(cpctu_condition_variable cv)
{
#ifdef _WIN32
#else
	pthread_cond_destroy(cv);
	free(cv);
#endif
}
int cpctu_notify_all(cpctu_condition_variable cv)
{
#ifdef _WIN32
#else
	return pthread_cond_broadcast(cv);
#endif
}
int cpctu_notify_one(cpctu_condition_variable cv)
{
#ifdef _WIN32
#else
	return pthread_cond_signal(cv);
#endif
}
int cpctu_timedwait(cpctu_condition_variable cv, cpctu_mutex m, long seconds, int nanos)
{
#ifdef _WIN32
#else
	struct timespec tm;
	tm.tv_nsec = nanos;
	tm.tv_sec = seconds;
	return pthread_cond_timedwait(cv, m, &tm);
#endif
}
int cpctu_wait(cpctu_condition_variable cv, cpctu_mutex m)
{
#ifdef _WIN32
#else
	return pthread_cond_wait(cv, m);
#endif
}
#endif
#endif
