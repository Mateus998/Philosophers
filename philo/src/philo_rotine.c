/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rotine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/01 18:01:17 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_terminal(philo->id, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_terminal(philo->id, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_terminal(philo->id, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_terminal(philo->id, "has taken right fork");
	}
}

void	partial_usleep(long time)
{
	long	start;

	start = time_ms();
	while ((time_ms() - start) < time)
		usleep(500);
}

int	ft_eat(t_philo *philo)
{
	print_terminal(philo->id, "is eating");
	partial_usleep(state()->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (state()->number_of_meals == -1)
		return (1);
	pthread_mutex_lock(&philo->meals_mutex);
	if (++philo->meals >= state()->number_of_meals)
	{
		pthread_mutex_unlock(&philo->meals_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	return (1);
}

void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (state()->number_of_philos == 1)
		return (NULL);
	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		ft_take_forks(philo);
		if (!ft_eat(philo))
			break ;
		print_terminal(philo->id, "is sleeping");
		partial_usleep(state()->time_to_sleep);
		print_terminal(philo->id, "is thinking");
		pthread_mutex_lock(&state()->status_mutex);
		if (state()->status != 1)
		{
			pthread_mutex_unlock(&state()->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&state()->status_mutex);
	}
	return (NULL);
}
