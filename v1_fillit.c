/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v1_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/15 20:58:44 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#include "fillit.h"

/*
** *(int *) Déréférencer cast int ==> Lire un int (de la taille de 4 octets)
** à partir de l'adresse suivante
** *(int *)"...." = 2e2e2e2e
** tetri->block[j] = &tetri->block[j][0]
** printd("%08x") pour 8 bits en hexa avec le 0x
** & 00, met tout à 0 donc pour ignorer
** & ff, met tous les bits de 1 à 1, char à chercher.
** __DARWIN_BYTE_ORDER = __DARWIN_LITTLE_ENDIAN
*/

// printf("adresse 00 32 :%p, data 32 : %#.08x\n",(uint32_t *)&(tetri->block[0][0]), *(uint32_t *)&(tetri->block[0][0]));
// printf("adresse 00 64 :%p, data 64 : %#.016llx\n",(uint64_t *)&(tetri->block[0][0]), *(uint64_t *)&(tetri->block[0][0]));
// printf("adresse 01 32 :%p, data 32 : %#.08x\n",(uint32_t *)&(tetri->block[0][1]), *(unsigned int *)&(tetri->block[0][1]));
// printf("adresse 01 64 :%p, data 64 : %#.016llx\n",(uint64_t *)&(tetri->block[0][1]), *(uint64_t *)&(tetri->block[0][1]));
// printf("column literal AND: %#.016llx\n",*(uint64_t *)".xxxx.xx" & 0x0000ff00000000ff);
// printf("column block   AND: %#.016llx\n",*(uint64_t *)tetri->block[0] & 0x0000ff00000000ff);

void cut_block(t_block *tetri)
{
	uint64_t endian = 0;

	if ((char)0x3132 == 0x31)
		endian = 0xff00000000ff0000;
	else
		endian = 0xff00000000ff;

	int j = 0;

	while (j < 4)
	{
		if (j > 0 && *(int *)tetri->block[j] != *(int *)"...."
			&& *(int *)tetri->block[j - 1] == *(int *)"....")
		{
			*(int *)tetri->block[j - 1] = *(int *)tetri->block[j];
			*(int *)tetri->block[j] = 0x2e2e2e2e;
			j = 0;
		}
			// if ((*(uint64_t *)tetri->block[0] & endian)
			// 	== (*(uint64_t *)".xxxx.xx" & endian)
			// 		&& (*(uint64_t *)tetri->block[2] & endian)
			// 			== (*(uint64_t *)".xxxx.xx" & endian))
			// {
			// 	*(int *)tetri->block[0] = *(int *)tetri->block[0] >> 8;
			// 	*(int *)tetri->block[1] = *(int *)tetri->block[1] >> 8;
			// 	*(int *)tetri->block[2] = *(int *)tetri->block[2] >> 8;
			// 	*(int *)tetri->block[3] = *(int *)tetri->block[3] >> 8;
			// }
		j++;
	}
	// j = 3;
	// k = 0xff;

	// printf("%#08x\n", j & k);

	// while (*(int *)tetri->block[0] == 0x2e2e2e2e)
	// {
	// 	while ((*(int *)tetri->block[j] == 0x2e2e2e2e) && j < 3)
	// 	{
	// 		*(int *)tetri->block[j] = *(int *)tetri->block[j + 1];
	// 		*(int *)tetri->block[j + 1] = 0x2e2e2e2e;
	// 		j++;
	// 	}
	// 	j = 0;
	// }
	// while (k < 4)
	// {
	// 	if (k != 0 && tetri->block[j][k - 1] == '.')
	// 	{
	// 		tetri->block[j][k - 1] = '#';
	// 		tetri->block[j][k] = '.';
	// 	}
	// 	k++;
	// }
	// k = 0;
	// j = 0;
	// while (j < 4)
	// {
	// 	while (k < 4)
	// 	{
	// 		if (tetri->block[j][k] == '#')
	// 		{
	// 			if (k != 3 && tetri->block[j][k + 1] == '.')
	// 				tetri->block[j][k + 1] = '*';
	// 			if (j != 3 && tetri->block[j + 1][k] == '.')
	// 				tetri->block[j + 1][k] = '*';
	// 		}
	// 		k++;
	// 	}
	// 	k = 0;
	// 	j++;
	// }
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
					neighbor++;
				if (j != 0 && tetri->block[j - 1][k] == '#')
					neighbor++;
			}
			k++;
		}
		k = 0;
		j++;
	}
	if ((neighbor != 3 && neighbor != 4) || nb != 4)
		return (0);
	return (1);
}

int *check_map(int fd, t_block *tetri, int *order)
{
	int i = 0;
	int ret;
	ret = read(fd, tetri, BUFF_SIZE);

	write(1,tetri[0].block[0],ret);

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

		cut_block(&tetri[i]);
		i++;
	}
	ft_putstr_fd_v2(YELLOW"AFTER CUT\n"RESET, 1);
	write(1, "\n", 1);
	write(1,tetri[0].block[0],ret);

	return (order);
}

int		main(int ac, char **av)
{
	// int i = 0;
	// int j = 0;
	int order[26];
	t_block tetri[26];
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