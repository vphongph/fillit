/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minos_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtorsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 02:45:16 by mtorsell          #+#    #+#             */
/*   Updated: 2019/02/26 02:45:20 by mtorsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		can_place_mino(t_map map)
{
	if (map.x_y.y < map.size && map.x_y.x < map.size
		&& map.x_y.y >= 0 && map.x_y.x >= 0
		&& !map.content[map.x_y.y][map.x_y.x])
		return (1);
	return (0);
}

t_x_y	find_next_mino(t_block block, t_x_y x_y)
{
	if (x_y.y < 3 && block.content[x_y.y][x_y.x] == 0)
	{
		x_y.y++;
		x_y.x = 0;
	}
	while (x_y.y < 3 && block.content[x_y.y][x_y.x] == '.')
	{
		x_y.x++;
		if (x_y.y < 3 && block.content[x_y.y][x_y.x] == 0)
		{
			x_y.y++;
			x_y.x = 0;
		}
	}
	return (x_y);
}

int		skip_empty(t_block block)
{
	int i;

	i = 0;
	while (block.content[0][i] == '.')
		i++;
	return (i);
}
