/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:21:33 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/02 17:54:45 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_clean(void)
{
	int	i;

	i = 0;
	while (i < sim()->n_philos)
		safe_join(&philo(i++)->thread);
	safe_join(&sim()->monitor);
	i = 0;
	while (i < sim()->n_philos)
	{
		safe_mutex_destroy(&philo(i)->last_meal_mutex);
		safe_mutex_destroy(&philo(i)->meals_mutex);
		safe_mutex_destroy(&sim()->forks[i++]);
	}
	safe_mutex_destroy(&sim()->print_mutex);
	safe_mutex_destroy(&sim()->status_mutex);
	free(sim()->philos);
	free(sim()->forks);
}

void	partial_usleep(int time)
{
	long	start;

	start = time_ms();
	while ((time_ms() - start) < time)
	{
		mutex_lock(&sim()->status_mutex);
		if (sim()->status != 1)
		{
			mutex_unlock(&sim()->status_mutex);
			return ;
		}
		mutex_unlock(&sim()->status_mutex);
		usleep(500);
	}
}

void	print_terminal(int i, char *msg)
{
	mutex_lock(&sim()->status_mutex);
	mutex_lock(&sim()->print_mutex);
	if (sim()->status == 1)
		printf("%ld %i %s\n", time_ms() - sim()->begin_time, i, msg);
	mutex_unlock(&sim()->print_mutex);
	mutex_unlock(&sim()->status_mutex);
}

long	time_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

int	check_arg(char *a)
{
	int		j;
	long	n;

	if (!*a)
		return (1);
	j = 0;
	while (a[j])
	{
		if (ft_isdigit(a[j]) == 0)
			return (1);
		j++;
	}
	n = ft_atol(a);
	if (n < 0 || n > INT_MAX)
		return (1);
	return (0);
}
