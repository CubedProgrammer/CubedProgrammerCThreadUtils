#ifndef __cplusplus
#ifndef Included_header_only_cpctu_thread_struct_h
#define Included_header_only_cpctu_thread_struct_h
#ifdef _WIN32
#include<synchapi.h>
#include<winnt.h>
//#elif defined __linux__
#endif
#include<cpctu_thread_struct.h>
struct thsocpctu
{
#ifdef _WIN32
	uintptr_t th;
#elif defined __linux__
	pthread_t th;
#endif
	cpctu_arg_type aarg;
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
	cpctu_func_type *aftbc = (cpctu_func_type*)++aa;
	(*aftbc)(--aa);
#ifdef _WIN32
	return 0;
#elif defined __linux__
	return NULL;
#endif
}
cpctu_thread cpctu_create_thread(cpctu_func_type ftc, cpctu_arg_type arg)
{
	cpctu_thread th = malloc(sizeof(cpctu_thread));
	th->aarg = malloc(sizeof(cpctu_func_type*) + sizeof(cpctu_arg_type));
	// pointer to arg and pointer to func
	void **pta = (void**)th->aarg;
	cpctu_func_type *ptf = (cpctu_func_type*)(pta + 1);

	*pta = arg;
	*ptf = ftc;
#ifdef _WIN32
	th->th = _beginthreadex(NULL, 0, &func_to_call, th->aarg, 0, NULL);
#elif defined __linux__
	pthread_create(&func_to_call, NULL, ftc, th->aarg);
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
