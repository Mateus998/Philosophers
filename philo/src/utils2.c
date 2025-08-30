/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:21:33 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/28 12:08:33 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_clean(void)
{
	int	i;

	i = 0;
	while (i < state()->number_of_philos)
		pthread_join(philo(i++)->thread, NULL);
	i = 0;
	while (i < state()->number_of_philos)
	{
		pthread_mutex_destroy(&state()->forks[i++]);
	}
	pthread_mutex_destroy(&state()->print_mutex);
	pthread_mutex_destroy(&state()->status_mutex);
	free(state()->philos);
	free(state()->forks);
}

void	print_terminal(int i, char *msg)
{
	pthread_mutex_lock(&state()->status_mutex);
	pthread_mutex_lock(&state()->print_mutex);
	if (state()->status == 1)
		printf("%ld %i %s\n", time_ms() - state()->begin_time, i, msg);
	pthread_mutex_unlock(&state()->print_mutex);
	pthread_mutex_unlock(&state()->status_mutex);
}

long	time_ms(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("get time ERRO\n");
		exit(1);
	}
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

void	check_arg(char *a)
{
	int		j;
	long	n;

	j = 0;
	if (!*a)
		exit(11);
	while (a[j] && ((a[j] >= 9 && a[j] <= 13) || a[j] == ' '))
		j++;
	if (a[j] == '\0')
		exit(12);
	if (a[j] == '+' || a[j] == '-')
		j++;
	while (a[j])
	{
		if (a[j] < '0' || a[j] > '9')
			exit(13);
		j++;
	}
	n = ft_atol(a);
	if (n < 0 || n > INT_MAX)
		exit(14);
}
