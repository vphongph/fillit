/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/12 03:12:19 by vphongph         ###   ########.fr       */
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
** block->content[j] = &block->content[j][0]
** printf("%08x") pour 8 bits en hexa avec le 0x
** & 00, met tout à 0 donc pour ignorer
** & ff, met tous les bits de 1 à 1, char à chercher.
** __DARWIN_BYTE_ORDER = __DARWIN_LITTLE_ENDIAN ou mes tests
** (voir brouillons fillit)
*/

/*
** ATTENTION JE SUIS MALADE
*/

void	set_char(t_block *block)
{
	static char c = 'A';
	int8_t i;

	i = -1;
	while (++i < 19)
		if (block->content[0][i] == '#')
			block->content[0][i] = c;
	c++;
}

int32_t	detectsharp(int32_t c)
{
	c = ~(c - 0x24242424) & ~c;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

void	delimit_block(t_block *block)
{
	int8_t k;

	k = 0;
	while (k <= 15)
	{
		if (!(k % 5) && !(detectsharp(*(int32_t *)&block->content[0][k])))
			*(int32_t *)&block->content[0][k] = *(int32_t *)"----";
			// *(int32_t *)&block->content[0][k] = 0;
		if (block->content[0][k] == '#' && block->content[0][k + 1] == '.')
			block->content[0][k + 1] = '*';
		k++;
	}
}

void	cut_block(t_block *block)
{
	while (*(int32_t *)block->content[0] == *(int32_t *)"....")
	{
		*(int32_t *)block->content[0] = *(int32_t *)block->content[1];
		*(int32_t *)block->content[1] = *(int32_t *)block->content[2];
		*(int32_t *)block->content[2] = *(int32_t *)block->content[3];
		*(int32_t *)block->content[3] = *(int32_t *)"....";
	}
	while ((*(int64_t *)block->content[0] & MASK_1STCOL)
		== (*(int64_t *)".xxxx.xx" & MASK_1STCOL)
			&& (*(int64_t *)block->content[2] & MASK_1STCOL)
				== (*(int64_t *)".xxxx.xx" & MASK_1STCOL))
	{
		*(int32_t *)block->content[0] = *(int32_t *)block->content[0] >> 8;
		*(int32_t *)block->content[1] = *(int32_t *)block->content[1] >> 8;
		*(int32_t *)block->content[2] = *(int32_t *)block->content[2] >> 8;
		*(int32_t *)block->content[3] = *(int32_t *)block->content[3] >> 8;
	}
	delimit_block(block);
}

/*
** ATTENTION sens de lecture important pour le recognize, sinon conflit entre le S et L90
** il faut droite gauche et bas haut. Si droite gauche et haut bas, lire à l'envers.
*/

int		recognize_block(t_block *block)
{
	int8_t i;
	int8_t j;
	char reco[9];

	i = -1;
	j = 0;
	ft_bzero_v2(reco, sizeof(reco));
	while (++i < 19)
	{
		if (block->content[0][i] == '#')
		{
			if (i < 19 && block->content[0][i + 1] == '#')
				reco[j++] = '3';
			if (i != 0 && block->content[0][i - 1] == '#')
				reco[j++] = '1';
			if (i < 14 && block->content[0][i + 5] == '#')
				reco[j++] = '4';
			if (i > 4 && block->content[0][i - 5] == '#')
				reco[j++] = '2';
		}
	}
	printf(ORDER"%s\n"RESET, reco);
	return (ft_atoi(reco));
}

int8_t	check_nl(t_block block)
{
	if ((*(int64_t *)&block.content[0][2] & MASK_NL)
		== (*(int64_t *)"xx\nxxxx\n" & MASK_NL)
			&& (*(int64_t *)&block.content[0][12] & MASK_NL)
				== (*(int64_t *)"xx\nxxxx\n" & MASK_NL))
		return (1);
	return (0);
}

int8_t	check_content(t_block block)
{
	int8_t	neighbor;
	int8_t	nb;
	int8_t	k;

	neighbor = 0;
	nb = 0;
	k = -1;
	while (++k <= 18)
	{
		if (block.content[0][k] == '#' && ++nb)
		{
			if (k > 0 && block.content[0][k - 1] == '#')
				neighbor++;
			if (k > 4 && block.content[0][k - 5] == '#')
				neighbor++;
		}
		else if ((k - 4) % 5 && block.content[0][k] != '.')
			return (0);
	}
	if ((check_nl(block) && (neighbor == 3 || neighbor == 4) && nb == 4))
		return (1);
	return (0);
}

int8_t	check_block(int16_t ret, t_block *block)
{
	int8_t i;

	i = 0;
	if (ret % 21 != 20 || ret > BUFF_SIZE)
		return (0);
	while (i < ((ret / 21) + 1))
	{
		if (i < (ret / 21) && block[i].sep != '\n')
			return (0);
		if (!check_content(block[i]))
			return (0);
		i++;
	}
	return (1);
}


int		*parse_block(int16_t ret, t_block *block, int *order)
{
	int8_t i;

	i = 0;

	write(1,block[0].content[0],ret);

	if (!check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		return(NULL);
	}

	while (i < ((ret / 21) + 1))
	{
		cut_block(&block[i]);
		order[i] = recognize_block(&block[i]);
		set_char(&block[i]);
		i++;
	}

	ft_putstr_fd_v2(YELLOW"AFTER CUT\n"RESET, 1);
	write(1, "\n", 1);
	write(1,block[0].content[0],ret);

	printf(PINK"nb block = %d\n\n"RESET, ret / 21 + 1);

	i = 0;
	int tmp = 0;
	while (order[i])
	{
		if (i > 0 && order[i] < order[i - 1])
		{
			tmp = order[i];
			order[i] = order[i - 1];
			order[i - 1] = tmp;
			i--;
		}
		else
			i++;
	}
	i = -1;
	while (order[++i])
		printf(ALLIANCE"%d\n"RESET, order[i]);
	printf("\n");

	i = -1;
	int j = -1;
	while (order[++j])
	{
		while (order[++i])
		{
			if (j != i && order[j] == order[i])
			{
				printf(YELLOW"LAME!\n"RESET);
				return (NULL);
			}
		}
		i = -1;
	}
	return (order);
}

int16_t check_main_read(int ac, char **av, t_block *block)
{
	int16_t ret;

	// ret = 0;
	if (ac != 2)
	{
		ft_putstr_fd_v2("usage : ./fillit [FILE] (with a valid format)\n", 1);
		return (-1);
	}
	if (open(av[1], O_RDONLY) == -1)
		return (-1);
	ret = read(3, block, BUFF_SIZE + 1);
	if (close(3) == -1)
		return (-1);
	return (ret);
}

int		main(int ac, char **av)
{
	t_block block[26];
	int order[27];
	ft_bzero_v2(block, sizeof(block));
	ft_bzero_v2(order, sizeof(order));

	if (!parse_block(check_main_read(ac, av, block), block, order))
		return (-1);

	return (0);
}
