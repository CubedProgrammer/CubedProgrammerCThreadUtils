#ifndef __cplusplus
#ifndef Included_header_only_cpctu_mutex_h
#define Included_header_only_cpctu_mutex_h
#include<stdlib.h>
#include<cpctu_mutex.h>
cpctu_mutex cpctu_create_mutex(void)
{
#ifdef _WIN32
	return CreateMutexA(NULL, FALSE, NULL);
#else
	pthread_mutex_t mutex;
	cpctu_mutex m;
	if(pthread_mutex_init(&mutex, NULL))
		m = NULL;
	else
	{
		m = malloc(sizeof(*m));
		*m = mutex;
	}
	return m;
#endif
}
char cpctu_valid_mutex(cpctu_mutex m)
{
	return m != NULL;
}
void cpctu_destroy_mutex(cpctu_mutex m)
{
#ifdef _WIN32
	CloseHandle(m);
#else
	pthread_mutex_destroy(m);
	free(m);
#endif
}
int cpctu_lock(cpctu_mutex m)
{
#ifdef _WIN32
	return WaitForSingleObject(m, INFINITE) != 0;
#else
	return pthread_mutex_lock(m);
#endif
}
int cpctu_timedlock(cpctu_mutex m, long seconds, int nanos)
{
#ifdef _WIN32
	return WaitForSingleObject(m, seconds * 1000 + nanos / 1000000) != 0;
#else
	struct timespec tm;
	tm.tv_nsec = nanos;
	tm.tv_sec = seconds;
	return pthread_mutex_timedlock(m, &tm);
#endif
}
int cpctu_trylock(cpctu_mutex m)
{
#ifdef _WIN32
	return WaitForSingleObject(m, 0) != 0;
#else
	return pthread_mutex_trylock(m);
#endif
}
int cpctu_unlock(cpctu_mutex m)
{
#ifdef _WIN32
	return ReleaseMutex(m) == 0;
#else
	return pthread_mutex_unlock(m);
#endif
}
#endif
#endif
