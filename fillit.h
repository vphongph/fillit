/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:24:21 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/20 18:25:10 by vphongph         ###   ########.fr       */
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
# include "libft/libft.h"
# include <stdlib.h>

enum e_bool
{
	t_true = 1,
	t_false = 0
};

enum e_cardinal{
	t_west = '1',
	t_north = '2',
	t_east = '3',
	t_south = '4'
};

typedef struct	s_block{

	char	content[4][5];
	char	sep;
}				t_block;

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;

typedef struct	s_map
{
	char		content[16][16];
	int8_t		size;
	t_coords	coords;
}				t_map;

int8_t			check_block(int16_t ret, t_block *block);
int16_t			check_main_read(int ac, char **av, t_block *block);
void			cut_block(t_block *block);
int				ft_sqrt(int nb);
void			solver(int16_t nb_tetros, t_block *blocks);

#endif
