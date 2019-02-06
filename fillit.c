/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/06 17:55:43 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "fillit.h"

/*
** *(int *) Déréférencer cast int ==> Lire un int (de la taille de 4 octets)
** à partir de l'adresse suivante
** *(int *)"...." = 2e2e2e2e
** tetri->block[j] = &tetri->block[j][0]
** printd("%08x") pour 8 bits en hexa avec le 0x
** & 00, met tout à 0 donc pour ignorer
** & ff, met tous les bits de 1 à 1, char à chercher.
** __DARWIN_BYTE_ORDER = __DARWIN_LITTLE_ENDIAN ou mes test (voir brouillons fillit)
*/

/*
** ATTENTION JE SUIS MALADE, BLACK MAGIC
*/

uint32_t	detectsharp(uint32_t c)
{
	c = ~(c - 0x24242424) & ~c;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

void	cut_block_short(t_block *tetri)
{
	uint8_t k;

	k = -1;
	while (*(uint32_t *)tetri->block[0] == *(uint32_t *)"....")
	{
		*(uint32_t *)tetri->block[0] = *(uint32_t *)tetri->block[1];
		*(uint32_t *)tetri->block[1] = *(uint32_t *)tetri->block[2];
		*(uint32_t *)tetri->block[2] = *(uint32_t *)tetri->block[3];
		*(uint32_t *)tetri->block[3] = *(uint32_t *)"....";
	}
	while ((*(uint64_t *)tetri->block[0] & 0xff00000000ff)
		== (*(uint64_t *)".xxxx.xx" & 0xff00000000ff)
			&& (*(uint64_t *)tetri->block[2] & 0xff00000000ff)
				== (*(uint64_t *)".xxxx.xx" & 0xff00000000ff))
	{
		*(int *)tetri->block[0] = *(int *)tetri->block[0] >> 8;
		*(int *)tetri->block[1] = *(int *)tetri->block[1] >> 8;
		*(int *)tetri->block[2] = *(int *)tetri->block[2] >> 8;
		*(int *)tetri->block[3] = *(int *)tetri->block[3] >> 8;
	}
	while (++k < 16)
	{
		if (!(k % 5) && !(detectsharp(*(uint32_t *)&tetri->block[0][k])))
			// *(uint32_t *)&tetri->block[0][k] = *(uint32_t *)"----";
			*(uint32_t *)&tetri->block[0][k] = 0;
		if (tetri->block[0][k] == '#' && tetri->block[0][k + 1] == '.')
			tetri->block[0][k + 1] = 0;
	}
}

int		recognize(t_block *tetri)
{
	uint8_t i;
	uint8_t j;

	char reco[9];

	ft_bzero_v2(reco, sizeof(reco));
	i = -1;
	j = 0;
	while (++i < 18)
	{
		if (tetri->block[0][i] == '#')
		{
			if (i != 0 && tetri->block[0][i - 1] == '#')
				reco[j++] = '1';
			if (i < 14 && tetri->block[0][i + 1] == '#')
				reco[j++] = '3';
			if (i > 4 && tetri->block[0][i - 5] == '#')
				reco[j++] = '2';
			if (i < 14 && tetri->block[0][i + 5] == '#')
				reco[j++] = '4';
		}
	}
	return (ft_atoi(reco));
}


int		check_block(t_block *tetri)
{
	int neighbor = 0;
	char reco[8];
	int	nb = 0;
	int j = 0;
	int k = 0;

	ft_bzero_v2(reco, sizeof(reco));

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
	int tab[27];

	ft_bzero_v2(tab, sizeof(tab));

	write(1,tetri[0].block[0],ret);

	if (ret % 21 != 20)
	{
		write(1, "error nb\n", 9);
		return (NULL);
	}
	printf("nb tetri = %d\n\n", ret / 21 + 1);
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
		tab[i] = recognize(&tetri[i]);
		i++;
	}
	i = 0;
	int tmp = 0;
	while (tab[i])
	{
		if (i > 0 && tab[i] < tab[i - 1])
		{
			tmp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = tmp;
			i--;
		}
		else
			i++;
	}
	i = -1;
	int j = 0;
	while (tab[++i])
		printf("%d\n", tab[i]);

	i = -1;
	j = -1;
	while (tab[++j])
	{
		while (tab[++i])
		{
			if (j != i && tab[j] == tab[i])
				write (1, "LAME!", 5);
		}
		i = -1;
	}

	ft_putstr_fd_v2(YELLOW"AFTER CUT\n"RESET, 1);
	write(1, "\n", 1);
	write(1,tetri[0].block[0],ret);

	return (order);
}

int		main(int ac, char **av)
{
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

		if (close(3) == -1)
		{
			ft_putstr_fd_v2(RED"close failed"RESET, 2);
			return (-1);
		}
	}

	return (0);
}
