/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 01:40:11 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/21 02:13:19 by vphongph         ###   ########.fr       */
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

int		main(void)
{
	t_block block;

	*(int64_t *)block.content[0] = *(int64_t *)"....\n...";
	block.content[1][3] = '.';
	block.content[1][4] = '\n';
	*(int64_t *)block.content[2] = *(int64_t *)"....\n...";
	block.content[3][3] = '.';
	block.content[3][4] = '\n';
	block.sep = '\n';

	test_cast((char **)&block.content);
	test_no_cast(block);

	return (0);
}
