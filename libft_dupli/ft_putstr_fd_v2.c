/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:13:49 by vphongph          #+#    #+#             */
/*   Updated: 2018/12/18 20:23:39 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_putstr_fd_v2(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
	{
		write(2, RED"\aputstr fd v2 -> ∅ pointer\n"RESET, 48);
		return (-1);
	}
	if ((i = write(fd, s, ft_strlen_v2(s))) == -1)
	{
		write(2, RED"\aputstr fd v2 -> write ∅\n"RESET, 46);
		return (-1);
	}
	return (i);
}
