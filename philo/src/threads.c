#include "../include/philosophers.h"

void	thread_handle(pthread_t *thread, void *(*routine)(void *), void *table, t_mutex_code code)
{

	if (code == CREATE)
		pthread_create(thread, NULL, routine, table);
	else if (code == JOIN)
		pthread_join(*thread, NULL);
	else if (code == DETACH)
		pthread_detach(*thread);
	else
		error_and_exit(RED"Invalid mutex code"RESET);
}