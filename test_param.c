/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 01:40:11 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/24 01:17:12 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	test_cast(char **content)
{
	printf("write cast : %zd\n",write (1, &content[0][0], 21));
	// content[0][0] = 0;
	printf("LAME\n\n");
}

void	test_no_cast(t_block block)
{
	printf("write no cast : %zd\n",write (1, block.content, 21));

	// content[0][0] = 0;
	printf("YEAH\n");
}

void	test_mappy(char **mappy)
{
	(void)mappy;
}

void	test_carte(char *carte)
{
	(void)carte;
}

void	test_map(t_map *map)
{
	(void)map;
}

int		main(void)
{
	t_block block;
	char mappy[16][16];
	char carte[16];

	t_map *map1;
	t_map map2[1];

	*(int64_t *)block.content[0] = *(int64_t *)"....\n...";
	block.content[1][3] = '.';
	block.content[1][4] = '\n';
	*(int64_t *)block.content[2] = *(int64_t *)"....\n...";
	block.content[3][3] = '.';
	block.content[3][4] = '\n';
	block.sep = '\n';

	test_cast((char **)&block.content);
	test_no_cast(block);

	test_mappy((char **)mappy);
	test_carte(carte);

	ft_bzero_v2(map1, sizeof(map1));
	ft_bzero_v2(map2, sizeof(map2));

	test_map(map1);

	test_map(map2);

	return (0);
}
