/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:01:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/20 16:27:01 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int init_philos()
{
    int i;
    
    state()->philos = malloc(sizeof(t_philo) * state()->number_of_philos);
    if (!state()->philos)
        return (0);
    i = 0;
    while (i < state()->number_of_philos)
    {
        state()->philos[i].id = i + 1;
        state()->philos[i].meals = 0;
        state()->philos[i].last_meal = time_ms();
        state()->philos[i].left_fork = &state()->forks[i];
        state()->philos[i].right_fork = &state()->forks[(i + 1) % state()->number_of_philos];
        i++;
    }
    return (1);
}

t_philo *philo(int i)
{
    if (i < 0 || i >= state()->number_of_philos)
        return (NULL);
    return (&state()->philos[i]);
}

int init_state(char **av, int ac)
{
    state()->number_of_philos = str_to_int(av[1]);
    state()->time_to_die = str_to_ml(av[2]);
    state()->time_to_eat = str_to_ml(av[3]);
    state()->time_to_sleep = str_to_ml(av[4]);
    if (ac == 6)
        state()->number_of_meals = str_to_int(av[5]);
    else
        state()->number_of_meals = -1;
    state()->forks = malloc(sizeof(pthread_mutex_t) * state()->number_of_philos);//protect
    if (!state()->forks)
        return (0);
    state()->status = 1;
    return (1);
}

t_state *state()
{
    static t_state state;
    return (&state);
}
