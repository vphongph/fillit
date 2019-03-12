# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/03/12 19:10:20 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DEPRECATED
# MAKEFILE ARCHIVE, WITH OLD AND NEW (CURRENT) RULES
# Last edit 12/03/2019

#___________________________________COLORS_____________________________________#

blink		:= 	"\033[5:m"
blue		:= 	"\033[38;5;26m"
purple_dark	:= 	"\033[38;5;62m"
purple		:= 	"\033[38;5;98m"
green		:= 	"\033[38;5;70m"
green_coa	:= 	"\033[38;5;47m"
green_dark	:= 	"\033[38;5;28m"
red			:= 	"\033[38;5;196m"
red_dark	:= 	"\033[38;5;88m"
grey		:=	"\033[38;5;242m"
yellow		:= 	"\033[38;5;178m"
reset		:= 	"\033[0m"

#__________________________________CONSTANTS___________________________________#

NAME		:=	fillit

CC			:=	gcc

ifeq ($(DEBUG), yes)
	CFLAGS	:=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS	:=	-Wall -Wextra -Werror
endif

SRC_NAMES		:=	fillit.c		\
					checking.c		\
					cutting.c		\
					solver.c		\
					minos_ops.c		\
					tetros_ops.c	\
					map_ops.c

SRC_PATH		:=	sources/

SRCS			:=	$(addprefix $(SRC_PATH), $(SRC_NAMES))

OBJ_NAMES		:=	$(SRC_NAMES:.c=.o)

OBJ_PATH		:=	objects/

OBJS			:=	$(addprefix $(OBJ_PATH), $(OBJ_NAMES))

HDR_NAMES		:=	$(addsuffix .h, $(NAME))

HDR_PATH		:=	$(SRC_PATH)

HDRS			:=	$(HDR_PATH)$(HDR_NAMES)

LIB_NAMES		:=	libft.a

LIB_PATH		:= 	libft/

CLIB 			:= libft/libft.a libft_dupli/libft_dupli.a

LIBS			:=	$(LIB_PATH)$(LIB_NAMES)

