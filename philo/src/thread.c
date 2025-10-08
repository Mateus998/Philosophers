/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:01:20 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/02 13:05:55 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	safe_join(t_thread *th)
{
	if (th->created)
		pthread_join(th->thread, NULL);
}

static int	safe_thread_create(t_thread *th, void *(*routine)(void *),
		void *arg)
{
	if (pthread_create(&th->thread, NULL, routine, arg) == 0)
		th->created = 1;
	else
	{
		sim()->status = 0;
		mutex_unlock(&sim()->status_mutex);
		return (1);
	}
	return (0);
}

int	create_all_threads(void)
{
	int	i;

	i = 0;
	mutex_lock(&sim()->status_mutex);
	while (i < sim()->n_philos)
	{
		if (safe_thread_create(&philo(i)->thread, &philo_routine,
				philo(i)) != 0)
			return (1);
		i++;
	}
	if (safe_thread_create(&sim()->monitor, &state_routine, sim()->philos) != 0)
		return (1);
	sim()->status = 1;
	if (sim()->t_die == 0)
		sim()->status = 0;
	sim()->begin_time = time_ms();
	mutex_unlock(&sim()->status_mutex);
	return (0);
}
