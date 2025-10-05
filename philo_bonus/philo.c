# include "philo.h"

t_sim *sim()
{
    static t_sim sim;
    return (&sim);
}

t_ph *ph()
{
    static t_ph ph;
    return (&ph);
}

void	partial_usleep(int time)
{
	long	start;

    if (time < 0)
    {
        return ;
    }
	start = time_ms();
	while ((time_ms() - start) < time)
	{
		if (time_ms() - ph()->last_meal >= sim()->t_die)
		    child_exit(1);
		usleep(500);
	}
}

void initial_check(int i)
{
    ph()->id = i;
    ph()->meals = sim()->n_meals;
    ph()->last_meal = time_ms();
    if (sim()->n_meals == 0)
        child_exit(0);
    if (sim()->n_philos == 1)
    {
        sem_wait(sim()->forks);
        print_terminal(1, "has taken a fork");
        partial_usleep(sim()->t_die * 2);
    }
}

void child_process(int i)
{
    initial_check(i);
    while (true)
    {
        sem_wait(sim()->table);
        sem_wait(sim()->forks);
        print_terminal(i, "has taken a fork");
        sem_wait(sim()->forks);
        print_terminal(i, "has taken a fork");
        sem_post(sim()->table);
        ph()->last_meal = time_ms();
        print_terminal(i, "is eating");
        partial_usleep(sim()->t_eat);
        sem_post(sim()->forks);
        sem_post(sim()->forks);
        if (sim()->n_meals > -1 && --ph()->meals <= 0)
            break ;
        print_terminal(i, "is sleeping");
        partial_usleep(sim()->t_sleep);
        print_terminal(i, "is thinking");
        partial_usleep((sim()->t_die - sim()->t_eat - sim()->t_sleep) / 2);
    }
    child_exit(0);
}

int	exit_status_return(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

bool fork_process()
{
    int status;
    int i;
    
    while(sim()->processes < sim()->n_philos)
    {
        sim()->child_pids[sim()->processes] = fork();
        if (sim()->child_pids[sim()->processes] == -1)
            return (p_error("fork() error\n"), false);
        if (sim()->child_pids[sim()->processes] == 0)
            child_process(sim()->processes + 1);
        sim()->processes++;
    }
    while (waitpid(-1, &status, 0) > 0)
    {
        status = exit_status_return(status);
        if (status != 0)
        {
            i = 0;
            while (i < sim()->n_philos)
                kill(sim()->child_pids[i++], SIGKILL);
            while (waitpid(-1, NULL, 0) > 0);
        }
    }
    return (true);
}

void ft_clear()
{
    sem_close(sim()->forks);
    sem_close(sim()->print);
    sem_close(sim()->table);
    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/table");
    if (sim()->child_pids)
        free(sim()->child_pids);
}

int main(int ac, char **av)
{
    if (ac < 5 || ac > 6)
        return (p_error("Invalid number of arguments\n"), 1);
    if (validate_args(av) == false)
        return (1);
    if (ft_init(av) == false)
        return (ft_clear(), 1);
    if (!fork_process())
    {
        sim()->processes = 0;
        while (sim()->child_pids[sim()->processes] != -1)
        {
            kill(sim()->child_pids[sim()->processes], SIGKILL);
            sim()->processes++;
        }
        return (ft_clear(), 1);
    }
    ft_clear();
    return (0);
}
/*
erros valgrind, leak semaforos
*/