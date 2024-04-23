#ifndef __cplusplus
#ifndef Included_cpctu_mutex_h
#define Included_cpctu_mutex_h
#ifdef _WIN32
#include<windows.h>
typedef HANDLE cpctu_mutex;
#else
#include<pthread.h>
typedef pthread_mutex_t*cpctu_mutex;
#endif
cpctu_mutex cpctu_create_mutex(void);
char cpctu_valid_mutex(cpctu_mutex m);
void cpctu_destroy_mutex(cpctu_mutex m);
int cpctu_lock(cpctu_mutex m);
int cpctu_timedlock(cpctu_mutex m, long seconds, int nanos);
int cpctu_trylock(cpctu_mutex m);
int cpctu_unlock(cpctu_mutex m);
#endif
#endif
