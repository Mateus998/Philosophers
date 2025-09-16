/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 15:37:01 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_take_forks(t_philo *philo)
{
	int	left_id;
	int	right_id;

	left_id = philo->id;
	right_id = philo->id % st()->number_of_philos + 1;
	if (left_id > right_id)
	{
		mutex_lock(philo->right_fork);
		print_terminal(philo->id, "has taken right fork");
		mutex_lock(philo->left_fork);
		print_terminal(philo->id, "has taken left fork");
	}
	else
	{
		mutex_lock(philo->left_fork);
		print_terminal(philo->id, "has taken left fork");
		mutex_lock(philo->right_fork);
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
	partial_usleep(st()->time_to_eat);
	mutex_unlock(philo->left_fork);
	mutex_unlock(philo->right_fork);
	mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	mutex_unlock(&philo->last_meal_mutex);
	if (st()->number_of_meals == -1)
		return (0);
	mutex_lock(&philo->meals_mutex);
	if (++philo->meals >= st()->number_of_meals)
	{
		mutex_unlock(&philo->meals_mutex);
		return (1);
	}
	mutex_unlock(&philo->meals_mutex);
	return (0);
}

int	begin_routine(t_philo *philo)
{
	if (st()->number_of_philos == 1 || st()->number_of_meals == 0)
		return (1);
	mutex_lock(&st()->status_mutex);
	mutex_unlock(&st()->status_mutex);
	mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	mutex_unlock(&philo->last_meal_mutex);
	if (philo->id % 2 != 0)
		usleep(1000);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (begin_routine(philo))
		return (NULL);
	while (1)
	{
		ft_take_forks(philo);
		if (ft_eat(philo))
			break ;
		print_terminal(philo->id, "is sleeping");
		partial_usleep(st()->time_to_sleep);
		print_terminal(philo->id, "is thinking");
		mutex_lock(&st()->status_mutex);
		if (st()->status != 1)
		{
			mutex_unlock(&st()->status_mutex);
			break ;
		}
		mutex_unlock(&st()->status_mutex);
	}
	return (NULL);
}
