/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:34:10 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/29 00:40:55 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

#include <stdio.h>

static void	ft_zero512(void **s, size_t *n, int *i)
{
	static t_64speed	speed64;
	static t_512speed	speed512;

	while (*n >> 9)
	{
		**(t_512speed **)s = speed512;
		*s += 512;
		*n -= 512;
		*i += 512;
	}
	while (*n >> 6)
	{
		**(t_64speed **)s = speed64;
		*s += 64;
		*n -= 64;
		*i += 64;
	}
}

void		ft_bzero_v2(void *s, size_t n)
{
	int i = 0;
	if (!s)
	{
		if (ft_putstr_fd_v2(RED"\abzero v2 -> ∅ pointer\n"RESET, 2) == -1)
			write(2, RED"\abzero v2 -> ∅ pointer & putstr fd v2 ∅\n"RESET, 63);
		return ;
	}
	ft_zero512(&s, &n, &i);
	while (n >> 3)
	{
		*(long long *)s = 0;
		s += 8;
		n -= 8;
		i += 8;
	}
	while (n)
	{
		*(char *)s = 0;
		s++;
		n--;
		i++;
	}
	printf("address bzero pointer = %p\n", s);
	printf("i bzero = %d\n", i);
}


