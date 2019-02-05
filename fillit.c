/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/05 17:07:29 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// #include <malloc/malloc.h>


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

// if ((char)0x3132 == 0x31)
// 	endian = 0xff00000000ff0000;
// else
// 	endian = 0xff00000000ff;

/*
** ATTENTION JE SUIS MALADE, BLACK MAGIC
*/

/*
** cut_block NEIGHBOR SHORT version
*/
#define DETECTSHARP(X) (~(X - 0x24242424))
#define DETECTNULL(X) ((X - 0x01010101) & ~X & 0x80808080)
// #define DETECTSHARP(X) DETECTNULL(~(X - 0x24242424))

int		detectnull(int c)
{
	c = (c - 0x01010101) & ~c;
	c = c & 0x80808080;
	return (c);
}

int		detectsharp(int c)
{
	c = ~(c - 0x24242424) & ~c;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

void	cut_block_short(t_block *tetri)
{
	uint8_t k;
	uint8_t nb;

	nb = 0;
	k = -1;
	while (*(uint32_t *)tetri->block[0] == *(uint32_t *)"....")
		if ((*(uint32_t *)tetri->block[0] = *(uint32_t *)tetri->block[1]))
			if ((*(uint32_t *)tetri->block[1] = *(uint32_t *)tetri->block[2]))
				if ((*(uint32_t *)tetri->block[2] = *(uint32_t *)tetri->block[3]))
					*(uint32_t *)tetri->block[3] = *(uint32_t *)"....";
	while ((*(uint64_t *)tetri->block[0] & 0xff00000000ff)
		== (*(uint64_t *)".xxxx.xx" & 0xff00000000ff)
			&& (*(uint64_t *)tetri->block[2] & 0xff00000000ff)
				== (*(uint64_t *)".xxxx.xx" & 0xff00000000ff))
		if ((*(int *)tetri->block[0] = *(int *)tetri->block[0] >> 8))
			if ((*(int *)tetri->block[1] = *(int *)tetri->block[1] >> 8))
				if ((*(int *)tetri->block[2] = *(int *)tetri->block[2] >> 8))
					*(int *)tetri->block[3] = *(int *)tetri->block[3] >> 8;
	k = 0;
	while (k < 16)
	{
		if (!(detectsharp(*(uint32_t *)&tetri->block[0][k])))
			*(uint32_t *)&tetri->block[0][k] = *(uint32_t *)"----";
		k += 5;
	}
}

int		check_block(t_block *tetri)
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

int		*check_map(int fd, t_block *tetri, int *order)
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
	printf("nb tetri = %d\n", ret / 21 + 1);
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

		cut_block_short(&tetri[i]);
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

		unsigned int z = 0x23230000;
		// printf("\nz : -%c- , sharp : %#.08x\n", z, DETECTSHARP(0x23232323));
		printf("\nz : -%c- , sharp : %#.08x\n", z, detectsharp(0x00760076));
		// printf("z : -%c- , sharp : %#.08x\n", z, DETECTNULL(DETECTSHARP(*(int *)"\0\0#\0")));
		printf("z : -%c- , sharp : %#.08x\n", z, detectnull(0x42002323));

		if (close(3) == -1)
		{
			ft_putstr_fd_v2(RED"close failed"RESET, 2);
			return (-1);
		}
	}

	return (0);
}