# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
#include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>

typedef struct s_ph
{
    int id;
    long last_meal;
    int meals;
    sem_t *forks;
    sem_t *print;
} t_ph;

typedef struct s_sim
{
    int n_philos;
    int t_die;
    int t_sleep;
    int t_eat;
    int n_meals;
    long begin_time;
    int processes;
    sem_t *forks;
    sem_t *print;
    pid_t *child_pids;
} t_sim;

t_sim *sim();
t_ph *ph();
bool ft_init(char **av);

//clear
void p_error(char *msg);
void child_exit(int i);

//utils
void	print_terminal(int i, char *msg);
long	time_ms(void);
bool	validate_args(char **av);

int	ft_atoi(const char *str);
long	ft_atol(const char *str);
int	ft_isdigit(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);