# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/02/22 00:43:09 by vphongph         ###   ########.fr        #
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

CC			=	gcc

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

SRC_NAMES	=	fillit.c		\
				checking.c		\
				cutting.c

SRC_PATH	=	sources/

SRCS		=	$(addprefix $(SRC_PATH), $(SRC_NAMES))

OBJ_NAMES	=	$(SRC_NAMES:.c=.o)

OBJ_PATH	=	objects/

OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ_NAMES))

HDR_NAMES	=	$(addsuffix .h, $(NAME))

HDR_PATH	=	$(SRC_PATH)

HDRS		=	$(HDR_PATH)$(HDR_NAMES)

LIB_NAMES	=	libft.a

LIB_PATH	= 	libft/

LIBS		=	$(LIB_PATH)$(LIB_NAMES)

RUN_ARGS	=	$(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))


.PHONY			:	all makeinclude clean fclean re run


all				:	makelibs $(NAME)
ifeq ($(DEBUG), yes)
				@echo $(red)$(blink)" DEBUG"$(reset) $(yellow)"MODE $(NAME)"\
				$(grey)"don't forget debug mode for libs"$(reset)
endif


$(NAME)			:	$(LIBS) $(OBJS)
				@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
				@echo $(green_dark)" Compiling" $(grey)$^ $(green)"-> $@"$(reset)
ifneq ($(DEBUG), yes)
				@echo $(yellow)" NORMAL MODE $(NAME)"$(reset)
endif


makelibs		:
ifeq ($(firstword $(MAKECMDGOALS)), re)
				@make re -C $(LIB_PATH)
else
				@make -C $(LIB_PATH)
endif


$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c $(HDRS)
ifneq ($(firstword $(MAKECMDGOALS)), re)
				@echo $(green)" NEW" $?
endif
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo $(green_dark)"  Compiling" $(grey)$< $(green_dark)\
				"->" $(grey)"$@"$(reset)


clean			:
ifneq ($(firstword $(MAKECMDGOALS)), fclean)
ifneq ($(firstword $(MAKECMDGOALS)), re)
				@make $@ -C $(LIB_PATH)
endif
endif
				@/bin/rm -f $(OBJS)
				@echo $(red_dark)" Removing objects from" $(grey)$(NAME)$(reset)


fclean			:	clean
ifneq ($(firstword $(MAKECMDGOALS)), re)
				@make $@ -C $(LIB_PATH)
endif
				@/bin/rm -f $(NAME)
				@echo $(red_dark)" Removing binary" $(grey)$(NAME)$(reset)


re				:	fclean all


ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT			:
endif
endif


run				:	all
				./$(NAME) $(RUN_ARGS)


#Boucle dans le makefile, mais il faut un tableau, à creuser
#@	i=1 ; while [[ $$i -le 1 ]] ; do	\
#	make re -C libft/;					\
#	i+=+1;								\
#	done