#ifndef __cplusplus
#ifndef Included_header_only_cpctu_thread_struct_h
#define Included_header_only_cpctu_thread_struct_h
#include<synchapi.h>
#include<winnt.h>
#include<cpctu_thread_struct.h>
struct thsocpctu
{
#ifdef _WIN32
	uintptr_t th;
#elif defined __linux__
	pthread_t th;
#endif
};
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
