/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 15:35:11 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
		if (check_arg(av[i++]))
			return (1);
	if (init_state(av, ac))
		return (1);
	if (init_philos())
		return (1);
	if (init_all_mutex())
		return (1);
	create_all_threads();
	ft_clean();
	return (0);
}
