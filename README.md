# CubedProgrammerCThreadUtils
Threading library for C that works across windows and linux
## cpctu_thread_struct.h
#### typename cpctu_thread
Thread type of this library.
#### typename cpctu_arg_type
Type for arg of functions for the thread, should be void ptr.
#### typename cpctu_func_type
Function type for the thread, should return void and have one `cpctu_arg_type` argument.
#### func cpctu_thread cpctu_create_thread(cpctu_func_type, cpctu_arg_type)
Creates a thread that calls a function with an argument.
#### func void cpctu_join_thread(cpctu_thread)
Joins a thread.
## cpctu_other_funcs.h
#### func void cpctu_sleep_thread(int millis)
Sleeps the calling thread for some time.
#### func void cpctu_init_fork(void)
Initializes thread forking.
#### func int cpctu_fork_status(void)
Returns zero if fork is already initialized.
#### func void cpctu_thread_fork(cpctu_func_type iftc, cpctu_func_type ff, cpctu_arg_type ifa, cpctu_arg_type ffa)
Parameters are initial function, fork function, and their respective arguments.

Calls the function iftc, when it returns, function ff is called in a new thread, and the function iftc is called again, and the process repeats.

This function will block the calling thread, the fork has to be stopped in a different thread.

You cannot call this function more than once in the same process, unless you stop it first.
#### func void cpctu_cleanup_fork(void)
Stops and releases fork resources. This function should be called in a different thread than the thread cpctu_thread_fork was called in.