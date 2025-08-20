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
    
    philo = (t_philo *)arg;
    if (philo->id % 2 != 0)
        usleep((state()->time_to_eat / 2) * 1000);
    while (1)
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
        //mutex lock para var status
    }
    return (NULL);
}

void *check_rotine(void *arg) //correcoes
{
    t_philo *philos;
    t_state *state;
    int meals;
    long time;
    int i;

    philos = (t_philo *)arg;
    state = philos[0].state;
    while(state->status == 1)
    {
        i = 0;
        time = time_ms();
        meals = 1;
        while(i < state->number_of_philos && state->status == 1)
        {
            if (time - philos[i].last_meal > state->time_to_die)
            {
                print_terminal(&philos[i], "has died");
                state->status = 0;
            }
            else if (state->number_of_meals == -1)
                continue;
            else if (philos[i].meals < state->number_of_meals)
                meals = 0;
            i++;
        }
        if (meals == 1 && state->number_of_meals != -1)
            state->status = 2;
    }
    return (NULL);
}