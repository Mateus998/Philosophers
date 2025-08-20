/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:59:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/20 16:49:36 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void *philo_rotine(void *arg)
{
    t_philo *philo;
    int loop;
    
    loop = 1;
    philo = (t_philo *)arg;
    if (philo->id % 2 != 0)
        usleep((state()->time_to_eat / 2) * 1000);
    while (loop)
    {
        pthread_mutex_lock(philo->left_fork);
        print_terminal(philo->id, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        print_terminal(philo->id, "has taken right fork");
        philo->last_meal = time_ms();
        print_terminal(philo->id, "is eating");
        usleep(state()->time_to_eat * 1000);
        philo->meals++;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        print_terminal(philo->id, "is sleeping");
        usleep(state()->time_to_sleep * 1000);
        print_terminal(philo->id, "is thinking");
        pthread_mutex_lock(state()->status_mutex);
        loop = state()->status;
        pthread_mutex_unlock(state()->status_mutex);
    }
    return (NULL);
}

void *check_rotine(void *arg)
{
    t_philo *philos;
    int meals;
    int i;
    int loop;

    philos = (t_philo *)arg;
    loop = 1;
    while(loop)
    {
        i = 0;
        meals = 1;
        while(loop && i < state()->number_of_philos)
        {
            if (time_ms() - philos[i].last_meal >= state()->time_to_die)
            {
                print_terminal(philos[i].id, "has died");
                loop = 0;
            }
            else if (state()->number_of_meals == -1)
                continue;
            else if (philos[i].meals < state()->number_of_meals)
                meals = 0;
            i++;
        }
        if (loop == 1 && meals == 1 && state()->number_of_meals != -1)
            loop = 0;
    }
    pthread_mutex_lock(state()->status_mutex);
    state()->status = 0;
    pthread_mutex_unlock(state()->status_mutex);
    return (NULL);
}