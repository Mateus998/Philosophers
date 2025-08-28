/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/28 13:25:22 by mateferr         ###   ########.fr       */
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

int	ft_take_forks_reverse(t_philo *philo)
{
	if (!loop_check(NULL, NULL, philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	if (!loop_check(philo->right_fork, NULL, philo))
		return (0);
	print_terminal(philo->id, "has taken right fork");
	if (!loop_check(philo->right_fork, NULL, philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!loop_check(philo->right_fork, philo->left_fork, philo))
		return (0);
	print_terminal(philo->id, "has taken left fork");
	return (1);
}

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
	if (!loop_check(NULL, NULL, philo))
		return (0);
	philo->last_meal = time_ms();
	if (state()->number_of_meals == -1)
		return (1);
	else if (++philo->meals >= state()->number_of_meals)
		return (0);
	return (1);
}

void	rotine_loop(t_philo *philo, int (*func)(t_philo *))
{
	while (1)
	{
		if (!func(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		if (!loop_check(NULL, NULL, philo))
			break ;
		print_terminal(philo->id, "is sleeping");
		usleep(state()->time_to_sleep * 1000);
		if (!loop_check(NULL, NULL, philo))
			break ;
		print_terminal(philo->id, "is thinking");
	}
}

void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (state()->number_of_philos == 1)
		return (NULL);
	if (philo->id % 2 != 0)
	{
		usleep((state()->time_to_eat / 4) * 1000);
		rotine_loop(philo, ft_take_forks_reverse);
	}
	else
		rotine_loop(philo, ft_take_forks);
	return (NULL);
}
