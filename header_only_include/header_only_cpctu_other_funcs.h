#ifndef __cplusplus
#ifndef Included_header_only_cpctu_other_funcs_h
#define Included_header_only_cpctu_other_funcs_h
#include<cpctu_other_funcs.h>
// initial function to call, fork function, inital function arg, fork function arg
// calls the initial function, when it returns, the fork function is called on a different thread
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa)
{
	// label to the beginning
	lttb:
	iftc(ifa);
	cpctu_create_thread(ff, ffa);
	goto lttb;
}
#endif
#endif
