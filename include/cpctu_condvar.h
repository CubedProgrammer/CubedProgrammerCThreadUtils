#ifndef __cplusplus
#ifndef Included_cpctu_condvar_h
#define Included_cpctu_condvar_h
#include<cpctu_mutex.h>
#ifdef _WIN32
typedef CONDITION_VARIABLE cpctu_condition_variable;
#else
typedef pthread_cond_t*cpctu_condition_variable;
#endif
cpctu_condition_variable cpctu_create_cv(void);
void cpctu_destroy_cv(cpctu_condition_variable cv);
int cpctu_notify_all(cpctu_condition_variable cv);
int cpctu_notify_one(cpctu_condition_variable cv);
int cpctu_timedwait(cpctu_condition_variable cv, cpctu_mutex m, long seconds, int nanos);
int cpctu_wait(cpctu_condition_variable cv, cpctu_mutex m);
#endif
#endif
