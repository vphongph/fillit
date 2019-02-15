/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/15 22:36:09 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "fillit.h"

/*
** REMARQUES PERSO SUR CE PROJET
** *(int *) Déréférencer cast int ==> Lire un int (de la taille de 4 octets)
** à partir de l'adresse suivante.
** *(int *)"...." = 2e2e2e2e
** block->content[j] = &block->content[j][0]
** printf("%08x") pour 8 bits en hexa avec le 0x
** & 00, met tout à 0 donc pour ignorer
** & ff, met tous les bits de 1 à 1, char à chercher.
** __DARWIN_BYTE_ORDER = __DARWIN_LITTLE_ENDIAN ou mes tests
** (voir brouillons fillit)
**
**
** ATTENTION JE SUIS MALADE
*/

/*
** SET CHAR
** -> Donne à l'ordre d'arrivée des tétriminos les lettres correspondantes,
** first = A, last = Z.
*/

void	set_char(t_block *block)
{
	static char c = 'A';
	int8_t		i;

	i = -1;
	while (++i < 19)
		if (block->content[0][i] == '#')
			block->content[0][i] = c;
	c++;
}

/*
** RECOGNIZE BLOCK
** -> Donne un id unique aux tétriminos différents.
** __ATTENTION__ sens de lecture important pour le recognize,
** sinon conflit entre le S et L90.
** Il faut droite gauche et bas haut.
** Si gauche droite et haut bas, lire à l'envers.
*/

int32_t	recognize_block(t_block *block, int8_t i)
{
	int8_t	k;
	int8_t	l;
	char	reco[9];

	k = -1;
	l = 0;
	ft_bzero_v2(reco, sizeof(reco));
	while (++k < 19)
	{
		if (block->content[0][k] == i + 'A')
		{
			if (k < 19 && block->content[0][k + 1] == i + 'A')
				reco[l++] = '3';
			if (k != 0 && block->content[0][k - 1] == i + 'A')
				reco[l++] = '1';
			if (k < 14 && block->content[0][k + 5] == i + 'A')
				reco[l++] = '4';
			if (k > 4 && block->content[0][k - 5] == i + 'A')
				reco[l++] = '2';
		}
	}
	printf(ORDER"%s\n"RESET, reco);
	return (ft_atoi(reco));
}

int32_t	*parse_block(int16_t ret, t_block *block, int32_t *order)
{
	int8_t i;

	i = 0;

	write(1,block[0].content[0],ret);

	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}

	while (i < ((ret / 21) + 1))
	{
		cut_block(&block[i]);
		set_char(&block[i]);
		order[i] = recognize_block(&block[i], i);
		// set_char(&block[i]);
		i++;
	}

/*
** Après parsing des tétri, on place l'id (suite à la reco) dans un tableau d'int.
** On trie par ordre croissant
** Check que id est unique, sinon LAME !
*/

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
	int 	j = -1;
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

int		main(int ac, char **av)
{
	t_block block[26];
	int32_t	order[27];

	ft_bzero_v2(block, sizeof(block));
	ft_bzero_v2(order, sizeof(order));
	parse_block(check_main_read(ac, av, block), block, order);
	return (0);
}
