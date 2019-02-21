/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/20 23:03:43 by vphongph         ###   ########.fr       */
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

	write(1, block, ret);
	write(1, "\n", 1);
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
	write(1, block, ret);
	printf(PINK"nb block = %d\n"RESET, nb_tetros);
	return (nb_tetros);
}

t_coords	find_next_mino(t_block block, t_coords coords)
{
	if (coords.y < 3 && block.content[coords.y][coords.x] == 0)
	{
		coords.y++;
		coords.x = 0;
	}
	while (coords.x < 3 && block.content[coords.y][coords.x] == '.')
		coords.x++;
	return (coords);
}

int		can_place_mino(t_map map, t_coords coords)
{
	if (!map.content[coords.y][coords.x])
		return (1);
	return (0);
}



int		try_tetro(t_block block, t_map map, t_coords coords, t_coords tetro_coords)
{
	t_coords swap;

	tetro_coords = find_next_mino(block, tetro_coords);
	if (can_place_mino(map, coords))
	{
		swap = tetro_coords;
		tetro_coords.x++;
		tetro_coords = find_next_mino(block, tetro_coords);
		if (block.content[tetro_coords.y][tetro_coords.x])
			return(1);
		coords.x = coords.x - (swap.x - tetro_coords.x);
		coords.y = coords.y - (swap.y - tetro_coords.y);
		return (try_tetro(block, map, coords, tetro_coords));
	}
	return (0);
}

void	write_tetro(t_block block, t_map *map, t_coords coords, t_coords tetro_coords)
{
	t_coords swap;

	while (block.content[tetro_coords.y][tetro_coords.x])
	{
		map->content[coords.y][coords.x] = block.content[tetro_coords.y][tetro_coords.x];
		swap = tetro_coords;
		tetro_coords.x++;
		tetro_coords = find_next_mino(block, tetro_coords);
		coords.x = coords.x - (swap.x - tetro_coords.x);
		coords.y = coords.y - (swap.y - tetro_coords.y);
	}
}

int		is_solved(t_map map, t_block *blocks, int16_t nb_tetros)
{
	(void)nb_tetros;
	t_coords coords;
	t_coords tetro_coords;

	tetro_coords.x = 0;
	tetro_coords.y = 0;
	coords.x = 4;
	coords.y = 4;
	if (try_tetro(blocks[0], map, coords, tetro_coords))
		write_tetro(blocks[0], &map, coords, tetro_coords);
	map.content[4][8] = '\n';
	write(1, &map.content, 16 * 16);
	printf("\n");
	return (1);
}

void	solver(int16_t nb_tetros, t_block *blocks)
{
	t_map	map = {.size = 0};
	int		i;

	i = 0;
	map.size = ft_sqrt(nb_tetros * 4);
	while (!is_solved(map, blocks, nb_tetros))
		map.size++;
	exit(EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_block block[26];

	ft_bzero_v2(block, sizeof(block));
	solver(parse_block(check_main_read(ac, av, block), block), block);
	return (0);
}
