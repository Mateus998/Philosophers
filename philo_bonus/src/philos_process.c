/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:50:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/09 11:25:05 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	partial_usleep(int time)
{
	long	start;

	if (time < 0)
	{
		return ;
	}
	start = time_ms();
	while ((time_ms() - start) < time)
	{
		if (time_ms() - ph()->last_meal >= sim()->t_die)
		{
			sem_wait(sim()->sems->print);
			printf("%ld %i %s\n", time_ms() - sim()->begin_time, ph()->id,
				"has died");
			sem_post(sim()->sems->end);
		}
		usleep(1000);
	}
}

void	initial_check(int i)
{
	ph()->id = i;
	ph()->meals = sim()->n_meals;
	ph()->last_meal = time_ms();
	if (sim()->n_meals == 0)
		sem_post(sim()->sems->meals);
	if (sim()->n_philos == 1)
	{
		sem_wait(sim()->sems->forks);
		print_terminal(1, "has taken a fork");
		partial_usleep(sim()->t_die * 2);
	}
}

void	philos_process(int i)
{
	initial_check(i);
	while (true)
	{
		sem_wait(sim()->sems->table);
		sem_wait(sim()->sems->forks);
		print_terminal(i, "has taken a fork");
		sem_wait(sim()->sems->forks);
		print_terminal(i, "has taken a fork");
		print_terminal(i, "is eating");
		partial_usleep(sim()->t_eat);
		ph()->last_meal = time_ms();
		sem_post(sim()->sems->forks);
		sem_post(sim()->sems->forks);
		sem_post(sim()->sems->table);
		if (ph()->meals > 0 && --ph()->meals == 0)
			sem_post(sim()->sems->meals);
		print_terminal(i, "is sleeping");
		partial_usleep(sim()->t_sleep);
		print_terminal(i, "is thinking");
		partial_usleep((sim()->t_die - sim()->t_eat - sim()->t_sleep) / 2);
	}
}

bool	processes_creation(void)
{
	int	i;

	while (sim()->processes <= sim()->n_philos + 1)
	{
		sim()->child_pids[sim()->processes] = fork();
		if (sim()->child_pids[sim()->processes] == -1)
			return (p_error("fork() error\n"), false);
		if (sim()->child_pids[sim()->processes] == 0)
		{
			if (sim()->processes == 0)
				monitoring_death();
			else if (sim()->processes == 1)
				monitoring_meals();
			else
				philos_process(sim()->processes - 1);
		}
		sim()->processes++;
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i <= sim()->n_philos + 1)
		kill(sim()->child_pids[i++], SIGKILL);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (true);
}
