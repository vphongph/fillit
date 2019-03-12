/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:30:21 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/17 14:10:34 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** La fonction DOIT reçevoir le top en paramètre
** return 'A' = ajouter un nouveau, le top est existant, ADDITION
** return 'C' = ajouter le premier, le top est inexistant, CREATION
*/

int		ft_dlstadd(t_dlist **top, t_dlist *new)
{
	if (top && *top && new)
	{
		new->next = *top;
		(*top)->prev = new;
		*top = new;
		return ('A');
	}
	if (top && new)
	{
		new->next = *top;
		*top = new;
		return ('C');
	}
	ft_putstr_fd_v2(RED"\adlstadd ∅\n"RESET, 2);
	return (-1);
}
