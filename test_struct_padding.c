/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_struct_padding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:27:54 by vphongph          #+#    #+#             */
/*   Updated: 2019/03/08 01:43:16 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_x_y1
{
	int	x;
	int	y;
}				t_x_y1;

typedef struct	s_x_y2
{
	char	x;
	char	y;
}				t_x_y2;

typedef struct	s_map1
{
	char		content[16][16];
	t_x_y1		x_y;
	int 		size;
}				t_map1;

typedef struct	s_map2
{
	t_x_y2		x_y;
	char 		size;
	char		content[16][16];

}				t_map2;

typedef struct	padding
{
	// int i;
	char c;
	int i;
	char a;
	// int i;
}				padding;



int		main(void)
{
	// printf("%ld\n", sizeof(t_x_y1));
	printf("%ld\n", sizeof(t_map1));
	printf("%ld\n", sizeof(padding));

	return (0);
}
