/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmemoirebzerofillit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/29 00:34:03 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#include "fillit.h"

int		main(void)
{
	// t_block tetri[1];
	t_block *tetri = (t_block *)malloc(sizeof(t_block) * 1);
	// printf("%lu\n", malloc_size(tetri));
	ft_bzero_v2(tetri, (sizeof(t_block) * 1) );
	printf("tetri sep = %p\n", &tetri->block[4][0]);
	printf("tetri sep + 1 = %p\n", tetri + 1);
	// printf("tetri + 42 = %p\n", &tetri->block[12][3]);
	// tetri->block[12][3] = 0;
	return (0);
}