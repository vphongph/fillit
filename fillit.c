/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/30 22:00:14 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#include "fillit.h"

int recognize(reco)
{

}

int	check_block(t_block *tetri)
{
	int neighbor = 0;
	int	nb = 0;
	int j = 0;
	int k = 0;

	while (j < 4)
	{
		if (tetri->block[j][4] != '\n')
			return (0);
		while (k < 4)
		{
			if (tetri->block[j][k] != '.' && tetri->block[j][k] != '#')
				return (0);
			if (tetri->block[j][k] == '#' && ++nb)
			{
				if (k != 0 && tetri->block[j][k - 1] == '#')
				{
					neighbor++;
					reco += 'W';
				}
				if (j != 0 && tetri->block[j - 1][k] == '#')
				{
					neighbor++;
					reco += 'N';

				}
			}
			k++;
		}
		k = 0;
		j++;
	}
	if ((neighbor != 3 && neighbor != 4) || nb != 4)
		return (0);
	return (recognize());
}

int *check_map(int fd, t_block *tetri, int *order)
{
	int i = 0;
	int ret;
	ret = read(fd, tetri, BUFF_SIZE);

	printf("%s",tetri[0].block[0]);
	fflush(stdout);

	if (ret % 21 != 20)
	{
		write(1, "error nb\n", 9);
		return (NULL);
	}
	while (i < ((ret / 21) + 1))
	{
		if (i < (ret / 21) && tetri[i].sep != '\n')
		{
			write(1, "error sep\n", 10);
			return (NULL);
		}
		if (!check_block(&tetri[i]))
		{
			write(1, "error content\n", 14);
			return (NULL);
		}
		i++;
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

		check_map(3, tetri, order);
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