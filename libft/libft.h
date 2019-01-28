/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 13:26:35 by vphongph          #+#    #+#             */
/*   Updated: 2019/01/19 05:35:22 by vphongph         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define RED		"\e[38;2;255;0;0m"
# define DARKPINK	"\e[38;2;252;19;104m"
# define PINK		"\e[38;2;253;155;203m"
# define BLUE		"\e[38;2;57;154;250m"
# define GREEN		"\e[38;2;175;215;44m"
# define YELLOW		"\e[38;2;243;197;80m"
# define ALLIANCE	"\e[38;2;51;196;127m"
# define FEDERATION	"\e[38;2;65;128;219m"
# define ASSEMBLY	"\e[38;2;160;97;209m"
# define ORDER		"\e[38;2;255;105;80m"
# define RESET		"\e[0m"
# include <string.h>

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef	struct	s_dlist
{
	struct s_dlist	*prev;
	struct s_dlist	*next;
	void			*content;
	size_t			content_size;
}				t_dlist;

typedef struct	s_512speed
{
	char		ram[512];
}				t_512speed;

typedef struct	s_64speed
{
	char		ram[64];
}				t_64speed;

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memjoin(void *s1, void *s2, size_t l, size_t n);
void			*ft_memjoinfree_l(void *s1, void *s2, size_t l, size_t n);
void			*ft_memcpy_v2(void *dst, void *src, size_t n);
int				ft_strlen_v2(char *s);
int				ft_putstr_fd_v2(char *s, int fd);
void			ft_bzero_v2(void *s, size_t n);
char			*ft_strsub_v2(char *s, unsigned int start, size_t len);
t_dlist			*ft_dlstnew(void *content, size_t content_size);
int				ft_dlstdelone(t_dlist **top, void (*del)(void *, size_t));
int				ft_dlstadd(t_dlist **top, t_dlist *new);

#endif
