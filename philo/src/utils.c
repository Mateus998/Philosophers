/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:32:39 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/20 16:48:19 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void ft_clean()
{
	int i;
	
	i = 0;
    while (i < state()->number_of_philos)
        pthread_join(philo(i++)->thread, NULL);
    pthread_join(state()->control, NULL);
    i = 0;
    while (i < state()->number_of_philos)
        pthread_mutex_destroy(&state()->forks[i++]);
    pthread_mutex_destroy(state()->print_mutex);
    pthread_mutex_destroy(state()->status_mutex);
    free(state()->philos);
    free(state()->forks);
}

void print_terminal(int i, char *msg)
{
    pthread_mutex_lock(state()->print_mutex);
    printf("%ld %i %s\n", time_ms(), i, msg);
    pthread_mutex_unlock(state()->print_mutex);
}

long time_ms()
{
	struct timeval tv;
	long time = 0;
	
	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("get time ERRO\n");
		exit(1);	
	}
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

long	str_to_ml(const char *str)
{
	int	i;
    long num;

    num = 0;
	i = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	str_to_int(const char *str)
{
	int	i;
    int num;

    num = 0;
	i = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}
