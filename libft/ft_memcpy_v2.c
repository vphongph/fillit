/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 01:49:59 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/08 23:16:19 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_cpy8(void **dst, void **src, size_t *n)
{
	while (*n / sizeof(long long))
	{
		**(long long **)dst = **(long long **)src;
		*src += sizeof(long long);
		*dst += sizeof(long long);
		*n -= sizeof(long long);
	}
	while (*n / sizeof(int))
	{
		**(int **)dst = **(int **)src;
		*src += sizeof(int);
		*dst += sizeof(int);
		*n -= sizeof(int);
	}
}

/*
** ATTENTION size_t n
** Penser au type de var (sizeof)
** Et + 1 -> cpy \0 de str s'il existe (éviter overflow)
** Si len = 0, src NULL ok
*/

void		*ft_memcpy_v2(void *dst, void *src, size_t n)
{
	void	*tmp;

	if (!dst || (n && !src))
	{
		if (ft_putstr_fd_v2(RED"\amemcpy v2 -> ∅ pointer\n"RESET, 2) == -1)
			write(2, RED"\amemcpy v2 -> ∅ pointer & putstr fd v2 ∅\n"RESET, 64);
		return (NULL);
	}
	tmp = dst;
	ft_cpy8(&dst, &src, &n);
	while (n / sizeof(short))
	{
		*(short *)dst = *(short *)src;
		src += sizeof(short);
		dst += sizeof(short);
		n -= sizeof(short);
	}
	if (n)
		*(char *)dst = *(char *)src;
	return (tmp);
}
