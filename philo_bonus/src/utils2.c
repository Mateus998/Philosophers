
#include "../philo.h"

void p_error(char *msg)
{
	int i;

	i = 0;
	while(msg[i])
		i++;
	write(2, msg, i);
}

long	time_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

void child_exit(int i)
{
	if (i == 1)
	{
		sem_wait(sim()->print);
		printf("%ld %i %s\n", time_ms() - sim()->begin_time, ph()->id, "has died");
	}
	sem_close(sim()->forks);
	sem_close(sim()->print);
	sem_close(sim()->table);
	free(sim()->child_pids);
	exit(i);
}

void	print_terminal(int i, char *msg)
{
	if (time_ms() - ph()->last_meal >= sim()->t_die)
		child_exit(1);
	sem_wait(sim()->print);
	printf("%ld %i %s\n", time_ms() - sim()->begin_time, i, msg);
	sem_post(sim()->print);
}

bool	validate_args(char **av)
{
	long	n;
	char *ptr;

	while(*++av != NULL)
	{
		ptr = *av;
		while (*ptr != '\0')
		{
			if (ft_isdigit(*ptr) == false)
				return (p_error("Invalid argument\n"), false);
			ptr++;
		}
		n = ft_atol(*av);
		if (n < 0 || n > INT_MAX)
			return (p_error("Invalid number\n"), false);
	}
	return (true);
}
