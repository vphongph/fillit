/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:53:37 by mtorsell          #+#    #+#             */
/*   Updated: 2019/02/25 20:14:06 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int8_t	ft_sqrt(int8_t area_mini)
{
	int8_t i;

	i = 2;
	while (i * i < area_mini)
		i++;
	return (i);
}

int		solver_iter(t_map *map, t_block *blocks, int16_t nb_tetros)
{
	int8_t i;

	i = 0;
	while (i < nb_tetros)
	{
		find_next_empty(map);
		if (try_tetro(blocks[i], *map))
		{
			write_tetro(blocks[i++], map);
			map->x_y.x = -1;
			map->x_y.y = 0;
		}
		else
		{
			if (map->x_y.x >= map->size && map->x_y.y >= map->size)
			{
				i--;
				if (i < 0
					|| recognize_tetro(blocks[i], i)
					== recognize_tetro(blocks[i + 1], i + 1))
					return (0);
				map->x_y = find_tetro(*map, 'A' + i, skip_empty(blocks[i]));
				delete_tetro(map, 'A' + i);
			}
		}
	}
	return (1);
}

int		is_solved(t_map *map, t_block *blocks, int16_t nb_tetros)
{
	ft_bzero_v2(map->content, 16 * 16);
	map->x_y.x = -1;
	map->x_y.y = 0;
	if (solver_iter(map, blocks, nb_tetros))
		return (1);
	return (0);
}

void	solver(int16_t nb_tetros, t_block *blocks)
{
	int i;
	t_map map;

	i = 0;
	map.size = ft_sqrt(nb_tetros * 4);
	while (is_solved(&map, blocks, nb_tetros) != 1)
		map.size++;
	print_map(map);
	exit(EXIT_SUCCESS);
}


