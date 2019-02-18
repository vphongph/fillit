# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/18 22:01:29 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

blink		= 	"\033[5m"
purple_dark	= 	"\033[38;5;62m"
green_dark	= 	"\033[38;5;28m"
red_dark	= 	"\033[38;5;88m"
grey		=	"\033[38;5;242m"
yellow		= 	"\033[38;5;178m"
reset		= 	"\033[0m"

EXEC		=	fillit

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
	BUG 	=	1
else
	CFLAGS	=	-Wall -Wextra -Werror
	BUG 	=	0
endif

CC			=	gcc

# DIR_INC

INCLUDED	=	libft/libft.a

INCLUDEDLIB =	libft/

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

.PHONY	:	all clean fclean re run

all		: lolilol $(EXEC)
ifneq ($(firstword $(MAKECMDGOALS)), run)
	@echo "make $(EXEC) over"
endif


$(EXEC)	: $(OBJS) $(INCLUDEDLIB)
		@$(CC) $(CFLAGS) libft/libft.a $(OBJS) -o $(EXEC)
		@echo $(green_dark)" Compiling  $^ -> $@"$(reset)

ifeq ($(DEBUG), yes)
		@echo $(yellow)" DEBUG MODE $(EXEC)"$(reset)
else
		@echo $(yellow)" NORMAL MODE $(EXEC)"$(reset)
endif


lolilol :
		@make -C libft/

%.o		: %.c $(HDRS)
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo $(green_dark)" Compiling $< -> $@"$(reset)

clean	:
		@make clean -C libft/
		@/bin/rm -f $(OBJS)
		@echo $(red_dark)" Removing objects from" $(grey)$(EXEC)$(reset)

fclean	:	clean
		@make fclean -C libft/
		@/bin/rm -f $(EXEC)
		@echo $(red_dark)" Removing binary" $(grey)$(EXEC)$(reset)

re		:	fclean all


ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT	:
endif
endif

run		: all
		./$(EXEC) $(RUN_ARGS)

lol		:
	/bin/mkdir $(DIR_OBJS) 2>/dev/null || true


