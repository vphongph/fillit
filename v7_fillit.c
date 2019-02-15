/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v7_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:09:39 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/15 22:15:23 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "fillit.h"

/*
** REMARQUES PERSO SUR CE PROJET
** *(int *) Déréférencer cast int ==> Lire un int (de la taille de 4 octets)
** à partir de l'adresse suivante.
** *(int *)"...." = 2e2e2e2e
** block->content[j] = &block->content[j][0]
** printf("%08x") pour 8 bits en hexa avec le 0x
** & 00, met tout à 0 donc pour ignorer
** & ff, met tous les bits de 1 à 1, char à chercher.
** __DARWIN_BYTE_ORDER = __DARWIN_LITTLE_ENDIAN ou mes tests
** (voir brouillons fillit)
**
**
** ATTENTION JE SUIS MALADE
*/

/*
** SET CHAR
** -> Donne à l'ordre d'arrivée des tétriminos les lettres correspondantes,
** first = A, last = Z.
*/

void	set_char(t_block *block)
{
	static char c = 'A';
	int8_t		i;

	i = -1;
	while (++i < 19)
		if (block->content[0][i] == '#')
			block->content[0][i] = c;
	c++;
}

/*
** RECOGNIZE BLOCK
** -> Donne un id unique aux tétriminos différents.
** __ATTENTION__ sens de lecture important pour le recognize,
** sinon conflit entre le S et L90.
** Il faut droite gauche et bas haut.
** Si gauche droite et haut bas, lire à l'envers.
*/

int		recognize_block(t_block *block)
{
	int8_t	i;
	int8_t	j;
	char	reco[9];

	i = -1;
	j = 0;
	ft_bzero_v2(reco, sizeof(reco));
	while (++i < 19)
	{
		if (block->content[0][i] == '#')
		{
			if (i < 19 && block->content[0][i + 1] == '#')
				reco[j++] = '3';
			if (i != 0 && block->content[0][i - 1] == '#')
				reco[j++] = '1';
			if (i < 14 && block->content[0][i + 5] == '#')
				reco[j++] = '4';
			if (i > 4 && block->content[0][i - 5] == '#')
				reco[j++] = '2';
		}
	}
	printf(ORDER"%s\n"RESET, reco);
	return (ft_atoi(reco));
}

/*
** DETECTSHARP
** Basé sur le détecteur de NULL de strlen,
** On met les octets # à NULL,
** On détecte les NULL.
*/

