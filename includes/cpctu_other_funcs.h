#ifndef __cplusplus
#ifndef Included_cpctu_other_funcs_h
#define Included_cpctu_other_funcs_h
#include<cpctu_thread_struct.h>
void cpctu_sleep_thread(int millis);
void cpctu_init_fork(void);
int cpctu_fork_status(void);
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa);
void cpctu_cleanup_fork(void);
#endif
#endif
