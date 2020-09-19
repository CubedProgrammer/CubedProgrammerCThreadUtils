#ifndef __cplusplus
#ifndef Included_header_only_cpctu_other_funcs_h
#define Included_header_only_cpctu_other_funcs_h
#include<stdio.h>
#include<cpctu_other_funcs.h>
#ifdef _WIN32
#include<synchapi.h>
#elif defined __linux__
#include<unistd.h>
#endif
void cpctu_sleep_thread(int millis)
{
#ifdef _WIN32
	Sleep(millis);
#elif defined __linux__
	usleep(millis * 1000);
#endif
}

// cpctu fork helper
struct cfh
{
	cpctu_thread th;
	struct cfh *prev;
};

// first cpctu fork helper
struct cfh *cpctu____glv__fcfh;
// fork status
volatile int cpctu____glv__fs = 1;

void cpctu_init_fork(void)
{
	cpctu____glv__fcfh = malloc(sizeof(struct cfh));
	cpctu____glv__fcfh->prev = NULL;
	cpctu____glv__fcfh->th = NULL;
}
int cpctu_fork_status(void)
{
	return cpctu____glv__fcfh ? 0 : 1;
}
// initial function to call, fork function, inital function arg, fork function arg
// calls the initial function, when it returns, the fork function is called on a different thread
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa)
{
	fflush(stdout);
	cpctu____glv__fs = 0;
	// label to the beginning
	lttb:
	iftc(ifa);
	cpctu_thread th = cpctu_create_thread(ff, ffa);
	fflush(stdout);

	if(cpctu____glv__fcfh->th == NULL)
		cpctu____glv__fcfh->th = th;
	else
	{
		struct cfh *tmp = malloc(sizeof(struct cfh));
		cpctu____glv__fcfh->prev = cpctu____glv__fcfh;
		cpctu____glv__fcfh->th = th;
		cpctu____glv__fcfh = tmp;
	}

	fflush(stdout);
	if(cpctu____glv__fs == 0)
		goto lttb;
}
void cpctu_cleanup_fork(void)
{
	cpctu____glv__fs = 1;
	cpctu_sleep_thread(1000);
	struct cfh * volatile tmp = cpctu____glv__fcfh;
	while(cpctu____glv__fcfh->prev)
	{
		cpctu____glv__fcfh = cpctu____glv__fcfh->prev;
		cpctu_join_thread(tmp->th);
		free(tmp->th);
		free(tmp);
	}
	free(cpctu____glv__fcfh);
	cpctu____glv__fcfh = NULL;
}
#endif
#endif
