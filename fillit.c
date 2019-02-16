/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/16 22:19:19 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"


#include <stdio.h>



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
** RECOGNIZE BLOCK
** -> Donne un id unique aux tétriminos différents.
** __ATTENTION__ sens de lecture important pour le recognize,
** sinon conflit entre le S et L90.
** Il faut droite gauche et bas haut.
** Si gauche droite et haut bas, lire à l'envers.
** Et la valeur du voisin est arbitraire,
** Ouest = 1, Nord = 2, Est = 3, Sud = 4.
** __ATTENTION__, bien renseigner le i correspondant au i du block[i].
*/

int32_t	recognize_block(t_block block, int8_t i_block)
{
	int8_t	k;
	int8_t	l;
	char	reco[9];

	k = -1;
	l = 0;
	ft_bzero_v2(reco, sizeof(reco));
	while (++k < 19)
	{
		if (block.content[0][k] == i_block + 'A')
		{
			if (k < 19 && block.content[0][k + 1] == i_block + 'A')
				reco[l++] = '3';
			if (k != 0 && block.content[0][k - 1] == i_block + 'A')
				reco[l++] = '1';
			if (k < 14 && block.content[0][k + 5] == i_block + 'A')
				reco[l++] = '4';
			if (k > 4 && block.content[0][k - 5] == i_block + 'A')
				reco[l++] = '2';
		}
	}
	return (ft_atoi(reco));
}

void	parse_block(int16_t ret, t_block *block)
{
	int8_t i;

	i = -1;
	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	while (++i < ((ret / 21) + 1))
		cut_block(&block[i]);
	printf(PINK"nb block = %d\n"RESET, ret / 21 + 1);
}

int		main(int ac, char **av)
{
	t_block block[26];

	// int32_t	order[27];
	ft_bzero_v2(block, sizeof(block));
	// ft_bzero_v2(order, sizeof(order));
	parse_block(check_main_read(ac, av, block), block);
	return (0);
}
