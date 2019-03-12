# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/03/12 18:48:32 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

blink		= 	"\033[5:m"
purple_dark	= 	"\033[38;5;62m"
purple		= 	"\033[38;5;98m"
green		= 	"\033[38;5;70m"
green_dark	= 	"\033[38;5;28m"
red			= 	"\033[38;5;196m"
red_dark	= 	"\033[38;5;88m"
grey		=	"\033[38;5;242m"
yellow		= 	"\033[38;5;178m"
reset		= 	"\033[0m"

NAME		=	libft_dupli.a

CC			=	gcc

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

SRCS		=	ft_memalloc.c		\
				ft_memdel.c			\
				ft_memjoin.c		\
				ft_memjoinfree_l.c	\
				ft_memcpy_v2.c		\
				ft_strlen_v2.c		\
				ft_putstr_fd_v2.c	\
				ft_bzero_v2.c		\
				ft_strsub_v2.c		\
				ft_dlstnew.c		\
				ft_dlstdelone.c		\
				ft_dlstadd.c		\
				ft_atoi.c

OBJS		=	$(SRCS:.c=.o)

HDRS		=	libft.h


.PHONY	:	all clean fclean re


all	:	$(NAME)


$(NAME)	:	$(OBJS)
		@ar r $(NAME) $(OBJS) 2>/dev/null
		@echo $(purple_dark)" Making lib" $(purple)"-> $@"$(reset)
		@ranlib $(NAME)
		@echo $(purple_dark)" Indexing lib"$(reset)
ifeq ($(DEBUG), yes)
		@echo $(red)$(blink)" DEBUG"$(reset) $(yellow)"MODE $(NAME)"$(reset)
else
		@echo $(yellow)" NORMAL MODE $(NAME)"$(reset)
endif


%.o		:	%.c $(HDRS)
ifneq ($(firstword $(MAKECMDGOALS)), re)
		@echo $(purple)" NEW" $?
endif
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo $(purple_dark)"  compiling" $(grey)$< $(purple_dark)"->" $(grey)$@$(reset)


clean	:
		@/bin/rm -f $(OBJS)
		@echo $(red_dark)" Removing objects from" $(grey)$(NAME)$(reset)


fclean	:	clean
		@/bin/rm -f $(NAME)
		@echo $(red_dark)" Removing lib" $(grey)$(NAME)$(reset)


re		:	fclean all
