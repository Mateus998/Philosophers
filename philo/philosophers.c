/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:02 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
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
}

int	loop_check(pthread_mutex_t *mutex1, pthread_mutex_t *mutex2, t_philo *philo)
{
	long	philo_life;

	philo_life = time_ms() - philo->last_meal;
	pthread_mutex_lock(&state()->status_mutex);
	if (state()->status == 1 && philo_life < state()->time_to_die)
	{
		pthread_mutex_unlock(&state()->status_mutex);
		return (1);
	}
	pthread_mutex_lock(&state()->print_mutex);
	if (philo_life >= state()->time_to_die)
	{
		printf("%ld %i %s\n", time_ms() - state()->begin_time, philo->id,
			"has died");
		state()->status = 0;
	}
	pthread_mutex_unlock(&state()->status_mutex);
	pthread_mutex_unlock(&state()->print_mutex);
	if (mutex1)
		pthread_mutex_unlock(mutex1);
	if (mutex2)
		pthread_mutex_unlock(mutex2);
	return (0);
}

int	main(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
		check_arg(av[i++]);
	init_state(av, ac);
	init_philos();
	mutex_init();
	thread_init();
	ft_clean();
	return (0);
}
/*
notes
protect the pthread functions? achar forma de identificar 
var mutex e/ou thread em uso

problems
cortar terminal logo na primeira morte
*/
