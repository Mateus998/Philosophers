/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/01 17:41:03 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		pthread_mutex_init(&state()->philos[i].last_meal_mutex, NULL);
		pthread_mutex_init(&state()->philos[i].meals_mutex, NULL);
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
	pthread_create(&state()->monitor, NULL, &state_rotine, state()->philos);
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
*/
