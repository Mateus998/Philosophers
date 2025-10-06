/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:50:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 16:54:06 by mateferr         ###   ########.fr       */
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
			child_exit(1);
		usleep(500);
	}
}

void	initial_check(int i)
{
	ph()->id = i;
	ph()->meals = sim()->n_meals;
	ph()->last_meal = time_ms();
	if (sim()->n_meals == 0)
		sem_post(sim()->sem_meals);
	if (sim()->n_philos == 1)
	{
		sem_wait(sim()->sem_forks);
		print_terminal(1, "has taken a fork");
		partial_usleep(sim()->t_die * 2);
	}
}

void	philos_child_process(int i)
{
	initial_check(i);
	while (true)
	{
		sem_wait(sim()->sem_table);
		sem_wait(sim()->sem_forks);
		print_terminal(i, "has taken a fork");
		sem_wait(sim()->sem_forks);
		print_terminal(i, "has taken a fork");
		sem_post(sim()->sem_table);
		ph()->last_meal = time_ms();
		print_terminal(i, "is eating");
		partial_usleep(sim()->t_eat);
		sem_post(sim()->sem_forks);
		sem_post(sim()->sem_forks);
		if (sim()->n_meals > -1 && --ph()->meals <= 0)
			sem_post(sim()->sem_meals);
		print_terminal(i, "is sleeping");
		partial_usleep(sim()->t_sleep);
		print_terminal(i, "is thinking");
		partial_usleep((sim()->t_die - sim()->t_eat - sim()->t_sleep) / 2);
	}
	child_exit(0);
}

void	meals_check_child(void)
{
	int	i;

	i = 0;
	sem_wait(sim()->sem_meals);
	while (i++ < sim()->n_meals)
		sem_wait(sim()->sem_meals);
	sem_close(sim()->sem_forks);
	sem_close(sim()->sem_print);
	sem_close(sim()->sem_table);
	sem_close(sim()->sem_meals);
	free(sim()->child_pids);
	exit(2);
}

void	wait_processes(void)
{
	int	status;
	int	i;

	while (waitpid(-1, &status, 0) > 0)
	{
		status = exit_status_return(status);
		if (status != 0)
		{
			i = 0;
			while (i < sim()->n_philos)
				kill(sim()->child_pids[i++], SIGKILL);
			while (waitpid(-1, NULL, 0) > 0);
		}
	}
}

bool	processes_creation(void)
{
	while (sim()->processes <= sim()->n_philos)
	{
		sim()->child_pids[sim()->processes] = fork();
		if (sim()->child_pids[sim()->processes] == -1)
			return (p_error("fork() error\n"), false);
		if (sim()->child_pids[sim()->processes] == 0)
		{
			if (sim()->processes == 0)
				meals_check_child();
			else
				philos_child_process(sim()->processes);
		}
		sim()->processes++;
	}
    wait_processes();
	return (true);
}
