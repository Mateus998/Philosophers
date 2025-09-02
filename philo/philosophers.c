/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/02 12:50:16 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void error_exit_mutex(int id, int mutex, int error_val)
{
	if (mutex <= 3)
	{
		if (mutex > 1)
			pthread_mutex_destroy(&state()->philos[id].last_meal_mutex);
		if (mutex == 3)
			pthread_mutex_destroy(&state()->philos[id].meals_mutex);
		id--;
	}
	while (id-- >= 0)
	{
		pthread_mutex_destroy(&state()->philos[id].last_meal_mutex);
		pthread_mutex_destroy(&state()->philos[id].meals_mutex);
		pthread_mutex_destroy(&state()->forks[id]);
	}
	if (mutex == 4 || mutex == 5)
		pthread_mutex_destroy(&state()->print_mutex);
	if (mutex == 5)
		pthread_mutex_destroy(&state()->status_mutex);
	free(state()->philos);
	free(state()->forks);
	exit(error_val + mutex);
}

static void	mutex_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		if (pthread_mutex_init(&state()->philos[i].last_meal_mutex, NULL) != 0)
			error_exit_mutex(--i, 1, 40);
		if (pthread_mutex_init(&state()->philos[i].meals_mutex, NULL) != 0)
			error_exit_mutex(--i, 2, 40);
		if (pthread_mutex_init(&state()->forks[i++], NULL) != 0)
			error_exit_mutex(--i, 3, 40);
	}
	if (pthread_mutex_init(&state()->print_mutex, NULL) != 0)
		error_exit_mutex(--i, 4, 40);
	if (pthread_mutex_init(&state()->status_mutex, NULL) != 0)
		error_exit_mutex(--i, 5, 40);
}

void error_exit_thread(int id, int thread)
{
	while (id-- >= 0)
		pthread_join(philo(id)->thread, NULL);
	if (thread == 2)
		pthread_join(state()->monitor, NULL);
	error_exit_mutex(state()->number_of_philos - 1, 5, 50);
}

static void	thread_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		if (pthread_create(&philo(i)->thread, NULL, &philo_rotine, philo(i)) != 0)
			error_exit_thread(--i, 1);
		i++;
	}
	if (pthread_create(&state()->monitor, NULL, &state_rotine, state()->philos) != 0)
		error_exit_thread(--i, 2);
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
	ft_clean(0);
	return (0);
}

