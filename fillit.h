/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:24:21 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/26 05:59:00 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define RED			"\e[38;2;255;0;0m"
# define RESET			"\e[0m"
# define BUFF_SIZE		21 * 26 - 1
# define MASK_NL		0xff00000000ff0000
# define MASK_1STCOL	0xff00000000ff
# define OK		0
# define NOOK	1
# include "libft/libft.h"
# include <stdlib.h>

enum	e_cardinal
{
	t_west = '1',
	t_north = '2',
	t_east = '3',
	t_south = '4'
};

typedef struct	s_block
{
	char	content[4][5];
	char	sep;
}				t_block;

typedef struct	s_x_y
{
	int	x;
	int	y;
}				t_x_y;

typedef struct	s_map
{
	int			size;
	t_x_y		x_y;
	char		content[16][16];
}				t_map;

int8_t			check_block(int16_t ret, t_block *block);
int16_t			check_main_read(int ac, char **av, t_block *block);
void			cut_block(t_block *block);
void			solve(int16_t nb_tetros, t_block *blocks);
void			find_next_empty(t_map *map);
int				try_tetro(t_block block, t_map map);
void			write_tetro(t_block block, t_map *map);
t_x_y			find_tetro(t_map map, char id, int bef_char);
int				skip_empty(t_block block);
void			delete_tetro(t_map *map, char id);
void			print_map(t_map map);
t_x_y			find_next_mino(t_block block, t_x_y x_y);
int				can_place_mino(t_map map);
void			populate_ids(int *ids, t_block *blocks, int16_t nb_tetros);

#endif
