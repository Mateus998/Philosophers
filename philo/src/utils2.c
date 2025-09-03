/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:21:33 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/02 12:45:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_clean(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
		safe_join(&philo(i++)->thread);
	safe_join(&state()->monitor);
	i = 0;
	while (i < state()->number_of_philos)
	{
		safe_mutex_destroy(&philo(i)->last_meal_mutex);
		safe_mutex_destroy(&philo(i)->meals_mutex);
		safe_mutex_destroy(&state()->forks[i++]);
	}
	safe_mutex_destroy(&state()->print_mutex);
	safe_mutex_destroy(&state()->status_mutex);
	free(state()->philos);
	free(state()->forks);
}

void	print_terminal(int i, char *msg)
{
	mutex_lock(&state()->status_mutex);
	mutex_lock(&state()->print_mutex);
	if (state()->status == 1)
		printf("%ld %i %s\n", time_ms() - state()->begin_time, i, msg);
	mutex_unlock(&state()->print_mutex);
	mutex_unlock(&state()->status_mutex);
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

	j = 0;
	if (!*a)
		return (1);
	while (a[j] && ((a[j] >= 9 && a[j] <= 13) || a[j] == ' '))
		j++;
	if (a[j] == '\0')
		return (1);
	if (a[j] == '+' || a[j] == '-')
		j++;
	while (a[j])
	{
		if (a[j] < '0' || a[j] > '9')
			return (1);
		j++;
	}
	n = ft_atol(a);
	if (n < 0 || n > INT_MAX)
		return (1);
	return (0);
}
