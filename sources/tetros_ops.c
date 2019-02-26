/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetros_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 02:45:29 by mtorsell          #+#    #+#             */
/*   Updated: 2019/02/26 02:45:33 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** RECOGNIZE TETRO
** -> Donne un id unique aux tétriminos différents.
** __ATTENTION__ sens de lecture important pour le recognize,
** sinon conflit entre le S et L90.
** Il faut droite gauche et bas haut.
** Si gauche droite et haut bas, lire à l'envers.
** Et la valeur du voisin est arbitraire,
** Ouest = 1, Nord = 2, Est = 3, Sud = 4.
** __ATTENTION__, bien renseigner le i correspondant au i du block[i].
*/

int32_t	recognize_tetro(t_block block, int8_t i_block)
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

t_x_y	find_tetro(t_map map, char id, int bef_char)
{
	t_x_y x_y;

	x_y.x = 0 - bef_char;
	x_y.y = 0;
	while (x_y.y < map.size)
	{
		while (x_y.x < map.size)
		{
			if (map.content[x_y.y][x_y.x] == id)
			{
				x_y.x -= bef_char;
				return (x_y);
			}
			x_y.x++;
		}
		x_y.x = 0;
		x_y.y++;
	}
	return (x_y);
}

int		try_tetro(t_block block, t_map map)
{
	int8_t		mino_placed;
	t_x_y		swap;
	t_x_y		tetro_x_y;

	tetro_x_y.x = 0;
	tetro_x_y.y = 0;
	mino_placed = 0;
	swap = tetro_x_y;
	tetro_x_y = find_next_mino(block, tetro_x_y);
	map.x_y.x = map.x_y.x - (swap.x - tetro_x_y.x);
	map.x_y.y = map.x_y.y - (swap.y - tetro_x_y.y);
	while (block.content[tetro_x_y.y][tetro_x_y.x] && can_place_mino(map))
	{
		mino_placed++;
		if (mino_placed == 4)
			return (1);
		swap = tetro_x_y;
		tetro_x_y.x++;
		tetro_x_y = find_next_mino(block, tetro_x_y);
		map.x_y.x = map.x_y.x - (swap.x - tetro_x_y.x);
		map.x_y.y = map.x_y.y - (swap.y - tetro_x_y.y);
	}
	return (0);
}
