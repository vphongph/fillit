/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:29:13 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/05 02:58:58 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strsub_v2(char *s, unsigned int start, size_t len)
{
	char	*str;

	if (!(s && (str = (char *)malloc(len + 1))))
	{
		if (ft_putstr_fd_v2(RED"\astrsub v2 ∅ pointer | malloc ∅\n"
			RESET, 2) == -1)
			write(2, RED"\astrsub v2 -> ∅ pointer | malloc ∅ & putstr fd v2 ∅\n"
				RESET, 77);
		return (NULL);
	}
	str[len] = 0;
	s = &s[start];
	return (ft_memcpy_v2(str, s, len));
}
