/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/09 11:03:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	sim_check(t_mutex *mtx1, t_mutex *mtx2)
{
	mutex_lock(&sim()->status_mutex);
	if (sim()->status != 1)
	{
		mutex_unlock(&sim()->status_mutex);
		if (mtx1)
			mutex_unlock(mtx1);
		if (mtx2)
			mutex_unlock(mtx2);
		return (false);
	}
	mutex_unlock(&sim()->status_mutex);
	return (true);
}

static bool	ft_take_forks(t_philo *philo)
{
	if (philo->id > philo->id % sim()->n_philos + 1)
	{
		mutex_lock(philo->right_fork);
		print_terminal(philo->id, "has taken right fork");
		mutex_lock(philo->left_fork);
		print_terminal(philo->id, "has taken left fork");
		return (sim_check(philo->right_fork, philo->left_fork));
	}
	mutex_lock(philo->left_fork);
	print_terminal(philo->id, "has taken left fork");
	if (sim()->n_philos == 1)
	{
		mutex_unlock(philo->left_fork);
		partial_usleep(sim()->t_die * 2);
		return (sim_check(philo->left_fork, NULL));
	}
	mutex_lock(philo->right_fork);
	print_terminal(philo->id, "has taken right fork");
	return (sim_check(philo->left_fork, philo->right_fork));
}

static bool	ft_eat(t_philo *philo)
{
	print_terminal(philo->id, "is eating");
	mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	mutex_unlock(&philo->last_meal_mutex);
	partial_usleep(sim()->t_eat);
	mutex_unlock(philo->left_fork);
	mutex_unlock(philo->right_fork);
	if (sim()->n_meals != -1)
	{
		mutex_lock(&philo->meals_mutex);
		philo->meals++;
		mutex_unlock(&philo->meals_mutex);
	}
	return (sim_check(NULL, NULL));
}

static void	begin_routine(t_philo *philo)
{
	mutex_lock(&sim()->status_mutex);
	mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = time_ms();
	mutex_unlock(&philo->last_meal_mutex);
	mutex_unlock(&sim()->status_mutex);
	if (philo->id % 2 != 0)
		usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	begin_routine(philo);
	while (true)
	{
		if (!ft_take_forks(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		print_terminal(philo->id, "is sleeping");
		partial_usleep(sim()->t_sleep);
		print_terminal(philo->id, "is thinking");
		partial_usleep((sim()->t_die - sim()->t_eat - sim()->t_sleep) / 2);
		if (!sim_check(NULL, NULL))
			break ;
	}
	return (NULL);
}
