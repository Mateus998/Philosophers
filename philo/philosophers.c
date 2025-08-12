/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:25:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/12 12:59:43 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
    int i;
    
    if (ac < 5 || ac > 6)
        return (0);
    init()->number_of_philosophers = str_to_int(*av[1]);
    init()->time_to_die = str_to_ml(*av[2]);
    init()->time_to_eat = str_to_ml(*av[3]);
    init()->time_to_sleep = str_to_ml(*av[4]);
    i = 1;
    while (i <= init()->number_of_philosophers)
    {
        pthread_create()
    }
}
