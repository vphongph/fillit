# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/18 15:02:47 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

green_dark	= 	"\033[38;5;28m"
red_dark	= 	"\033[38;5;88m"
reset_col	= 	"\033[0m"

EXEC		=	fillit
DEBUG		=	yes

# ifeq ($(DEBUG), yes)
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
# else
# CFLAGS		=	-Wall -Wextra -Werror
# endif

CC			=	gcc

INC			=	libft/libft.a

SRCS		=	fillit.c		\
				checking.c		\
				cutting.c

DIR_OBJS	=	object
# OBJS	=	$(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
OBJS	=	$(SRCS:.c=.o)



# DIR_SRCS	=
# HDRS = $(addprefix $(INCLUDE_DIR), fillit.h)
HDRS 	=	fillit.h

# @echo $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
RUN_ARGS = $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

.PHONY	:	all clean fclean re run lol

all		:	$(EXEC)

$(EXEC)	:	$(OBJS)
		@make -C libft/
		@$(CC) $(CFLAGS) $(INC) $^ -o $(EXEC)
		@echo $(green_dark) "Compiling $(INC) $^ -> $@" $(reset_col)

%.o		: %.c $(HDRS)
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo $(green_dark) "Compiling $< -> $@" $(reset_col)


clean	:
		@/bin/rm -f $(OBJS)
		@echo $(red_dark)"Removing objects" $(reset_col)

fclean	:	clean
		@make fclean -C libft/
		@/bin/rm -f $(EXEC)
		@echo $(red_dark)"Removing binary" $(reset_col)

re		:	fclean all


ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT	:
endif
endif

run		: $(EXEC)
		./$(EXEC) $(RUN_ARGS)

lol		:
	/bin/mkdir $(DIR_OBJS) 2>/dev/null || true

# @echo -e "\e[38;2;51;196;127mMODE DEBUG\e[0m"#
# else
# 		@echo "\e[38;2;51;196;127mMODE NORMAL\e[0m"
# endif