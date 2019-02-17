# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/17 02:06:24 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	=	fillit
DEBUG	=	yes

ifeq ($(DEBUG), yes)
		CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
		CFLAGS	=	-Wall -Wextra -Werror
endif

CC		=	gcc

INC		=	libft/libft.a

SRCS	=	fillit.c		\
			checking.c		\
			cutting.c

OBJS	=	$(SRCS:.c=.o)

.PHONY	:	all clean fclean re

all		:	$(EXEC)
# ifeq ($(DEBUG), yes)
# 		@echo -e "\e[38;2;51;196;127mMODE DEBUG\e[0m"
# else
# 		@echo "\e[38;2;51;196;127mMODE NORMAL\e[0m"
# endif

$(EXEC)	:	$(OBJS)
		$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(EXEC)

%.o	: %.c
	@$(CC) $(CFLAGS) $< -c -o $@

clean	:
		@/bin/rm -f $(OBJS)

fclean	:	clean
		@/bin/rm -f $(NAME)

re		:	fclean all
