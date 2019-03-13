/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:24:21 by vphongph          #+#    #+#             */
/*   Updated: 2019/03/13 01:28:21 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The tetriminos names are O, I, T, L, J, Z, S
** The _[number] following correspond to the clockwise degree they are flipped
** Each tetrimino has a unique id
**
** The initial position 0 is:
**
**  OO  I  TTT  L    J  ZZ    SS
**  OO  I   T   L    J   ZZ  SS
**      I       LL  JJ
**      I
**
** 0xff00000000ff = 0x0000ff00000000ff
*/

#ifndef FILLIT_H
# define FILLIT_H
# define RED			"\e[38;2;255;0;0m"
# define RESET			"\e[0m"
# define BUFF_SIZE		21 * 26 - 1
# define MASK_NL		0xff00000000ff0000
# define MASK_1STCOL	0xff00000000ff
# define OK		0
# define NOOK	1
# include "../libft/libft.h"
# include <stdlib.h>

enum	e_cardinal{
	t_west = '1',
	t_north = '2',
	t_east = '3',
	t_south = '4'
};

typedef struct	s_block{

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

int32_t			recognize_block(t_block block, int8_t i_block);
int8_t			check_block(int16_t ret, t_block *block);
int16_t			check_main_read(int ac, char **av, t_block *block);
void			cut_block(t_block *block);
int8_t			ft_sqrt(int8_t area_mini);
void			solver(int16_t nb_tetros, t_block *blocks);
void			find_next_empty(t_map *map);
int				try_tetro(t_block block, t_map map);
void			write_tetro(t_block block, t_map *map);
int32_t			recognize_tetro(t_block block, int8_t i_block);
t_x_y			find_tetro(t_map map, char id, int bef_char);
int				skip_empty(t_block block);
void			delete_tetro(t_map *map, char id);
void			print_map(t_map map);
t_x_y			find_next_mino(t_block block, t_x_y x_y);
int				can_place_mino(t_map map);
void			populate_ids(int *ids, t_block *blocks, int16_t nb_tetros);

#endif
