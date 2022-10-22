#ifndef __cplusplus
#ifndef Included_header_only_cpctu_other_funcs_h
#define Included_header_only_cpctu_other_funcs_h
#include<cpctu_other_funcs.h>
#ifdef _WIN32
#include<windows.h>
#elif defined __unix__ || defined __APPLE__
#include<dirent.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#endif
#include<stdio.h>

// sleeps the thread
void cpctu_sleep_thread(int millis)
{
#ifdef _WIN32
	Sleep(millis);
#else
	usleep(millis * 1000);
#endif
}

// sleep with nanosecond precision
void cpctu_nanosleep_thread(long nanos)
{
#ifdef _WIN32
	Sleep((nanos + 999999) / 1000000);
#else
	struct timespec ts;
	ts.tv_sec = nanos / 1000000000;
	ts.tv_nsec = nanos % 1000000000;
	nanosleep(&ts, NULL);
#endif
}

// count number of threads being used by the current process
int cpctu_count_threads(void)
{
	int cnt = 0;
#ifdef _WIN32
	THREADENTRY32 then, *thenp = &then;
	HANDLE hand = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if(Thread32First(hand, thenp))
	{
		do
			++cnt;
		while(Thread32Next(hand, thenp));
	}
	else
		cnt = -1;
#else
	DIR *dirp = opendir("/proc/self/task");
	if(dirp == NULL)
		cnt = -1;
	else
	{
		cnt = -2;
		struct dirent *en = readdir(dirp);
		while(en)
		{
			++cnt;
			en = readdir(dirp);
		}
		closedir(dirp);
	}
#endif
	return cnt;
}

// Get available threads in the computer, threads used by process do not affect this number
int cpctu_available_threads(void)
{
#ifdef _WIN32
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
#else
	return get_nprocs();
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

// initialize the fork
void cpctu_init_fork(void)
{
	cpctu____glv__fcfh = malloc(sizeof(struct cfh));
	cpctu____glv__fcfh->prev = NULL;
	cpctu____glv__fcfh->th = NULL;
}

// see whether or not the fork has been initialized
// will return zero if it is
int cpctu_fork_status(void)
{
	return cpctu____glv__fcfh ? 0 : 1;
}

// initial function to call, fork function, inital function arg, fork function arg
// calls the initial function, when it returns, the fork function is called on a different thread
// this process is repeated, forever, or until you decide to stop it
// note, this will block the calling thread
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa)
{
	cpctu____glv__fs = 0;
	// label to the beginning
	lttb:
	iftc(ifa);
	cpctu_thread th = cpctu_create_thread(ff, ffa);

	if(cpctu____glv__fcfh->th == NULL)
		cpctu____glv__fcfh->th = th;
	else
	{
		struct cfh *tmp = malloc(sizeof(struct cfh));
		cpctu____glv__fcfh->prev = cpctu____glv__fcfh;
		cpctu____glv__fcfh->th = th;
		cpctu____glv__fcfh = tmp;
	}

	if(cpctu____glv__fs == 0)
		goto lttb;
}

// stops forking threads
// and releases resources used
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
