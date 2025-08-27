/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/27 17:41:22 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		// pthread_mutex_init(&philo(i)->last_meal_mutex, NULL);
		// pthread_mutex_init(&philo(i)->meals_mutex, NULL);
		pthread_mutex_init(&state()->forks[i++], NULL);
	}
	pthread_mutex_init(&state()->print_mutex, NULL);
	pthread_mutex_init(&state()->status_mutex, NULL);
}

static void	thread_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		pthread_create(&philo(i)->thread, NULL, &philo_rotine, philo(i));
		i++;
	}
	// pthread_create(&state()->control, NULL, &check_rotine, state()->philos);
}

int	loop_check(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2, t_philo *philo)
{
	long philo_life;
	
	pthread_mutex_lock(&state()->status_mutex);
	philo_life = time_ms() - philo->last_meal;
	if (state()->status == 1 && philo_life < state()->time_to_die)
	{
		pthread_mutex_unlock(&state()->status_mutex);
		return (1);
	}
	if (philo_life >= state()->time_to_die)
	{
		pthread_mutex_lock(&state()->print_mutex);
		printf("%ld %i %s\n", time_ms() - state()->begin_time, philo->id, "has died");
		state()->status = 0;
		pthread_mutex_unlock(&state()->print_mutex);
	}
	if (mutex1)
		pthread_mutex_unlock(mutex1);
	if (mutex2)
		pthread_mutex_unlock(mutex2);
	pthread_mutex_unlock(&state()->status_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (init_state(av, ac))
		return (1);
	if (init_philos())
		return (free(state()->forks), 1);
	mutex_init();
	thread_init();
	ft_clean();
	return (0);
}
/*
notes
singleton philo(id) nao funcionou dentro de loop_check....?
protect the pthread functions? use exit and general close/clean
delay on the creation of the thread comum a todos?
odd number of philos is the same logic for even num, the initial delay works for both?
create checker for args
clean comments

problems
erros on valgrind with flags
*/
