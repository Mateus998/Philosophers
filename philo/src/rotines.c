/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/26 19:05:59 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int loop_check()
{
	int loop;
	
	pthread_mutex_lock(&state()->status_mutex);
	loop = state()->status;
	pthread_mutex_unlock(&state()->status_mutex);
	return (loop);
}

int ft_take_forks(t_philo *philo)
{
	if(!loop_check())
		return (0);
	pthread_mutex_lock(philo->left_fork);
	print_terminal(philo->id, "has taken left fork");
	if(!loop_check())
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_terminal(philo->id, "has taken right fork");
	return (1);
}

int meals_check(t_philo *philo)
{
	int ret;
	
	ret = 1;
	if (state()->number_of_meals == -1)
		return (ret);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals++;
	if (philo->meals >= state()->number_of_meals)
		ret = 0;
	pthread_mutex_unlock(&philo->meals_mutex);
	return (ret);
}

int ft_eat(t_philo *philo)
{
	if(!loop_check())
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_terminal(philo->id, "is eating");
	usleep(state()->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (meals_check(philo));
}

int ft_sleep(t_philo *philo)
{
	if(!loop_check())
		return (0);
	print_terminal(philo->id, "is sleeping");
	usleep(state()->time_to_sleep * 1000);
	return (1);
}

void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep((state()->time_to_eat / 2) * 1000);
	while (1)
	{
		if (!ft_take_forks(philo))
			break;
		if (!ft_eat(philo))
			break;
		if (!ft_sleep(philo))
			break;
		if(!loop_check())
			break;
		print_terminal(philo->id, "is thinking");
	}
	return (NULL);
}

int with_number_of_meals(t_philo *philos, int i, int meals)
{
	pthread_mutex_lock(&philos[i].last_meal_mutex);
	pthread_mutex_lock(&philos[i].meals_mutex);
	if (time_ms() - philos[i].last_meal >= state()->time_to_die && philos[i].meals < state()->number_of_meals)
	{
		pthread_mutex_unlock(&philos[i].meals_mutex);
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		print_terminal(philos[i].id, "has died");
		return (0);
	}
	pthread_mutex_unlock(&philos[i].last_meal_mutex);
	if (philos[i].meals >= state()->number_of_meals)
		meals++;
	pthread_mutex_unlock(&philos[i].meals_mutex);
	if (meals == state()->number_of_philos)
		return (0);
	return (1);
}

int without_number_of_meals(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos[i].last_meal_mutex);
	if (time_ms() - philos[i].last_meal >= state()->time_to_die)
	{
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		print_terminal(philos[i].id, "has died");
		return (0);
	}
	pthread_mutex_unlock(&philos[i].last_meal_mutex);
	return (1);
}

void	*check_rotine(void *arg)
{
	t_philo *philos;
	int meals;
	int i;

	philos = (t_philo *)arg;
	i = 0;
	meals = 0;
	while (1)
	{
		if (i >= state()->number_of_philos)
		{
			i = 0;
			meals = 0;
		}
		if (state()->number_of_meals != -1)
		{
			if (!without_number_of_meals(philos, i))
				break;
		}
		else
		{
			if (!with_number_of_meals(philos, i, meals))
				break;
		}
		i++;
	}
	pthread_mutex_lock(&state()->status_mutex);
	state()->status = 0;
	pthread_mutex_unlock(&state()->status_mutex);
	return (NULL);
}
