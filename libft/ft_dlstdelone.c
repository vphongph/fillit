/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 00:34:17 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/19 05:58:24 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ATTENTION **dlst, ça modifie le pointeur, ce n'est pas une copie
** TOUJOURS envoyer en arg un pointeur de tête
** et JAMAIS un dlst->next (pointeurs != => CONFLIT)
** 'J' = ascii 74 = DEL JOIN
** 'T' = ascii 84 = DEL TOP
** 'E' = ascii 69 = DEL END
** 'L' = ascii 76 = DEL LAST
** La fonction supprime le maillon pointé reçu en paramètre,
** relink la chaîne et place le pointeur en début de chaine
*/

static int	delete(t_dlist **tmp, void (*del)(void *, size_t), int c)
{
	if (del)
		del((*tmp)->content, (*tmp)->content_size);
	ft_memdel((void *)&(*tmp)->content);
	ft_memdel((void *)&(*tmp));
	return (c);
}

static void	relink_move2top(t_dlist **dlst, int c)
{
	if (c == 'J')
	{
		(*dlst)->prev->next = (*dlst)->next;
		(*dlst)->next->prev = (*dlst)->prev;
		while ((*dlst)->prev)
			*dlst = (*dlst)->prev;
	}
	if (c == 'T')
	{
		(*dlst)->next->prev = NULL;
		(*dlst) = (*dlst)->next;
	}
	if (c == 'E')
	{
		(*dlst)->prev->next = NULL;
		while ((*dlst)->prev)
			*dlst = (*dlst)->prev;
	}
}

int			ft_dlstdelone(t_dlist **dlst, void (*del)(void *, size_t))
{
	t_dlist *tmp;

	if (dlst && *dlst)
	{
		tmp = *dlst;
		if ((*dlst)->prev && (*dlst)->next)
		{
			relink_move2top(dlst, 'J');
			return (delete(&tmp, del, 'J'));
		}
		if ((*dlst)->next)
		{
			relink_move2top(dlst, 'T');
			return (delete(&tmp, del, 'T'));
		}
		if ((*dlst)->prev)
		{
			relink_move2top(dlst, 'E');
			return (delete(&tmp, del, 'E'));
		}
		return (delete(dlst, del, 'L'));
	}
	ft_putstr_fd_v2(RED"\adlstdelone ∅\n"RESET, 2);
	return (-1);
}
