#include "../philosophers.h"

void safe_join(t_thread *th)
{
    if (th->created)
        pthread_join(th->thread, NULL);
}

static int safe_thread_create(t_thread *th, void *(*routine)(void *), void *arg)
{
    if (pthread_create(&th->thread, NULL, routine, arg) == 0)
        th->created = 1;
	else
    {
        state()->status = 0;
        mutex_unlock(&state()->status_mutex);
		return (1);
    }
	return (0);
}

int	create_all_threads(void)
{
	int	i;

	i = 0;
    mutex_lock(&state()->status_mutex);
	while (i < state()->number_of_philos)
	{
		if (safe_thread_create(&philo(i)->thread, &philo_routine, philo(i)) != 0)
			return (1);
		i++;
	}
	if (safe_thread_create(&state()->monitor, &state_routine, state()->philos) != 0)
		return (1);
    state()->status = 1;
    if(state()->time_to_die == 0)
        state()->status = 0;
    state()->begin_time = time_ms();
    mutex_unlock(&state()->status_mutex);
	return (0);
}
