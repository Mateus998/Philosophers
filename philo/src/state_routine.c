/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:20:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/08 19:42:32 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	death_check(t_philo *philo)
{
	mutex_lock(&philo->last_meal_mutex);
	if (time_ms() - philo->last_meal >= sim()->t_die)
	{
		mutex_unlock(&philo->last_meal_mutex);
		mutex_lock(&sim()->status_mutex);
		mutex_lock(&sim()->print_mutex);
		printf("%ld %i %s\n", time_ms() - sim()->begin_time, philo->id,
			"has died");
		sim()->status = 0;
		mutex_unlock(&sim()->print_mutex);
		mutex_unlock(&sim()->status_mutex);
		return (true);
	}
	mutex_unlock(&philo->last_meal_mutex);
	return (false);
}

static bool	meals_check(t_philo *philo, int *meals)
{
	if (sim()->n_meals != -1)
	{
		mutex_lock(&philo->meals_mutex);
		if (philo->meals >= sim()->n_meals)
		{
			*meals = *meals + 1;
		}
		mutex_unlock(&philo->meals_mutex);
		if (*meals >= sim()->n_philos)
		{
			mutex_lock(&sim()->status_mutex);
			sim()->status = 0;
			mutex_unlock(&sim()->status_mutex);
			return (true);
		}
	}
	return (false);
}

void	*state_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	int		meals;

	i = 0;
	philos = (t_philo *)arg;
	meals = 0;
	mutex_lock(&sim()->status_mutex);
	mutex_unlock(&sim()->status_mutex);
	while (true)
	{
		if (meals_check(&philos[i], &meals))
			break ;
		if (death_check(&philos[i]))
			break ;
		if (++i >= sim()->n_philos)
		{
			i = 0;
			meals = 0;
			usleep(1000);
		}
	}
	return (NULL);
}
