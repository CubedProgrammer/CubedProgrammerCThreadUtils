#ifndef __cplusplus
#ifndef Included_cpctu_other_funcs_h
#define Included_cpctu_other_funcs_h
#include<cpctu_thread_struct.h>
void cpctu_init_fork(void);
void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa);
void cpctu_cleanup_fork(void);
#endif
#endif
