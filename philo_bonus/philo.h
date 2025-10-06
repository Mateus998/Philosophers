/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:39:12 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 16:43:41 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_ph
{
	int		id;
	long	last_meal;
	int		meals;
}			t_ph;

typedef struct s_sim
{
	int		n_philos;
	int		t_die;
	int		t_sleep;
	int		t_eat;
	int		n_meals;
	long	begin_time;
	int		processes;
	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	*sem_table;
	sem_t	*sem_meals;
	pid_t	*child_pids;
	pid_t	meals_check;
}			t_sim;

bool		processes_creation(void);

// init
t_sim		*sim(void);
t_ph		*ph(void);
bool		ft_init(char **av);

// clear
void		p_error(char *msg);
void		child_exit(int i);
void		ft_clear(void);

// utils
int			exit_status_return(int status);
void		print_terminal(int i, char *msg);
long		time_ms(void);
bool		validate_args(char **av);

int			ft_atoi(const char *str);
long		ft_atol(const char *str);
int			ft_isdigit(int c);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);