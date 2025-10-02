/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:26:35 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/02 12:58:23 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_thread
{
	pthread_t		thread;
	int				created;
}					t_thread;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				initiated;
}					t_mutex;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	t_thread		thread;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_mutex			last_meal_mutex;
	t_mutex			meals_mutex;
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
	t_thread		monitor;
	t_mutex			status_mutex;
	t_mutex			print_mutex;
	t_mutex			*forks;
	t_philo			*philos;
}					t_state;

void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_atoi(const char *str);
long				ft_atol(const char *str);

long				time_ms(void);
void				print_terminal(int i, char *msg);
void				ft_clean(void);
int					check_arg(char *a);

void				*philo_routine(void *arg);
void				*state_routine(void *arg);

int					init_philos(void);
int					init_state(char **av, int ac);
t_philo				*philo(int i);
t_state				*st(void);

int					create_all_threads(void);
void				safe_join(t_thread *th);

int					init_all_mutex(void);
void				safe_mutex_destroy(t_mutex *mtx);
void				mutex_unlock(t_mutex *mtx);
void				mutex_lock(t_mutex *mtx);

#endif