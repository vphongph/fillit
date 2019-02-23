/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/23 01:13:26 by vphongph         ###   ########.fr       */
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


	mem = ~(mem - diff_c) & ~mem;
	return ((mem - diff_zero) & ~mem & and_mem);
}

static int32_t	detectsharp(int32_t c)
{
	c = ~(c - 0x24242424) & ~c;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

// static int32_t	detectsharp(void)
// {
// 	int chhar1;
// 	int chhar2;
// 	int result;

// 	int chhar_origin						= 0x24242424;
// 	int zero 								= 0x00000000;

// 	chhar1 	= chhar_origin					- 0x23232323;
// 	chhar2 	= ~(chhar_origin 				- 0x22222222);


// 	printf("c1 : %#.8x\n", chhar1);
// 	printf("c2 : %#.8x\n", chhar2);

// 	chhar1 	= (chhar1 & ~chhar_origin);
// 	chhar2 	= (chhar2 & ~chhar_origin);

// 	printf("c1 : %#.8x\n", chhar1);
// 	printf("c2 : %#.8x\n", chhar2);

// 	chhar1 	= chhar1 & 0x80808080;
// 	chhar2 	= chhar2 & 0x80808080;

// 	result = chhar1 & chhar2;

// 	printf(ALLIANCE"c1 : %#.8x\n", chhar1);
// 	printf("c2 : %#.8x\n", chhar2);
// 	printf(ORDER"zero : %#.8x\n", (zero - 0x01010101) & ~zero & 0x80808080);


// 	printf(YELLOW"\n%#.8x\n"RESET, result);


// 	return (0);
// }


int		main(void)
{
	t_block tetri[1];
	// t_block *tetri = (t_block *)malloc(sizeof(t_block) * 1);
	// printf("%lu\n", malloc_size(tetri));
	ft_bzero_v2(tetri, sizeof(t_block));
	printf("result %#.8x\n",detectsharp(*(int32_t *)"..\0#"));

	return (0);
}