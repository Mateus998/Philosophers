/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:35 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/27 17:37:26 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// pthread_mutex_t	last_meal_mutex;
	// pthread_mutex_t	meals_mutex;
}					t_philo;

typedef struct s_state
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_meals;
	long			begin_time;
	int				status;
	// pthread_t		control;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_state;

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
long				str_to_ml(const char *str);
int					str_to_int(const char *str);
long				time_ms(void);
void				print_terminal(int i, char *msg);
void				ft_clean(void);

void				*check_rotine(void *arg);
void				*philo_rotine(void *arg);
int					loop_check(pthread_mutex_t *mutex1,
						pthread_mutex_t *mutex2, t_philo *philo);

int					init_philos(void);
t_philo				*philo(int i);
int					init_state(char **av, int ac);
t_state				*state(void);

#endif