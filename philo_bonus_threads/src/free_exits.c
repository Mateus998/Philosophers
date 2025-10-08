/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:33 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/08 19:38:51 by mateferr         ###   ########.fr       */
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

void	ft_clear(void)
{
	if (sim()->sems->forks != SEM_FAILED)
		sem_close(sim()->sems->forks);
	if (sim()->sems->print != SEM_FAILED)
		sem_close(sim()->sems->print);
	if (sim()->sems->table != SEM_FAILED)
		sem_close(sim()->sems->table);
	if (sim()->sems->meals != SEM_FAILED)
		sem_close(sim()->sems->meals);
	if (sim()->sems->end != SEM_FAILED)
		sem_close(sim()->sems->end);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	sem_unlink("/meals");
	sem_unlink("/end_sim");
	if (sim()->child_pids)
		free(sim()->child_pids);
	if (sim()->sems)
		free(sim()->sems);
}
