/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:26:08 by vphongph          #+#    #+#             */
/*   Updated: 2018/12/20 01:18:36 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/*
** ATTENTION size_t n
** Penser au type de var (sizeof)
** Et + 1 -> \0 de str (éviter overflow)
*/

void	*ft_memalloc(size_t size)
{
	void *mem;

	if (!(mem = malloc(size)))
	{
		if (ft_putstr_fd_v2(RED"\amemalloc -> malloc ∅\n"RESET, 2) == -1)
			write(2, RED"\amemalloc -> malloc ∅ & putstr fd v2 ∅\n"RESET, 62);
		return (NULL);
	}
	ft_bzero_v2(mem, size);
	return (mem);
}
