/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 02:45:42 by mtorsell          #+#    #+#             */
/*   Updated: 2019/02/26 02:45:45 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_map(t_map map)
{
	int	i;
	int y;

	i = 0;
	y = 0;
	while (i < map.size * map.size)
	{
		if (map.content[i / map.size][i % map.size] == 0)
			map.content[i / map.size][i % map.size] = '.';
		i++;
	}
	while (y < map.size)
	{
		ft_putstr_fd_v2(map.content[y++], 1);
		ft_putstr_fd_v2("\n", 1);
	}
}

void	sanitize_map(t_map *map)
{
	int	i;
	int x;
	int y;

	i = 0;
	while (i < map->size * map->size)
	{
		y = i / map->size;
		x = i % map->size;
		if (map->content[y][x] == '.' || map->content[y][x] == '\n')
			map->content[i / map->size][i % map->size] = 0;
		i++;
	}
}

void	write_tetro(t_block block, t_map *map)
{
	t_x_y swap;
	t_x_y x_y;
	t_x_y tetro_x_y;

	tetro_x_y.x = 0;
	tetro_x_y.y = 0;
	swap = tetro_x_y;
	x_y = map->x_y;
	tetro_x_y = find_next_mino(block, tetro_x_y);
	x_y.x = x_y.x - (swap.x - tetro_x_y.x);
	x_y.y = x_y.y - (swap.y - tetro_x_y.y);
	while (block.content[tetro_x_y.y][tetro_x_y.x])
	{
		map->content[x_y.y][x_y.x] = block.content[tetro_x_y.y][tetro_x_y.x];
		swap = tetro_x_y;
		tetro_x_y.x++;
		tetro_x_y = find_next_mino(block, tetro_x_y);
		x_y.x = x_y.x - (swap.x - tetro_x_y.x);
		x_y.y = x_y.y - (swap.y - tetro_x_y.y);
	}
	sanitize_map(map);
}

void	find_next_empty(t_map *map)
{
	int8_t	x;
	int8_t	y;

	x = map->x_y.x + 1;
	y = map->x_y.y;
	if (x >= map->size)
	{
		x = 0;
		y++;
	}
	map->x_y.y = y;
	if (y >= map->size)
		x = 16;
	map->x_y.x = x;
}

void	delete_tetro(t_map *map, char id)
{
	int	i;
	int x;
	int y;

	i = 0;
	while (i < map->size * map->size)
	{
		y = i / map->size;
		x = i % map->size;
		if (map->content[y][x] == id || map->content[y][x] == '.')
			map->content[i / map->size][i % map->size] = 0;
		i++;
	}
}
