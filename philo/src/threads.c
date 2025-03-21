#include "../include/philosophers.h"

static void	handle_thread_error(int	ret_val, t_mutex_code code)
{
	if (ret_val == 0)
		return ;
	if (EINVAL == ret_val)
		error_and_exit(RED"No resources to create another thread"RESET);
	else if (EPERM == ret_val)
		error_and_exit(RED"The caller does not have appropriate permission"RESET);
	else if (EINVAL == ret_val && code == CREATE)
		error_and_exit(RED"The value specified by attr is invalid"RESET);
	else if (EINVAL == ret_val && (code == JOIN || code == DETACH))
		error_and_exit(RED"The value specified by thread is not joinable"RESET);
	else if (ESRCH == ret_val)
		error_and_exit(RED"No thread could be found"RESET);
	else if (EDEADLK == ret_val)
		error_and_exit(RED"Deadlock would occur if the thread blocked was waiting for a mutex"RESET);
	
	
}

void	thread_handle(pthread_t *thread, void *(*routine)(void *), void *table, t_mutex_code code)
{

	if (code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, routine, table), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else
		error_and_exit(RED"Invalid mutex code"RESET);
}