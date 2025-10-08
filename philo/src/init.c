/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:01:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 11:33:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	init_state(char **av, int ac)
{
	sim()->n_philos = ft_atoi(av[1]);
	if (sim()->n_philos == 0)
		return (1);
	sim()->t_die = ft_atoi(av[2]);
	sim()->t_eat = ft_atoi(av[3]);
	sim()->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		sim()->n_meals = ft_atoi(av[5]);
	else
		sim()->n_meals = -1;
	sim()->status = 2;
	sim()->forks = ft_calloc(sim()->n_philos, sizeof(t_mutex));
	if (!sim()->forks)
		return (1);
	return (0);
}

t_sim	*sim(void)
{
	static t_sim	state;

	return (&state);
}

int	init_philos(void)
{
	int	i;

	sim()->philos = ft_calloc(sim()->n_philos, sizeof(t_philo));
	if (!sim()->philos)
		return (free(sim()->forks), 1);
	i = 0;
	while (i < sim()->n_philos)
	{
		sim()->philos[i].id = i + 1;
		sim()->philos[i].meals = 0;
		sim()->philos[i].last_meal = time_ms();
		sim()->philos[i].left_fork = &sim()->forks[i];
		sim()->philos[i].right_fork = &sim()->forks[(i + 1)
		% sim()->n_philos];
		i++;
	}
	return (0);
}

t_philo	*philo(int i)
{
	if (i < 0 || i >= sim()->n_philos)
		return (NULL);
	return (&sim()->philos[i]);
}
