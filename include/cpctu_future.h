#ifndef __cplusplus
#ifndef Included_cpctu_future_h
#define Included_cpctu_future_h
#include <cpctu_other_funcs.h>
#define cpctu_future_type(ret, arg)struct cpctu_future_func_truearg_##ret##_##arg{ret(*func)(arg);ret retval;arg val;};void cpctu_call_future_##ret##_##arg(void *vp){struct cpctu_future_func_truearg_##ret##_##arg *ptr = vp;ptr->retval = ptr->func(ptr->val);}cpctu_future cpctu_true_async_##ret##_##arg(ret(*func)(arg), arg aval){struct cpctu_future f;struct cpctu_future_func_truearg_##ret##_##arg *truearg = malloc(sizeof(*truearg));truearg->func = func;truearg->val = aval;f.th = cpctu_create_thread(cpctu_call_future_##ret##_##arg, truearg);f.x = truearg;f.func = NULL;return f;}ret cpctu_retrieve_##ret##_##arg(cpctu_future f){if(f.func == NULL) cpctu_join_thread(f.th);else f.func(f.x);struct cpctu_future_func_truearg_##ret##_##arg *truearg = f.x;ret v = truearg->retval;free(truearg);return v;}
struct cpctu_future
{
	struct thsocpctu *th;
	void *x;
	void(*func)(void*);
};
typedef struct cpctu_future cpctu_future;
#endif
#endif
