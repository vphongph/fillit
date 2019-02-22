/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/22 04:52:38 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#include "sources/fillit.h"


int64_t	detectchar(int64_t mem, int8_t memsize, char c)
{

	int8_t i = 0;

	int64_t diff_c = 0;
	int64_t diff_zero = 0;
	int64_t and_mem = 0;

	if (memsize != 2 && memsize != 4 && memsize != 8)
	{
		ft_putstr_fd_v2(RED"error size detect"RESET, 1);
		return(0);
	}

	while (i++ < memsize)
	{
		 diff_c = diff_c * 256 + (c + 1);
		 diff_zero = diff_zero * 256 + 1;
		 and_mem = and_mem * 256 + 128;
	}


	printf("%#.8llx\n", diff_c);
	printf("%#.8llx\n", mem);
	printf("%#.8llx\n", diff_zero);
	printf("%#.8llx\n", and_mem);


	mem = ~(mem - diff_c) & ~mem;
	return ((mem - diff_zero) & ~mem & and_mem);
}

static int32_t	detectsharp(int32_t c)
{
	c = (c + 0xDBDBDBDB);
	printf("%#.8x\n", c);
	return (c & 0x80808080);
}


int		main(void)
{
	t_block tetri[1];
	// t_block *tetri = (t_block *)malloc(sizeof(t_block) * 1);
	// printf("%lu\n", malloc_size(tetri));
	ft_bzero_v2(tetri, sizeof(t_block));

	printf("detect char : %#.8llx\n", detectchar(0x2b000000	, 4, '*'));
	printf("detect sharp: %#.8x\n", detectsharp(0x00000000));

	return (0);
}