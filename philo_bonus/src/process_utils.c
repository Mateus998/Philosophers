/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:39:31 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/08 18:56:45 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	monitoring_meals(void)
{
	int	i;

	i = 0;
	while (i < sim()->n_philos)
	{
		sem_wait(sim()->sems->meals);
		i++;
	}
	sem_close(sim()->sems->forks);
	sem_close(sim()->sems->print);
	sem_close(sim()->sems->table);
	sem_close(sim()->sems->meals);
	sem_close(sim()->sems->end);
	free(sim()->sems);
	free(sim()->child_pids);
	exit(2);
}

void	monitoring_death(void)
{
	sem_wait(sim()->sems->end);
	sem_close(sim()->sems->forks);
	sem_close(sim()->sems->print);
	sem_close(sim()->sems->table);
	sem_close(sim()->sems->meals);
	sem_close(sim()->sems->end);
	free(sim()->sems);
	free(sim()->child_pids);
	exit(1);
}

long	time_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

void	print_terminal(int i, char *msg)
{
	if (time_ms() - ph()->last_meal >= sim()->t_die)
	{
		sem_wait(sim()->sems->print);
		printf("%ld %i %s\n", time_ms() - sim()->begin_time, ph()->id,
			"has died");
		sem_post(sim()->sems->end);
	}
	sem_wait(sim()->sems->print);
	printf("%ld %i %s\n", time_ms() - sim()->begin_time, i, msg);
	sem_post(sim()->sems->print);
}

bool	validate_args(char **av)
{
	long	n;
	char	*ptr;

	while (*++av != NULL)
	{
		ptr = *av;
		while (*ptr != '\0')
		{
			if (ft_isdigit(*ptr) == false)
				return (p_error("Invalid argument\n"), false);
			ptr++;
		}
		n = ft_atol(*av);
		if (n < 0 || n > INT_MAX)
			return (p_error("Invalid number\n"), false);
	}
	return (true);
}
