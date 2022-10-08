#ifndef __cplusplus
#ifndef Included_cpctu_thread_struct_h
#define Included_cpctu_thread_struct_h
#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#elif defined __unix__ || defined __APPLE__
#include <pthread.h>
#endif
// thread struct of cpctu
struct thsocpctu;
struct thsocpctu *cpctu_create_thread(void(*ftc)(void *), void *arg);
void cpctu_detach(struct thsocpctu *th);
void cpctu_join_thread(struct thsocpctu *th);
// typedefs
typedef struct thsocpctu*cpctu_thread;
typedef void*cpctu_arg_type;
typedef void(*cpctu_func_type)(void*);
#endif
#endif
