/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:33 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 16:15:44 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	p_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
}

void	child_exit()
{
	sem_wait(sim()->sem_print);
		printf("%ld %i %s\n", time_ms() - sim()->begin_time, ph()->id,
			"has died");
	sem_close(sim()->sem_forks);
	sem_close(sim()->sem_print);
	sem_close(sim()->sem_table);
	sem_close(sim()->sem_meals);
	sem_close(sim()->sem_temp);
	free(sim()->child_pids);
	exit(1);
}

void	ft_clear(void)
{
    if (sim()->sem_forks != SEM_FAILED)
	    sem_close(sim()->sem_forks);
    if (sim()->sem_print != SEM_FAILED)
	    sem_close(sim()->sem_print);
    if (sim()->sem_table != SEM_FAILED)
	    sem_close(sim()->sem_table);
    if (sim()->sem_meals != SEM_FAILED)
	    sem_close(sim()->sem_meals);
	if (sim()->sem_temp != SEM_FAILED)
	    sem_close(sim()->sem_temp);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	sem_unlink("/meals");
	sem_unlink("/temp");
	if (sim()->child_pids)
		free(sim()->child_pids);
}
