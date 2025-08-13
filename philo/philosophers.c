/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/12 12:59:43 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *rotine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

}

void init_philo(t_philo *philo, int id, t_state *state)
{
    struct timeval tv;

    gettimeofday(&tv, NULL); //protect
    philo->id = id;
    philo->state = state;
    philo->meals = 0;
    philo->last_meal = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    philo->left_fork = &state->forks[id - 1];
    philo->right_fork = &state->forks[id % state->number_of_philos];
}

void init_state(t_state *state, char **av, int ac)
{
    state->number_of_philos = str_to_int(av[1]);
    state->time_to_die = str_to_ml(av[2]);
    state->time_to_eat = str_to_ml(av[3]);
    state->time_to_sleep = str_to_ml(av[4]);
    if (ac == 6)
        state->number_of_meals = str_to_int(av[5]);
    else
        state->number_of_meals = -1;
    state->forks = malloc(sizeof(pthread_mutex_t) * state->number_of_philos);//protect
    state->status = 1;
}

int main(int ac, char **av) //protect thread and mutex functions
{
    int i;
    t_state state;
    t_philo *philos;
    
    if (ac < 5 || ac > 6)
        return (0);
    init_state(&state, av, ac);
    i = 0;
    while (i < state.number_of_philos)
    {
        pthread_mutex_init(&state.forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&state.print_mutex, NULL);
    philos = malloc(sizeof(t_philo) * state.number_of_philos);//protect
    i = 0;
    while (i < state.number_of_philos)
    {
        init_philo(&philos[i], i + 1, &state);
        pthread_create(&philos[i].thread, NULL, &rotine, &philos[i]);
        i++;
    }
}
