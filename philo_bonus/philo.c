/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:39:05 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/08 19:49:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (p_error("Invalid number of arguments\n"), 1);
	if (validate_args(av) == false)
		return (1);
	if (ft_init(av) == false)
		return (ft_clear(), 1);
	if (!processes_creation())
	{
		sim()->processes = 0;
		while (sim()->child_pids[sim()->processes] != -1)
			kill(sim()->child_pids[sim()->processes++], SIGKILL);
		return (ft_clear(), 1);
	}
	ft_clear();
	return (0);
}
