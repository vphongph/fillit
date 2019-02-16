# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/16 22:19:18 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	=	fillit

CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address

CC		=	gcc

INC		=	libft/libft.a

SRCS	=	fillit.c		\
			checking.c		\
			cutting.c

OBJS	=	$(SRCS:.c=.o)

.PHONY	:	all, clean, fclean, re

all		:	$(EXEC)

$(EXEC)	:	$(OBJS)
		$(CC) $(CFLAGS) $(INC) -o $(EXEC) $(OBJS)
		ranlib $(EXEC)

clean	:
		/bin/rm -f $(OBJS)

fclean	:	clean
		/bin/rm -f $(NAME)

re		:	fclean all
