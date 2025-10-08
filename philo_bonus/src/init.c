/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:39:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/08 19:39:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_sim	*sim(void)
{
	static t_sim	sim;

	return (&sim);
}

t_ph	*ph(void)
{
	static t_ph	ph;

	return (&ph);
}

static bool	init_sems(void)
{
	sem_t	*sem;

	sem = sem_open("/print", O_CREAT, 0644, 1);
	sim()->sems->print = sem;
	sem = sem_open("/forks", O_CREAT, 0644, sim()->n_philos);
	sim()->sems->forks = sem;
	if (sim()->n_philos % 2 == 0)
		sem = sem_open("/table", O_CREAT, 0644, sim()->n_philos / 2);
	else
		sem = sem_open("/table", O_CREAT, 0644, sim()->n_philos / 2 + 1);
	sim()->sems->table = sem;
	sem = sem_open("/meals", O_CREAT, 0644, 0);
	sim()->sems->meals = sem;
	sem = sem_open("/end_sim", O_CREAT, 0644, 0);
	sim()->sems->end = sem;
	if (sim()->sems->forks == SEM_FAILED || sim()->sems->print == SEM_FAILED
		|| sim()->sems->forks == SEM_FAILED || sim()->sems->print == SEM_FAILED
		|| sim()->sems->end == SEM_FAILED)
		return (p_error("error opening semaphore\n"), false);
	return (true);
}

bool	ft_init(char **av)
{
	sim()->n_philos = ft_atoi(av[1]);
	sim()->t_die = ft_atoi(av[2]);
	sim()->t_eat = ft_atoi(av[3]);
	sim()->t_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		sim()->n_meals = ft_atoi(av[5]);
	else
		sim()->n_meals = -1;
	sim()->begin_time = time_ms();
	sim()->processes = 0;
	sim()->child_pids = ft_calloc(sim()->n_philos + 2, sizeof(pid_t));
	if (!sim()->child_pids)
		return (p_error("malloc() error\n"), false);
	sim()->sems = ft_calloc(1, sizeof(t_sem));
	if (!sim()->sems)
		return (p_error("malloc() error\n"), false);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	sem_unlink("/meals");
	sem_unlink("/end_sim");
	if (!init_sems())
		return (false);
	return (true);
}
