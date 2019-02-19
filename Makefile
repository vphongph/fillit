# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/19 01:33:36 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

blink		= 	"\033[5m"
purple_dark	= 	"\033[38;5;62m"
purple		= 	"\033[38;5;98m"
green		= 	"\033[38;5;70m"
green_dark	= 	"\033[38;5;28m"
red_dark	= 	"\033[38;5;88m"
grey		=	"\033[38;5;242m"
yellow		= 	"\033[38;5;178m"
reset		= 	"\033[0m"

EXEC		=	fillit

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

CC			=	gcc

INCLUDED	=	libft/libft.a

SRCS		=	fillit.c		\
				checking.c		\
				cutting.c

DIR_OBJS	=	object

# OBJS	=	$(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
OBJS	=	$(SRCS:.c=.o)


# HDRS = $(addprefix $(INCLUDE_DIR), fillit.h)
HDRS 	=	fillit.h

# @echo $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
RUN_ARGS = $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

.PHONY	:	all makeinclude clean fclean re run

all		: makeinclude $(EXEC)

$(EXEC)	:$(INCLUDED) $(OBJS)
		@$(CC) $(CFLAGS) libft/libft.a $(OBJS) -o $(EXEC)
		@echo $(green_dark)" Compiling" $(grey)$^ $(green)"-> $@"$(reset)

ifeq ($(DEBUG), yes)
		@echo $(yellow)" DEBUG MODE $(EXEC)"$(reset)
else
		@echo $(yellow)" NORMAL MODE $(EXEC)"$(reset)
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
		@make clean -C libft/
endif
endif
		@/bin/rm -f $(OBJS)
		@echo $(red_dark)" Removing objects from" $(grey)$(EXEC)$(reset)

fclean	:	clean
ifneq ($(firstword $(MAKECMDGOALS)), re)
		@make fclean -C libft/
endif
		@/bin/rm -f $(EXEC)
		@echo $(red_dark)" Removing binary" $(grey)$(EXEC)$(reset)

re		: fclean all

ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT	:
endif
endif

run		: all
		./$(EXEC) $(RUN_ARGS)
