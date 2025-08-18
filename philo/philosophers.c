/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/18 18:32:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo(t_philo *philo, int id, t_state *state)
{
    philo->id = id;
    philo->state = state;
    philo->meals = 0;
    philo->last_meal = time_ms();
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

void print_terminal(t_philo *philo, char *msg)
{
    pthread_mutex_lock(philo->state->print_mutex);
    printf("%ld %i %s", time_ms(), philo->id, msg);
    pthread_mutex_unlock(philo->state->print_mutex);
}

void *philo_rotine(void *arg)
{
    t_philo *philo;
    t_state *state;
    
    philo = (t_philo *)arg;
    state = philo->state;
    if (philo->id % 2 != 0)
        usleep((state->time_to_eat / 2) * 1000);
    while (state->status == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_terminal(philo, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        print_terminal(philo, "has taken right fork");
        philo->last_meal = time_ms();
        print_terminal(philo, "is eating");
        usleep(state->time_to_eat * 1000);
        philo->meals++;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        print_terminal(philo, "is sleeping");
        usleep(state->time_to_sleep * 1000);
        print_terminal(philo, "is thinking");
    }
    return (NULL);
}

void *check_rotine(void *arg)
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
            else if (philos[i].meals < state->number_of_meals)
                meals = 0;
            i++;
        }
        if (meals == 1)
            state->status = 2;
    }
    return (NULL);
}

int main(int ac, char **av) //protect functions and end program
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
    pthread_mutex_init(state.print_mutex, NULL);
    philos = malloc(sizeof(t_philo) * state.number_of_philos);//protect
    i = 0;
    while (i < state.number_of_philos)
    {
        init_philo(&philos[i], i + 1, &state);
        pthread_create(&philos[i].thread, NULL, &philo_rotine, &philos[i]);
        i++;
    }
    pthread_create(&state.control, NULL, &check_rotine, philos);
    i = 0;
    while (i < state.number_of_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    pthread_join(state.control, NULL);
    i = 0;
    while (i < state.number_of_philos)
    {
        pthread_mutex_destroy(&state.forks[i]);
        i++;
    }
    pthread_mutex_destroy(state.print_mutex);
    free(philos);
    free(state.forks);
    return (0);
}
