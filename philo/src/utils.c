/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:32:39 by mateferr          #+#    #+#             */
/*   Updated: 2025/08/25 15:58:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*cs;

	if (!s)
		return ;
	cs = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		cs[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		ptr = malloc(0);
	else if (nmemb <= ((size_t)-1) / size)
		ptr = malloc(nmemb * size);
	else
		return (NULL);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

long	str_to_ml(const char *str)
{
	int		i;
	long	num;

	num = 0;
	i = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	str_to_int(const char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}
