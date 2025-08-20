/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:35 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/20 16:44:32 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
    int id;
    int meals;
    long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_state
{
    int number_of_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int number_of_meals;
    int status;
    pthread_t control;
    pthread_mutex_t *status_mutex;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *forks;
    t_philo *philos;
} t_state;

long	str_to_ml(const char *str);
int	str_to_int(const char *str);
long time_ms();
void print_terminal(int i, char *msg);
void ft_clean();

void *check_rotine(void *arg);
void *philo_rotine(void *arg);

int init_philos();
t_philo *philo(int i);
int init_state(char **av, int ac);
t_state *state();

#endif