int32_t	detectsharp(int32_t c)
{
	c = ~(c - 0x24242424) & ~c;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

/*
** DELIMIT
** -> borde la pièce de 0,
** k % 5 permet de ne lire et écrire qu'en début de ligne,
** donc les 4 octets d'une ligne.
*/

void	delimit(t_block *block)
{
	int8_t k;

	k = 0;
	while (k <= 15)
	{
		if (!(k % 5) && !(detectsharp(*(int32_t *)&block->content[0][k])))
			*(int32_t *)&block->content[0][k] = *(int32_t *)"----";
			// *(int32_t *)&block->content[0][k] = 0;
		if (block->content[0][k] == '#' && block->content[0][k + 1] == '.')
			block->content[0][k + 1] = '*';
		k++;
	}
}

/*
** CUT BLOCK
** -> Découpe les tétriminos reçus dans un meilleur format,
** -> Placés dans le coin sup gauche puis bordés de 0.
** A la fin de la première boucle de cut block, why last line = .... ?
** Si = 0, on a une ligne de 0, et pour la reco de col vide (col de .),
** ça ne marche pas.
** De plus ça ne delimite pas le block, car si le block est déjà en haut,
** on ne place pas de 0 => on doit quand même utiliser la fonction delimit
*/

void	cut_block(t_block *block)
{
	while (*(int32_t *)block->content[0] == *(int32_t *)"....")
	{
		*(int32_t *)block->content[0] = *(int32_t *)block->content[1];
		*(int32_t *)block->content[1] = *(int32_t *)block->content[2];
		*(int32_t *)block->content[2] = *(int32_t *)block->content[3];
		*(int32_t *)block->content[3] = *(int32_t *)"....";
	}
	while ((*(int64_t *)block->content[0] & MASK_1STCOL)
		== (*(int64_t *)".xxxx.xx" & MASK_1STCOL)
			&& (*(int64_t *)block->content[2] & MASK_1STCOL)
				== (*(int64_t *)".xxxx.xx" & MASK_1STCOL))
	{
		*(int32_t *)block->content[0] = *(int32_t *)block->content[0] >> 8;
		*(int32_t *)block->content[1] = *(int32_t *)block->content[1] >> 8;
		*(int32_t *)block->content[2] = *(int32_t *)block->content[2] >> 8;
		*(int32_t *)block->content[3] = *(int32_t *)block->content[3] >> 8;
	}
	delimit(block);
}

/*
** Les fonctions CHECK fonctionnent comme le main pour la valeur de retour,
** 0 = OK
** 1 = NOOK ou error
** nl = new line
** CHECK NL -> vérifie que la col de \n existe.
*/

int8_t	check_nl(t_block block)
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

int8_t	check_content(t_block block)
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
			if (k > 0 && block.content[0][k - 1] == '#')
				neighbor++;
			if (k > 4 && block.content[0][k - 5] == '#')
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

int8_t	check_block(int16_t ret, t_block *block)
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

int32_t	*parse_block(int16_t ret, t_block *block, int32_t *order)
{
	int8_t i;

	i = 0;

	write(1,block[0].content[0],ret);

	if (check_block(ret, block))
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}

	while (i < ((ret / 21) + 1))
	{
		cut_block(&block[i]);
		order[i] = recognize_block(&block[i]);
		set_char(&block[i]);
		i++;
	}

/*
** Après parsing des tétri, on place l'id (suite à la reco) dans un tableau d'int.
** On trie par ordre croissant
** Check que id est unique, sinon LAME !
*/

	ft_putstr_fd_v2(YELLOW"AFTER CUT\n"RESET, 1);
	write(1, "\n", 1);
	write(1,block[0].content[0],ret);

	printf(PINK"nb block = %d\n\n"RESET, ret / 21 + 1);

	i = 0;
	int tmp = 0;
	while (order[i])
	{
		if (i > 0 && order[i] < order[i - 1])
		{
			tmp = order[i];
			order[i] = order[i - 1];
			order[i - 1] = tmp;
			i--;
		}
		else
			i++;
	}
	i = -1;
	while (order[++i])
		printf(ALLIANCE"%d\n"RESET, order[i]);
	printf("\n");

	i = -1;
	int 	j = -1;
	while (order[++j])
	{
		while (order[++i])
		{
			if (j != i && order[j] == order[i])
			{
				printf(YELLOW"LAME!\n"RESET);
				return (NULL);
			}
		}
		i = -1;
	}
	return (order);
}

/*
** CHECK MAIN READ
** -> Vérifie nb d'arg du main, open ok ? close ok ? read ok ?
** exit failure -> sur mac -> main return (1)
*/

int16_t	check_main_read(int ac, char **av, t_block *block)
{
	int16_t ret;

	// ret = 0;
	if (ac != 2)
	{
		ft_putstr_fd_v2("usage : ./fillit [FILE] (in the valid format)\n", 1);
		exit(EXIT_FAILURE);
	}
	if (open(av[1], O_RDONLY) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	if ((ret = read(3, block, BUFF_SIZE + 1)) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	if (close(3) == -1)
	{
		ft_putstr_fd_v2("error\n", 1);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int		main(int ac, char **av)
{
	t_block block[26];
	int32_t	order[27];

	ft_bzero_v2(block, sizeof(block));
	ft_bzero_v2(order, sizeof(order));
	parse_block(check_main_read(ac, av, block), block, order);
	return (0);
}
