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

static int	philo_death(t_philo *philo)
{
	mutex_lock(&philo->last_meal_mutex);
	if (time_ms() - philo->last_meal >= st()->time_to_die)
	{
		mutex_lock(&philo->meals_mutex);
		if (st()->number_of_meals == -1 || philo->meals < st()->number_of_meals)
		{
			mutex_unlock(&philo->last_meal_mutex);
			mutex_unlock(&philo->meals_mutex);
			mutex_lock(&st()->status_mutex);
			mutex_lock(&st()->print_mutex);
			printf("%ld %i %s\n", time_ms() - st()->begin_time, philo->id,
				"has died");
			st()->status = 0;
			mutex_unlock(&st()->print_mutex);
			mutex_unlock(&st()->status_mutex);
			return (1);
		}
		mutex_unlock(&philo->meals_mutex);
	}
	mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

static void	reset_loop(int *i, int *meals)
{
	if (*i >= st()->number_of_philos)
	{
		*i = 0;
		*meals = 0;
		usleep(1000);
	}
}

static int	meals_check(t_philo *philo, int *meals)
{
	if (st()->number_of_meals != -1)
	{
		mutex_lock(&philo->meals_mutex);
		if (philo->meals >= st()->number_of_meals)
			*meals = *meals + 1;
		mutex_unlock(&philo->meals_mutex);
		if (*meals >= st()->number_of_philos)
		{
			mutex_lock(&st()->status_mutex);
			st()->status = 0;
			mutex_unlock(&st()->status_mutex);
			return (1);
		}
	}
	return (0);
}

void	*state_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	int		meals;

	i = 0;
	philos = (t_philo *)arg;
	meals = 0;
	if (st()->number_of_meals == 0)
		return (NULL);
	mutex_lock(&st()->status_mutex);
	mutex_unlock(&st()->status_mutex);
	while (1)
	{
		reset_loop(&i, &meals);
		if (meals_check(&philos[i], &meals))
			break ;
		if (philo_death(&philos[i]))
			break ;
		i++;
	}
	return (NULL);
}
