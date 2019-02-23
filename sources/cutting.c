/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 22:16:10 by vphongph          #+#    #+#             */
/*   Updated: 2019/02/23 21:57:50 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** DETECTSHARP
** Basé sur le détecteur de NULL de strlen,
** On met les octets # à NULL,
** On détecte les NULL.
*/

static int32_t	detectsharp(int32_t c)
{
	c = c ^ 0x23232323;
	return ((c - 0x01010101) & ~c & 0x80808080);
}

/*
** DELIMIT SET CHAR
** -> Borde la pièce de 0,
** -> Et donne à l'ordre d'arrivée des tétriminos les lettres correspondantes,
** first = A, last = Z.
** k % 5 permet de ne lire et écrire qu'en début de ligne,
** donc les 4 octets d'une ligne.
*/

static void		delimit_setchar(t_block *block)
{
	int8_t		k;
	static char c = 'A';

	k = 0;
	while (k <= 15)
	{
		if (!(k % 5) && !(detectsharp(*(int32_t *)&block->content[0][k])))
			*(int32_t *)&block->content[0][k] = 0;
		if (block->content[0][k] == '#' && block->content[0][k + 1] == '.')
			block->content[0][k + 1] = 0;
		if (block->content[0][k] == '#')
			block->content[0][k] = c;
		k++;
	}
	c++;
}

/*
** CUT BLOCK
** -> Découpe les tétriminos reçus dans un meilleur format,
** => Placés dans le coin sup gauche puis bordés de 0,
** => Et réécris dans la lettre correspondante à l'ordre de réception.
** A la fin de la première boucle de cut block, why last line = .... ?
** Si = 0, on a une ligne de 0, et pour la reco de col vide (col de .),
** ça ne marche pas.
** De plus ça ne delimite pas le block, car si le block est déjà en haut,
** on ne place pas de 0 => on doit quand même utiliser la fonction delimit
*/

void			cut_block(t_block *block)
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
	delimit_setchar(block);
}
