#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int	g = 0;

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec/1000);
}

void *mythread(void *arg)
{
	int	myid = getpid();
	static int s = 0;

	++g;
	++s;
	printf("Thread ID:%d, Static: %d, Global:%d\n", myid, s, g);
	return (NULL);
}

int	main(void)
{
	uint64_t	start_time;
	uint64_t	time_now;

	start_time= get_time();
	usleep(10000);
	time_now = get_time();
	printf("time: %ld\n", time_now - start_time);

	pthread_t	thread;
	int		i;

	i = 0;
	printf ("Hello from main\n");
	while (i < 3)
	{
		pthread_create(&thread, NULL, mythread, NULL);
		++i;
	}
	pthread_exit(NULL);
	printf("Thread finished\n");
	return (0);
}