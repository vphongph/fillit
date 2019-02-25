/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/25 18:10:47 by vphongph         ###   ########.fr       */
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
			if (k < 19 && block.content[0][k + 1] == i_block + 'A')
				reco[l++] = t_east;
			if (k != 0 && block.content[0][k - 1] == i_block + 'A')
				reco[l++] = t_west;
			if (k < 14 && block.content[0][k + 5] == i_block + 'A')
				reco[l++] = t_south;
			if (k > 4 && block.content[0][k - 5] == i_block + 'A')
				reco[l++] = t_north;
		}
	}
	return (ft_atoi(reco));
}

int8_t	parse_block(int16_t ret, t_block *block)
{
	int8_t i;
	int8_t nb_tetros;

	// write(1, block, ret);
	// write(1, "\n", 1);
	i = -1;
	nb_tetros = (ret / 21) + 1;
	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	while (++i < nb_tetros)
	{
		cut_block(&block[i]);
	}
	// write(1, block, ret);
	// printf(PINK"nb block = %d\n"RESET, nb_tetros);
	return (nb_tetros);
}

int8_t	ft_sqrt_victor(int8_t nb_block)
{
	int i = 2;
	while (i * i < nb_block * 4)
		i++;
	return (i);
}

int8_t	place_block_victor(t_block *block, t_map_victor *map_victor)
{

	(void)map_victor;
	(void)block;

	return (0);
}

int8_t	solver_victor(t_map_victor *map_victor, t_block *block)
{
	(void)block;
	(void)map_victor;

	place_block_victor(block, map_victor);

	return (0);
}

void	initialize_map_victor(t_map_victor* map_victor, int16_t ret)
{
	map_victor[0].content[0][0] = 'a';
	map_victor[0].content[0][1] = '\n';
	map_victor[0].content[15][14] = 'z';
	map_victor[0].content[15][15] = '\n';

	(void)ret;
	// printf("%ld\n", sizeof(map_victor[0]));

	// map_victor[0].nb_block = '8';
	printf("%d\n",map_victor[0].nb_block = ret / 21 + 1);
	// map_victor[0].map_victor_size = '9';
	printf("%d\n",map_victor[0].map_size = ft_sqrt_victor(map_victor[0].nb_block));
	ft_bzero_v2(map_victor[0].content, sizeof (map_victor[0].content));
	map_victor[1] = map_victor[0];

	printf("%d\n",map_victor[1].nb_block = ret / 21 + 1);
	printf("%d\n",map_victor[1].map_size = ft_sqrt_victor(map_victor[1].nb_block));

	printf("%d\n",map_victor[0].nb_block = 42);
	printf("%d\n",map_victor[1].nb_block);


}

int		main(int ac, char **av)
{
	t_block block[26];
	// t_map_victor map_victor[2];

	ft_bzero_v2(block, sizeof(block));
	// ft_bzero_v2(map_victor, sizeof(map_victor));

	// initialize_map_victor(map_victor, parse_block(check_main_read(ac, av, block), block));
	// solver_victor(map_victor, block);

	// write(1, &map[0], map[0].map_size * map[0].map_size);

	printf("%ld\n", sizeof(t_block));
	printf("%ld\n", sizeof(t_coords));
	printf("%ld\n", sizeof(t_map));

	solver(parse_block(check_main_read(ac, av, block), block), block);
	return (0);
}

