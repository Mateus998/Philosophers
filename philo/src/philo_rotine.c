/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_rotine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/02 12:49:58 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int error_stop(pthread_mutex_t *mtx, int status)
{
	if (mtx)
		pthread_mutex_unlock(mtx);
	if (status == 0)
	{
		if (pthread_mutex_lock(&state()->status_mutex) != 0)
		{
			state()->status = 0;
			return (1);
		}
		state()->status = 0;
	}
	pthread_mutex_unlock(&state()->status_mutex);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (error_stop(NULL, 0));
		if (print_terminal(philo->id, "has taken right fork"))
			return (1);
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (error_stop(philo->right_fork, 0));
		if (print_terminal(philo->id, "has taken left fork"))
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (error_stop(NULL, 0));
		if (print_terminal(philo->id, "has taken left fork"))
			return (1);
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (error_stop(philo->left_fork, 0));
		if (print_terminal(philo->id, "has taken right fork"))
			return (1);
	}
	return (0);
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
	if (print_terminal(philo->id, "is eating"))
			return (1);
	partial_usleep(state()->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (pthread_mutex_lock(&philo->last_meal_mutex) != 0)
		return (error_stop(NULL, 0));
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (state()->number_of_meals == -1)
		return (1);
	if (pthread_mutex_lock(&philo->meals_mutex) != 0)
		return (error_stop(NULL, 0));
	if (++philo->meals >= state()->number_of_meals)
	{
		pthread_mutex_unlock(&philo->meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	return (0);
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
		if (ft_take_forks(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (print_terminal(philo->id, "is sleeping"))
			break ;
		partial_usleep(state()->time_to_sleep);
		if (print_terminal(philo->id, "is thinking"))
			break ;
		if (pthread_mutex_lock(&state()->status_mutex) != 0)
			state()->status = 2;
		if (state()->status != 1)
		{
			if (state()->status == 0)
				pthread_mutex_unlock(&state()->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&state()->status_mutex);
	}
	return (NULL);
}
