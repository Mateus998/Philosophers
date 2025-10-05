#include "../philo.h"

bool ft_init(char **av)
{
    sim()->n_philos = ft_atoi(av[1]);
    sim()->t_die = ft_atoi(av[2]);
    sim()->t_eat = ft_atoi(av[3]);
    sim()->t_sleep = ft_atoi(av[4]);
    if (av[5] != NULL)
        sim()->n_meals = ft_atoi(av[5]);
    else
        sim()->n_meals = -1;
    sim()->begin_time = time_ms();
    sim()->processes = 0;
    sim()->child_pids = ft_calloc(sim()->n_philos, sizeof(pid_t));
    if (!sim()->child_pids)
        return (p_error("malloc() error\n"), false);
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/table");
    sim()->forks = sem_open("/forks", O_CREAT, 0644, sim()->n_philos);
    sim()->print = sem_open("/print", O_CREAT, 0644, 1);
    if (sim()->n_philos % 2 == 0)
        sim()->table = sem_open("/table", O_CREAT, 0644, sim()->n_philos / 2);
    else
        sim()->table = sem_open("/table", O_CREAT, 0644, sim()->n_philos / 2 + 1);
    if (sim()->forks == SEM_FAILED || sim()->print == SEM_FAILED)
        return (p_error("error opening semaphore\n"), false);
    return (true);
}
