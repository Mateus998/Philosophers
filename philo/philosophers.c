/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/26 19:18:22 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_init(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
	{
		pthread_mutex_init(&philo(i)->last_meal_mutex, NULL);
		pthread_mutex_init(&philo(i)->meals_mutex, NULL);
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
	pthread_create(&state()->control, NULL, &check_rotine, state()->philos);
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
protect the pthread functions?
delay on the creation of the thread comum a todos
odd number of philos is the same logic for even num, the initial delay works for both
1 philo must have a check to not deadlock
create checker for args

problems
filosofo morre em condicoes ideais quando codigo tem variavel numero de refeicoes
*/