RUN_ARGS		:=	$(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

.DEFAULT_GOAL	:=  all

#__________________________________VARIABLES___________________________________#

ifeq ($(firstword $(MAKECMDGOALS)), )
libraries		=	$(shell make -q -s -C $(1) || echo 'FORCE')
else
libraries		=	$(shell echo 'FORCE')
endif

#____________________________________RULES_____________________________________#

.SECONDEXPANSION:

ifneq ($(CLIB), )
$(CLIB)			:	$$(strip $$(call libraries,$ $$(@D)))
ifeq ($(firstword $(MAKECMDGOALS)), re)
		@make re -C $(@D)
else
ifeq ($(firstword $(MAKECMDGOALS)), clean)
		@make clean -C $(@D)
else
ifeq ($(firstword $(MAKECMDGOALS)), fclean)
		@make fclean -C $(@D)
else
		@make -C $(@D)
endif
endif
endif
endif


.PHONY			:	all clean fclean re relibs run


all				:	$(NAME)
ifeq ($(DEBUG), yes)
				@echo $(red)$(blink)" DEBUG"$(reset) $(yellow)"MODE $(NAME)"\
				$(grey)"don't forget debug mode for libs"$(reset)
endif



#makeinclude		:
#ifeq ($(firstword $(MAKECMDGOALS)), re)
#				@make re -C $(LIB_PATH)
#else
#				@make -C $(LIB_PATH)
#endif


$(NAME)			:	$(CLIB) $(OBJS)
#ifeq ($(firstword $(MAKECMDGOALS)), re)
#				@make re -C $(LIB_PATH)
# endif
				@$(CC) $(CFLAGS) $(CLIB) $(OBJS) -o $(NAME)
				@echo $(green_dark)" Compiling" $(grey)"libs and objects" $(green)"-> $@"$(reset)
ifneq ($(DEBUG), yes)
				@echo $(yellow)" NORMAL MODE $(NAME)"$(reset)
endif
				@printf $(blue)"\
				      ____________ \n\
				     /\  ________ \ \n\
				    /  \ \______/\ \ "$(yellow)"FILLIT"$(blue)"\n\
				   / /\ \ \  / /\ \ \ "$(green_coa)"vphongph"$(blue)"\n\
				  / / /\ \ \/ / /\ \ \ "$(purple)"mtorsell"$(blue)"\n\
				 / / /__\ \ \/_/__\_\ \__________ \n\
				/ /_/____\ \__________  ________ \ \n\
				\ \ \____/ / ________/\ \______/\ \ \n\
				 \ \ \  / / /"$(red_dark)$(blink)"\ \  / /"$(reset)$(blue)"\ \ \  / /\ \ \ \n\
				  \ \ \/ / /"$(red_dark)$(blink)"\ \ \/ / /"$(reset)$(blue)"\ \ \/ / /\ \ \ \n\
				   \ \/ / /"$(red_dark)$(blink)"__\_\/ / /__"$(reset)$(blue)"\ \ \/_/__\_\ \ \n\
				    \  /_/"$(red_dark)$(blink)"______\/_/____"$(reset)$(blue)"\ \___________\ \n\
				    /  \ " 2>/dev/null || true
				@printf "\\" 2>/dev/null || true
				@printf $(red_dark)$(blink)"______/\ \____"$(reset)$(blue)"/ / ________  / \n\
				   / /\ \ " 2>/dev/null || true
				@printf "\\" 2>/dev/null || true
				   	@printf $(red_dark)$(blink)"  / /\ \ \  "$(reset)$(blue)"/ / /\ \  / / / \n\
				  / / /\ \ " 2>/dev/null || true
				@printf "\\" 2>/dev/null || true
				@printf $(red_dark)$(blink)"/ / /\ \ " 2>/dev/null || true
				@printf "\\" 2>/dev/null || true
				@printf $(reset)$(blue)"/ / /\ \ \/ / / \n\
				 / / /__\ \ " 2>/dev/null || true
				@printf "\\" 2>/dev/null || true
				@printf $(red_dark)$(blink)"/"$(reset)$(blue)"_"$(red_dark)$(blink)"/"$(reset)$(blue)"__" 2>/dev/null || true
				@printf $(red_dark)$(blink)"\\" 2>/dev/null || true
				@printf $(reset)$(blue)"_" 2>/dev/null || true
				@printf $(red_dark)$(blink)"\\" 2>/dev/null || true
				@printf $(reset)$(blue)"/ / /__\_\/ / / \n\
				/ /_/____\ \_________\/ /______\/ / \n\
				\ \ \____/ / ________  __________/ \n\
				 \ \ \  / / /\ \  / / / \n\
				  \ \ \/ / /\ \ \/ / / \n\
				   \ \/ / /__\_\/ / / \n\
				    \  / /______\/ / \n\
				     \/___________/ \n"$(reset) 2>/dev/null || true


$(OBJ_PATH)%.o	: $(SRC_PATH)%.c $(HDRS)
ifneq ($(firstword $(MAKECMDGOALS)), re)
				@echo $(green)" NEW" $?
endif
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo $(green_dark)"  Compiling" $(grey)$< $(green_dark)\
				"->" $(grey)"$@"$(reset)


clean			: $(CLIB)
ifneq ($(firstword $(MAKECMDGOALS)), fclean)
ifneq ($(firstword $(MAKECMDGOALS)), re)
				@make $@ -C $(LIB_PATH)
endif
endif
				@/bin/rm -f $(OBJS)
				@rmdir $(OBJ_PATH) 2>/dev/null || true
				@echo $(red_dark)" Removing objects from" $(grey)$(NAME)$(reset)


fclean			:	$(CLIB) clean
				@/bin/rm -f $(NAME)
	 			@echo $(red_dark)" Removing binary" $(grey)$(NAME)$(reset)


# re				:	fclean relibs all

re				:	fclean all

# relibs			:
#				@make re -C $(LIB_PATH)

FORCE			:

ifeq ($(firstword $(MAKECMDGOALS)), run)
ifndef VERBOSE
.SILENT			:
endif
endif


run				:	all
				./$(NAME) $(RUN_ARGS)


# A creuser avec la boucle ci dessous + foreach
#define CLEAN_LIB__TEMPLATE
#	@make -C $(1) $@
#endef

#Boucle dans le makefile, mais il faut un tableau, à creuser
#@	i=1 ; while [[ $$i -le 1 ]] ; do	\
#	make re -C libft/;					\
#	i+=+1;								\
#	done
