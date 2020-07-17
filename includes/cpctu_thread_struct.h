#ifndef __cplusplus
#ifndef Included_cpctu_thread_struct_h
#define Included_cpctu_thread_struct_h
#ifdef _WIN32
#include <process.h>
#elif defined __linux__
#include <pthread.h>
#endif
// thread struct of cpctu
struct thsocpctu;
struct thsocpctu *cpctu_create_thread(void(*ftc)(void *), void *arg);
void cpctu_join_thread(struct thsocpctu *th);
typedef struct thsocpctu*cpctu_thread;
typedef void*cpctu_arg_type;
#endif
#endif
