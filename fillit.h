/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:24:21 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/24 23:28:08 by vphongph         ###   ########.fr       */
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
*/

#ifndef FILLIT_H
# define FILLIT_H
# define RED		"\e[38;2;255;0;0m"
# define RESET		"\e[0m"
# define BUFF_SIZE	21
# define O_0	10
# define I_0	20
# define I_90	21
# define T_0	30
# define T_90	31
# define T_180	32
# define T_270	33
# define L_0 	40
# define L_90	41
# define L_180	42
# define L_270	43
# define J_0 	50
# define J_90 	51
# define J_180	52
# define J_270	53
# define Z_0	60
# define Z_90	61
# define S_0	70
# define S_90	71
# include "libft/libft.h"

typedef struct	s_tetridata{

	int		type;
	int		number;
	int		*order;
}				t_tetridata;

#endif
