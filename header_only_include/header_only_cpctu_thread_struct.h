#ifndef __cplusplus
#ifndef Included_header_only_cpctu_thread_struct_h
#define Included_header_only_cpctu_thread_struct_h
#ifdef _WIN32
#include<synchapi.h>
#include<winnt.h>
typedef unsigned(*cpctu_func_type)(void*);
#elif defined __linux__
typedef void*(*cpctu_func_type)(void*);
#endif
#include<cpctu_thread_struct.h>
struct thsocpctu
{
#ifdef _WIN32
	uintptr_t th;
#elif defined __linux__
	pthread_t th;
#endif
};
#ifdef _WIN32
unsigned
#elif defined __linux__
cpctu_arg_type
#endif
func_to_call(cpctu_arg_type arg)
{
	cpctu_arg_type *aa = arg;
	// actual function to be called
	cpctu_func_type *aftbc = ++aa;
	(*aftbc)(--aa);
#ifdef _WIN32
	return 0;
#elif defined __linux__
	return NULL;
#endif
}
cpctu_thread cpctu_create_thread(void(*ftc)(cpctu_arg_type), cpctu_arg_type arg)
{
	cpctu_thread th = malloc(sizeof(cpctu_thread));
#ifdef _WIN32
	th->th = _beginthread(ftc, 0, arg);
#elif defined __linux__
	pthread_create(th, NULL, ftc, arg);
#endif
	return th;
}
void cpctu_join_thread(cpctu_thread th)
{
#ifdef _WIN32
	// handle to windows thread
	HANDLE htwth = (HANDLE)th->th;
	WaitForSingleObject(htwth, 0xffffffff);
#elif defined __linux__
	pthread_join(th->th, NULL);
#endif
}
#endif
#endif
