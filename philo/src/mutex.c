#include "../philosophers.h"

void mutex_lock(t_mutex *mtx)
{
    pthread_mutex_lock(&mtx->mutex);
}

void mutex_unlock(t_mutex *mtx)
{
    pthread_mutex_unlock(&mtx->mutex);
}

void safe_mutex_destroy(t_mutex *mtx)
{
    if (mtx->initiated)
        pthread_mutex_destroy(&mtx->mutex);
}

static int safe_mutex_init(t_mutex *mtx)
{
	if (pthread_mutex_init(&mtx->mutex, NULL) == 0)
		mtx->initiated = 1;
	else
		return (1);
	return (0);
}

int	init_all_mutex(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		if (safe_mutex_init(&philo(i)->last_meal_mutex) != 0)
			return (ft_clean(), 1);
		if (safe_mutex_init(&philo(i)->meals_mutex) != 0) //philo() with possible error
			return (ft_clean(), 1);
		if (safe_mutex_init(&state()->forks[i++]) != 0)
			return (ft_clean(), 1);
	}
	if (safe_mutex_init(&state()->print_mutex) != 0)
		return (ft_clean(), 1);
	if (safe_mutex_init(&state()->status_mutex) != 0)
		return (ft_clean(), 1);
	return(0);
}
