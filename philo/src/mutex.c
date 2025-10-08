/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:01:06 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 13:30:32 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	mutex_lock(t_mutex *mtx)
{
	pthread_mutex_lock(&mtx->mutex);
}

void	mutex_unlock(t_mutex *mtx)
{
	pthread_mutex_unlock(&mtx->mutex);
}

void	safe_mutex_destroy(t_mutex *mtx)
{
	if (mtx->initiated)
		pthread_mutex_destroy(&mtx->mutex);
}

static int	safe_mutex_init(t_mutex *mtx)
{
	if (pthread_mutex_init(&mtx->mutex, NULL) == 0)
		mtx->initiated = 1;
	else
		return (1);
	return (0);
}

int	init_all_mutex(void)
{
	int	i;

	i = 0;
	while (i < sim()->n_philos)
	{
		if (safe_mutex_init(&philo(i)->last_meal_mutex) != 0)
			return (ft_clean(), 1);
		if (safe_mutex_init(&philo(i)->meals_mutex) != 0)
			return (ft_clean(), 1);
		if (safe_mutex_init(&sim()->forks[i++]) != 0)
			return (ft_clean(), 1);
	}
	if (safe_mutex_init(&sim()->print_mutex) != 0)
		return (ft_clean(), 1);
	if (safe_mutex_init(&sim()->status_mutex) != 0)
		return (ft_clean(), 1);
	return (0);
}
