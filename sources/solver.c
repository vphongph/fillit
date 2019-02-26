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
#include <stdio.h>
#include <unistd.h>

int8_t	ft_sqrt(int8_t area_mini)
{
	int8_t i;

	i = 2;
	while (i * i < area_mini)
		i++;
	return (i);
}

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

t_coords	find_next_mino(t_block block, t_coords coords)
{
	if (coords.y < 3 && block.content[coords.y][coords.x] == 0)
	{
		coords.y++;
		coords.x = 0;
	}
	while (coords.y < 3 && block.content[coords.y][coords.x] == '.')
	{
		coords.x++;
		if (coords.y < 3 && block.content[coords.y][coords.x] == 0)
		{
			coords.y++;
			coords.x = 0;
		}
	}
	return (coords);
}

int		can_place_mino(t_map map)
{
	if (map.coords.y < map.size && map.coords.x < map.size
			&& map.coords.y >= 0 && map.coords.x >= 0
			&& !map.content[map.coords.y][map.coords.x])
		return (1);
	return (0);
}

int		try_tetro(t_block block, t_map map)
{
	int8_t		mino_placed;
	t_coords	swap;
	t_coords	tetro_coords;

	tetro_coords.x = 0;
	tetro_coords.y = 0;
	mino_placed = 0;
	swap = tetro_coords;
	tetro_coords = find_next_mino(block, tetro_coords);
	map.coords.x = map.coords.x - (swap.x - tetro_coords.x);
	map.coords.y = map.coords.y - (swap.y - tetro_coords.y);
	while(block.content[tetro_coords.y][tetro_coords.x] && can_place_mino(map))
	{
		mino_placed++;
		if (mino_placed == 4)
			return (1);
		swap = tetro_coords;
		tetro_coords.x++;
		tetro_coords = find_next_mino(block, tetro_coords);
		map.coords.x = map.coords.x - (swap.x - tetro_coords.x);
		map.coords.y = map.coords.y - (swap.y - tetro_coords.y);
	}
	return (0);
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
	t_coords swap;
	t_coords coords;
	t_coords tetro_coords;

	tetro_coords.x = 0;
	tetro_coords.y = 0;
	swap = tetro_coords;
	coords = map->coords;
	tetro_coords = find_next_mino(block, tetro_coords);
	coords.x = coords.x - (swap.x - tetro_coords.x);
	coords.y = coords.y - (swap.y - tetro_coords.y);
	while (block.content[tetro_coords.y][tetro_coords.x])
	{
		map->content[coords.y][coords.x] = block.content[tetro_coords.y][tetro_coords.x];
		swap = tetro_coords;
		tetro_coords.x++;
		tetro_coords = find_next_mino(block, tetro_coords);
		coords.x = coords.x - (swap.x - tetro_coords.x);
		coords.y = coords.y - (swap.y - tetro_coords.y);
	}
	sanitize_map(map);
}

void	find_next_empty(t_map *map)
{
	int8_t	x;
	int8_t	y;

	x = map->coords.x + 1;
	y = map->coords.y;
	if (x >= map->size)
	{
		x = 0;
		y++;
	}
	map->coords.y = y;
	if (y >= map->size)
		x = 16;
	map->coords.x = x;
}

t_coords	find_tetro(t_map map, char id, int bef_char)
{
	t_coords coords;

	coords.x = 0 - bef_char;
	coords.y = 0;
	while (coords.y < map.size)
	{
		while (coords.x < map.size)
		{
			if (map.content[coords.y][coords.x] == id)
			{
				coords.x -= bef_char;
				return (coords);
			}
		coords.x++;
		}
		coords.x = 0;
		coords.y++;
	}
	return (coords);
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

int		points_before_char(t_block block)
{
	int i;

	i = 0;
	while (block.content[0][i] == '.')
		i++;
	return (i);
}

int		solver_iter(t_map *map, t_block *blocks, int16_t nb_tetros)
{
	int8_t tetros_placed;

	tetros_placed = 0;
	while (tetros_placed < nb_tetros)
	{
		find_next_empty(map);
		if (try_tetro(blocks[tetros_placed], *map))
		{
			write_tetro(blocks[tetros_placed++], map);
			map->coords.x = -1;
			map->coords.y = 0;
		}
		else
		{
			if (map->coords.x >= map->size && map->coords.y >= map->size)
			{
				tetros_placed--;
				if (tetros_placed < 0)
					return (0);
				if (recognize_block(blocks[tetros_placed], tetros_placed) == recognize_block(blocks[tetros_placed + 1], tetros_placed + 1))
					return (0);
				map->coords = find_tetro(*map, 'A' + tetros_placed, points_before_char(blocks[tetros_placed]));
				delete_tetro(map, 'A' + tetros_placed);
			}
		}
	}
	return (1);
}

int		is_solved(t_map *map, t_block *blocks, int16_t nb_tetros)
{
	ft_bzero_v2(map->content, 16 * 16);
	map->coords.x = -1;
	map->coords.y = 0;
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


