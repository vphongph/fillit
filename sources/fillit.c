/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/22 22:38:12 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"


#include <stdio.h>
#include <unistd.h>

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
	while (++k <= 15)
	{
		if (block.content[0][k] == i_block + 'A')
		{
			if (block.content[0][k + 1] == i_block + 'A')
				reco[l++] = '3';
			if (k >= 1 && block.content[0][k - 1] == i_block + 'A')
				reco[l++] = '1';
			if (k <= 10 && block.content[0][k + 5] == i_block + 'A')
				reco[l++] = '4';
			if (k >= 5 && block.content[0][k - 5] == i_block + 'A')
				reco[l++] = '2';
		}
	}
	return (ft_atoi(reco));
}

int16_t	parse_block(int16_t ret, t_block *block)
{
	int8_t i;

	write(1, block, ret);
	write(1, "\n", 1);
	i = -1;
	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	while (++i < ((ret / 21) + 1))
	{
		cut_block(&block[i]);
	}
	write(1, block, ret);
	printf(PINK"nb block = %d\n"RESET, ret / 21 + 1);
	return (ret);
}

int		main(int ac, char **av)
{
	t_block block[26];

	ft_bzero_v2(block, sizeof(block));
	parse_block(check_main_read(ac, av, block), block);
	return (0);
}
