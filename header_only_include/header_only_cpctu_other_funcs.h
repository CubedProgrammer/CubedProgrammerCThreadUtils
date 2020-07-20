#ifndef __cplusplus
#ifndef Included_header_only_cpctu_other_funcs_h
#define Included_header_only_cpctu_other_funcs_h
#include<cpctu_other_funcs.h>
// cpctu fork helper
struct cfh
{
	cpctu_thread th;
	struct cfh *prev;
};
// first cpctu fork helper
struct cfh *fcfh;
void cpctu_init_fork(void)
{
	fcfh = malloc(sizeof(struct cfh));
	fcfh->prev = NULL;
	fcfh->th = NULL;
}
// initial function to call, fork function, inital function arg, fork function arg
// calls the initial function, when it returns, the fork function is called on a different thread
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa)
{
	// label to the beginning
	lttb:
	iftc(ifa);
	cpctu_thread th = cpctu_create_thread(ff, ffa);

	if(fcfh->th == NULL)
		fcfh->th = th;
	else
	{
		struct cfh *tmp = malloc(sizeof(struct cfh));
		fcfh->prev = fcfh;
		fcfh->th = th;
		fcfh = tmp;
	}

	goto lttb;
}
void cpctu_cleanup_fork(void)
{
	struct cfh *tmp = fcfh;
	while(fcfh->prev)
	{
		fcfh = fcfh->prev;
		free(tmp->th);
		free(tmp);
	}
	free(fcfh);
	fcfh = NULL;
}
#endif
#endif
