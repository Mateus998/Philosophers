/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:01:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/28 12:09:35 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_state(char **av, int ac)
{
	state()->number_of_philos = ft_atoi(av[1]);
	if (state()->number_of_philos == 0)
		exit(21);
	state()->time_to_die = ft_atoi(av[2]);
	state()->time_to_eat = ft_atoi(av[3]);
	state()->time_to_sleep = ft_atoi(av[4]);
	state()->begin_time = time_ms();
	if (ac == 6)
		state()->number_of_meals = ft_atoi(av[5]);
	else
		state()->number_of_meals = -1;
	state()->forks = ft_calloc(state()->number_of_philos,
			sizeof(pthread_mutex_t));
	if (!state()->forks)
		exit(22);
	state()->status = 1;
}

t_state	*state(void)
{
	static t_state	state;
	return (&state);
}

void	init_philos(void)
{
	int	i;

	state()->philos = ft_calloc(state()->number_of_philos, sizeof(t_philo));
	if (!state()->philos)
		exit(31);
	i = 0;
	while (i < state()->number_of_philos)
	{
		state()->philos[i].id = i + 1;
		state()->philos[i].meals = 0;
		state()->philos[i].last_meal = time_ms();
		state()->philos[i].left_fork = &state()->forks[i];
		state()->philos[i].right_fork = &state()->forks[(i + 1)
			% state()->number_of_philos];
		i++;
	}
}

t_philo	*philo(int i)
{
	if (i < 0 || i >= state()->number_of_philos)
		return (NULL);
	return (&state()->philos[i]);
}
