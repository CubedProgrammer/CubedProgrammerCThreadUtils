#ifndef __cplusplus
#ifndef Included_header_only_cpctu_thread_struct_h
#define Included_header_only_cpctu_thread_struct_h
#ifdef _WIN32
#include<windows.h>
#elif defined __unix__ || defined __APPLE__
#include<pthread.h>
#endif
#include<cpctu_thread_struct.h>

// struct for threads
struct thsocpctu
{
#ifdef _WIN32
	uintptr_t th;
#elif defined __unix__ || defined __APPLE__
	pthread_t th;
#endif
	cpctu_arg_type aarg;
};

// determines return type of the function
#ifdef _WIN32
unsigned
#elif defined __unix__ || defined __APPLE__
cpctu_arg_type
#endif

// function for thread to call
cpctu____func_to_call(cpctu_arg_type arg)
{
	cpctu_arg_type *aa = arg;
	// actual function to be called
	cpctu_func_type *aftbc = (cpctu_func_type*)++aa;
	(*aftbc)(*--aa);
#ifdef _WIN32
	return 0;
#elif defined __unix__ || defined __APPLE__
	return NULL;
#endif
}

// creates a thread
cpctu_thread cpctu_create_thread(cpctu_func_type ftc, cpctu_arg_type arg)
{
	cpctu_thread th = malloc(sizeof(cpctu_thread));
	th->aarg = malloc(sizeof(cpctu_func_type) + sizeof(cpctu_arg_type));
	// pointer to arg and pointer to func
	void **pta = (void**)th->aarg;
	cpctu_func_type *ptf = (cpctu_func_type*)(pta + 1);

	*pta = arg;
	*ptf = ftc;
#ifdef _WIN32
	th->th = _beginthreadex(NULL, 0, &cpctu____func_to_call, th->aarg, 0, NULL);
#elif defined __unix__ || defined __APPLE__
	pthread_create(&th->th, NULL, cpctu____func_to_call, th->aarg);
#endif
	return th;
}

// joins a thread
void cpctu_join_thread(cpctu_thread th)
{
#ifdef _WIN32
	// handle to windows thread
	HANDLE htwth = (HANDLE)th->th;
	WaitForSingleObject(htwth, 0xffffffff);
#elif defined __unix__ || defined __APPLE__
	pthread_join(th->th, NULL);
#endif
}
#endif
#endif
