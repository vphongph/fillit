/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/24 23:39:02 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#include "fillit.h"

int *check_parse(int fd, int *order)
{
	int ret;
	char *buf;

	buf = (char *)ft_memalloc(BUFF_SIZE);
	ret = read(fd, buf, BUFF_SIZE)



	return (order);
}

int		main(int ac, char **av)
{

	int i = 0;
	int order[26];
	ft_bzero_v2(tetritab, 26 * sizeof(int));
	if (ac > 2)
	{
		ft_putstr_fd_v2(RED"Too many arguments"RESET, 2);
		return(-1);
	}
	if (ac == 2)
	{
		if (open(av[1], O_RDONLY) == -1)
		{
			ft_putstr_fd_v2(RED"open failed"RESET, 2);
			return (-1);
		}

		check_parse(3, tetritab);

		while (i < 26)
		{
			printf("%d\n", tetritab[i]);
			i++;
		}

		if (close(3) == -1)
		{
			ft_putstr_fd_v2(RED"close failed"RESET, 2);
			return (-1);
		}
	}

	return (0);
}