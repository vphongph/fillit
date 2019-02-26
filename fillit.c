/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/26 06:04:43 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int8_t	parse_block(int16_t ret, t_block *block)
{
	int8_t i;
	int8_t nb_tetros;

	i = -1;
	nb_tetros = (ret / 21) + 1;
	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	while (++i < nb_tetros)
		cut_block(&block[i]);
	return (nb_tetros);
}

int		main(int ac, char **av)
{
	t_block block[26];

	ft_bzero_v2(block, sizeof(block));
	solve(parse_block(check_main_read(ac, av, block), block), block);
	return (0);
}
