/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/23 21:48:58 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>


#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

#define DETECTCHAR(x,c) (DETECTNULL((x) ^ ((c)*0x01010101l) ))

#include "sources/fillit.h"

/*
** _ATTENTION_ recherche 00, si 01 puis 00 (0x0100)
**			OU recherche c,	 si c-1 puis c (0x2223 pour c = '#')
** 			=> Les deux octects sont ON
** _ATTENTION_ si memsize > mem recherchée => fonction FAIL
** _ATTENTION_ endian
*/

int64_t	detectchar(int64_t mem, int8_t memsize, char c)
{
	int64_t distribution;
	int64_t eighty;

	distribution = 1;
	eighty = 0x80;
	if (!(memsize <= 8 && memsize >= 1))
	{
		ft_putstr_fd_v2(RED BLINK"error detectchar\n"RESET, 2);
		return (0);
	}
	while (--memsize)
	{
		distribution = (distribution << 8) + 0x1;
		eighty = (eighty << 8) + 0x80;
	}
	mem = mem ^ (c * distribution);
	return ((mem - distribution) & ~mem & eighty);
}

int		main(void)
{
	t_block tetri[1];
	ft_bzero_v2(tetri, sizeof(t_block));

	printf(YELLOW"%#.16llx\n"RESET,detectchar(*(int64_t *)"...i....", 8, 'i'));
										//    0xZZZZZZZZZZZZZZZZ
	return (0);
}