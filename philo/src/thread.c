/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:01:20 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 15:35:50 by mateferr         ###   ########.fr       */
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
		st()->status = 0;
		mutex_unlock(&st()->status_mutex);
		return (1);
	}
	return (0);
}

int	create_all_threads(void)
{
	int	i;

	i = 0;
	mutex_lock(&st()->status_mutex);
	while (i < st()->number_of_philos)
	{
		if (safe_thread_create(&philo(i)->thread, &philo_routine,
				philo(i)) != 0)
			return (1);
		i++;
	}
	if (safe_thread_create(&st()->monitor, &state_routine, st()->philos) != 0)
		return (1);
	st()->status = 1;
	if (st()->time_to_die == 0)
		st()->status = 0;
	st()->begin_time = time_ms();
	mutex_unlock(&st()->status_mutex);
	return (0);
}
