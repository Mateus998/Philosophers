/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_rotine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:20:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/02 12:41:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_death(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->last_meal_mutex) != 0)
		return (error_stop(NULL, 0));
	if (time_ms() - philo->last_meal >= state()->time_to_die)
	{
		if (pthread_mutex_lock(&state()->status_mutex) != 0)
			return (error_stop(&philo->last_meal_mutex, 0));
		if (pthread_mutex_lock(&state()->print_mutex) != 0)
			return (error_stop(&philo->last_meal_mutex, 1));
		if (state()->status == 1)
			printf("%ld %i %s\n", time_ms() - state()->begin_time, philo->id,
				"has died");
		state()->status = 0;
		pthread_mutex_unlock(&state()->print_mutex);
		pthread_mutex_unlock(&state()->status_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	reset_loop(int *i, int *meals)
{
	if (*i >= state()->number_of_philos)
	{
		*i = 0;
		*meals = 0;
		usleep(500);
	}
}

int	meals_check(t_philo *philo, int *meals)
{
	if (state()->number_of_meals != -1)
	{
		if (pthread_mutex_lock(&philo->meals_mutex) != 0)
			return (error_stop(NULL, 0));
		if (philo->meals >= state()->number_of_meals)
			*meals = *meals + 1;
		pthread_mutex_unlock(&philo->meals_mutex);
		if (*meals >= state()->number_of_philos)
			return (1);
	}
	return (0);
}

void	*state_rotine(void *arg)
{
	t_philo	*philos;
	int		i;
	int		meals;

	i = 0;
	philos = (t_philo *)arg;
	meals = 0;
	if (state()->number_of_philos == 1)
		return (NULL);
	while (1)
	{
		reset_loop(&i, &meals);
		if (philo_death(&philos[i]))
			break ;
		if (meals_check(&philos[i], &meals))
			break ;
		i++;
	}
	return (NULL);
}
