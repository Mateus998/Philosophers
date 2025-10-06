/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:39:31 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 15:55:42 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	exit_status_return(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

long	time_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

void	print_terminal(int i, char *msg)
{
	if (time_ms() - ph()->last_meal >= sim()->t_die)
		child_exit(1);
	sem_wait(sim()->sem_print);
	printf("%ld %i %s\n", time_ms() - sim()->begin_time, i, msg);
	sem_post(sim()->sem_print);
}

bool	validate_args(char **av)
{
	long	n;
	char	*ptr;

	while (*++av != NULL)
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
