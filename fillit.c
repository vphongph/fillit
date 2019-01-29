/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/29 17:58:59 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#include "fillit.h"

int check_map(int fd, t_block *tetri, int *order)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int ret;
	ret = read(fd, tetri, BUFF_SIZE);
	printf("ret = %d\n",ret);

	printf("%s",tetri[0].block[0]);
	fflush(stdout);

	if (ret % 21 != 20)
	{
		write(1, "error nb\n", 9);
		return (NULL);
	}
	while (i < ((ret / 21) + 1))
	{
		while (j < 4)
		{
			while (k < 4)
			{
				if (tetri[i].block[j][k] != '.' && tetri[i].block[j][k] != '#')
				{
					write(1, "error content\n", 14);
					return (NULL);
				}
				k++;
			}
			k = 0;
			if (tetri[i].block[j++][4] != '\n')
			{
				write(1, "error EOL\n", 10);
				return (NULL);
			}
		}
		j = 0;
		i++;
	}
	i = 0;
	while (i < (ret / 21))
	{
		printf("sep = %c", tetri[i].sep);
		if (tetri[i++].sep != '\n')
		{
			write(1, "error sep\n", 10);
			return (NULL);
		}
	}

	return (order);
}

int		main(int ac, char **av)
{
	// int i = 0;
	// int j = 0;
	int order[26];
	t_block tetri[26];
	tetri[25].sep = 'Z';
	ft_bzero_v2(tetri, sizeof(tetri));
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

		check_parse(3, tetri, order);
		// while (i < 26)
		// {
		// 	while (j < 4)
		// 	{
		// 		printf("%s\n",tetri[i].block[j]);
		// 		printf("%c\n",tetri[i].sep);
		// 		printf("%d %d\n", i, j);
		// 		j++;
		// 	}
		// 	j = 0;
		// 	i++;
		// }

		if (close(3) == -1)
		{
			ft_putstr_fd_v2(RED"close failed"RESET, 2);
			return (-1);
		}
	}

	return (0);
}