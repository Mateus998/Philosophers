/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:01:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 15:37:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_state(char **av, int ac)
{
	st()->number_of_philos = ft_atoi(av[1]);
	if (st()->number_of_philos == 0)
		return (1);
	st()->time_to_die = ft_atoi(av[2]);
	st()->time_to_eat = ft_atoi(av[3]);
	st()->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		st()->number_of_meals = ft_atoi(av[5]);
	else
		st()->number_of_meals = -1;
	st()->status = 2;
	st()->forks = ft_calloc(st()->number_of_philos, sizeof(t_mutex));
	if (!st()->forks)
		return (1);
	return (0);
}

t_state	*st(void)
{
	static t_state	state;

	return (&state);
}

int	init_philos(void)
{
	int	i;

	st()->philos = ft_calloc(st()->number_of_philos, sizeof(t_philo));
	if (!st()->philos)
		return (free(st()->forks), 1);
	i = 0;
	while (i < st()->number_of_philos)
	{
		st()->philos[i].id = i + 1;
		st()->philos[i].meals = 0;
		st()->philos[i].last_meal = time_ms();
		st()->philos[i].left_fork = &st()->forks[i];
		st()->philos[i].right_fork = &st()->forks[(i + 1)
			% st()->number_of_philos];
		i++;
	}
	return (0);
}

t_philo	*philo(int i)
{
	if (i < 0 || i >= st()->number_of_philos)
		return (NULL);
	return (&st()->philos[i]);
}
