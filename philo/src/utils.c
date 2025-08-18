/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:32:39 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/18 18:38:01 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long time_ms()
{
	struct timeval *tv = 0;
	long time;
	
	gettimeofday(tv, NULL);
	time = tv->tv_sec * 1000 + tv->tv_usec / 1000;
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
