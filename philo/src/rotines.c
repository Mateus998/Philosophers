/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/27 17:29:42 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_take_forks(t_philo *philo)
{
	if (!loop_check(NULL, NULL, philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!loop_check(philo->left_fork, NULL, philo))
		return (0);
	print_terminal(philo->id, "has taken left fork");
	if (!loop_check(philo->left_fork, NULL, philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (!loop_check(philo->left_fork, philo->right_fork, philo))
		return (0);
	print_terminal(philo->id, "has taken right fork");
	return (1);
}

// int	meals_check(t_philo *philo)
// {
// 	if (state()->number_of_meals == -1)
// 		return (1);
// 	// pthread_mutex_lock(&philo->meals_mutex);
// 	if (!loop_check(&philo->meals_mutex, NULL))
// 		return (0);
// 	philo->meals++;
// 	if (philo->meals >= state()->number_of_meals)
// 		ret = 0;
// 	pthread_mutex_unlock(&philo->meals_mutex);
// 	return (ret);
// }

int	ft_eat(t_philo *philo)
{
	if (!loop_check(philo->left_fork, philo->right_fork, philo))
		return (0);
	print_terminal(philo->id, "is eating");
	if (!loop_check(philo->left_fork, philo->right_fork, philo))
		return (0);
	usleep(state()->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_meal = time_ms();
	// if (!loop_check(NULL, NULL, philo->id))
	// 	return (0);
	// pthread_mutex_lock(&philo->last_meal_mutex);
	// if (!loop_check(&philo->last_meal_mutex, NULL, philo->id))
	// 	return (0);
	// pthread_mutex_unlock(&philo->last_meal_mutex);
	if (state()->number_of_meals == -1)
		return (1);
	else if (++philo->meals >= state()->number_of_meals)
		return (0);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (!loop_check(NULL, NULL, philo))
		return (0);
	print_terminal(philo->id, "is sleeping");
	usleep(state()->time_to_sleep * 1000);
	return (1);
}

void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (state()->number_of_philos == 1)
		return (NULL);
	if (philo->id % 2 != 0)
		usleep((state()->time_to_eat / 4) * 1000);
	while (1)
	{
		if (!ft_take_forks(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		if (!loop_check(NULL, NULL, philo))
			break ;
		print_terminal(philo->id, "is thinking");
	}
	return (NULL);
}
/*
void	with_number_of_meals(t_philo *philos)
{
	int		meals;
	int		i;
	
	i = 0;
	meals = 0;
	while (1)
	{
		if (i >= state()->number_of_philos)
		{
			i = 0;
			meals = 0;
		}
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		pthread_mutex_lock(&philos[i].meals_mutex);
		if (time_ms() - philos[i].last_meal >= state()->time_to_die
			&& philos[i].meals < state()->number_of_meals)
		{
			pthread_mutex_unlock(&philos[i].meals_mutex);
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			pthread_mutex_lock(&state()->print_mutex);
			pthread_mutex_lock(&state()->status_mutex);
			printf("%ld %i %s\n", time_ms() - state()->begin_time, philos[i].id, "has died");
			state()->status = 0;
			pthread_mutex_unlock(&state()->print_mutex);
			pthread_mutex_unlock(&state()->status_mutex);
			break;
		}
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		if (philos[i].meals >= state()->number_of_meals)
			meals++;
		pthread_mutex_unlock(&philos[i].meals_mutex);
		if (meals == state()->number_of_philos)
			break;
		i++;
	}
}

void	without_number_of_meals(t_philo *philos)
{
	int		i;
	
	i = 0;
	while (1)
	{
		if (i >= state()->number_of_philos)
			i = 0;
		pthread_mutex_lock(&philos[i].last_meal_mutex);
		if (time_ms() - philos[i].last_meal >= state()->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].last_meal_mutex);
			pthread_mutex_lock(&state()->print_mutex);
			pthread_mutex_lock(&state()->status_mutex);
			printf("%ld %i %s\n", time_ms() - state()->begin_time, philos[i].id, "has died");
			state()->status = 0;
			pthread_mutex_unlock(&state()->print_mutex);
			pthread_mutex_unlock(&state()->status_mutex);
			break;
		}
		pthread_mutex_unlock(&philos[i].last_meal_mutex);
		i++;
	}
}

void	*check_rotine(void *arg)
{
	t_philo	*philos;
	

	philos = (t_philo *)arg;
	if (state()->number_of_meals == -1)
	{
		without_number_of_meals(philos);
	}
	else
	{
		with_number_of_meals(philos);
	}
	return (NULL);
}*/
