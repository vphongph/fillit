/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:56:46 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/25 20:17:59 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <unistd.h>
#include <fcntl.h>

/*
** Les fonctions CHECK fonctionnent comme le main pour la valeur de retour,
** 0 = OK
** 1 = NOOK ou error
** nl = new line
** CHECK NL -> vérifie que la col de \n existe.
*/

static int8_t	check_nl(t_block block)
{
	if ((*(int64_t *)&block.content[0][2] & MASK_NL)
		== (*(int64_t *)"xx\nxxxx\n" & MASK_NL)
		&& (*(int64_t *)&block.content[0][12] & MASK_NL)
		== (*(int64_t *)"xx\nxxxx\n" & MASK_NL))
		return (OK);
	return (NOOK);
}

/*
** CHECK CONTENT
** -> Vérifie le contenu, c-a-d l'existence de . ou #,
** -> positions cardinales des voisins, nb de #.
** (k - 4) % 5 permet de ne pas lire les positions de la col de \n
*/

static int8_t	check_content(t_block block)
{
	int8_t	neighbor;
	int8_t	nb;
	int8_t	k;

	neighbor = 0;
	nb = 0;
	k = -1;
	while (++k <= 18)
	{
		if (block.content[0][k] == '#' && ++nb)
		{
			if (k >= 1 && block.content[0][k - 1] == '#')
				neighbor++;
			if (k >= 5 && block.content[0][k - 5] == '#')
				neighbor++;
		}
		else if ((k - 4) % 5 && block.content[0][k] != '.')
			return (NOOK);
	}
	if (!check_nl(block) && (neighbor == 3 || neighbor == 4) && nb == 4)
		return (OK);
	return (NOOK);
}

/*
** CHECK BLOCK
** -> Vérifie la structure, c-a-d le nb de char, entre 21 et 545 inclus.
** -> Et la présence du séparateur \n entre deux tétriminos.
** (k - 4) % 5 permet de ne pas lire les positions de la col de \n
*/

int8_t			check_block(int16_t ret, t_block *block)
{
	int8_t i;

	i = 0;
	if (ret % 21 != 20 || ret > BUFF_SIZE)
		return (NOOK);
	while (i < ((ret / 21) + 1))
	{
		if (i < (ret / 21) && block[i].sep != '\n')
			return (NOOK);
		if (check_content(block[i]))
			return (NOOK);
		i++;
	}
	return (OK);
}

/*
** CHECK MAIN READ
** -> Vérifie nb d'arg du main, open ok ? close ok ? read ok ?
** exit failure -> sur mac -> main return (1)
*/

int16_t			check_main_read(int ac, char **av, t_block *block)
{
	int16_t ret;
	int8_t	fd;

	if (ac != 2)
	{
		ft_putstr_fd_v2("usage : ./fillit [FILE] (in the valid format)\n", 1);
		exit(EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	if ((ret = read(fd, block, BUFF_SIZE + 1)) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
