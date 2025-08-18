/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:35 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/18 15:35:28 by mateferr         ###   ########.fr       */
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

typedef struct s_state
{
    int number_of_philos;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int number_of_meals;
    int status;
    struct timeval *tv;
    pthread_t control;
    pthread_mutex_t *forks;
    pthread_mutex_t *print_mutex;
} t_state;

typedef struct s_philo
{
    int id;
    struct timeval *tv;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int meals;
    long last_meal;
    t_state *state;
} t_philo;

long	str_to_ml(const char *str);
int	str_to_int(const char *str);
long time_ms();

#endif