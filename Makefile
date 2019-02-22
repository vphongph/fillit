# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/20 22:20:37 by vphongph         ###   ########.fr        #
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

NAME		=	fillit

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

CC			=	gcc

INCLUDED	=	libft.a

SRCS		=	fillit.c		\
				checking.c		\
				cutting.c		\
				ft_sqrt.c		\
				solver.c

DIR_OBJS	=	object

# OBJS	=	$(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
OBJS	=	$(SRCS:.c=.o)


# HDRS = $(addprefix $(INCLUDE_DIR), fillit.h)
HDRS 	=	fillit.h

# @echo $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
RUN_ARGS = $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

.PHONY	:	all makeinclude clean fclean re run

all		: makeinclude $(NAME)
ifeq ($(DEBUG), yes)
		@echo $(red)$(blink)" DEBUG"$(reset) $(yellow)"MODE $(NAME)"\
		$(grey)"don't forget debug mode for libs"$(reset)
endif

$(NAME)	: libft/libft.a $(OBJS)
		@$(CC) $(CFLAGS) libft/libft.a $(OBJS) -o $(NAME)
		@echo $(green_dark)" Compiling" $(grey)$^ $(green)"-> $@"$(reset)
ifeq ($(DEBUG), yes)
		@
else
		@echo $(yellow)" NORMAL MODE $(NAME)"$(reset)
endif


makeinclude :
ifeq ($(firstword $(MAKECMDGOALS)), re)
		@make re -C libft/
else
		@make -C libft/
endif

%.o		: %.c $(HDRS)
ifneq ($(firstword $(MAKECMDGOALS)), re)
		@echo $(green)" NEW" $?
endif
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo $(green_dark)"  Compiling" $(grey)$< $(green_dark)"->" $(grey)"$@"$(reset)

clean	:
ifneq ($(firstword $(MAKECMDGOALS)), fclean)
ifneq ($(firstword $(MAKECMDGOALS)), re)
		@make $@ -C libft/
endif
endif
		@/bin/rm -f $(OBJS)
		@echo $(red_dark)" Removing objects from" $(grey)$(NAME)$(reset)

fclean	:	clean
ifneq ($(firstword $(MAKECMDGOALS)), re)
		@make $@ -C libft/
endif
		@/bin/rm -f $(NAME)
		@echo $(red_dark)" Removing binary" $(grey)$(NAME)$(reset)

re		: fclean all

ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT	:
endif
endif

run		: all
		./$(NAME) $(RUN_ARGS)
