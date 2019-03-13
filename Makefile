# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vphongph <vphongph@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/24 21:12:59 by vphongph          #+#    #+#              #
#    Updated: 2019/03/13 01:14:19 by vphongph         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

NAME			:=	fillit

CC				:=	gcc

ifeq ($(DEBUG), yes)
	CFLAGS		:=	-Wall -Wextra -Werror -g3 -fsanitize=address
else
	CFLAGS		:=	-Wall -Wextra -Werror
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

LIBS			:=	libft/libft.a	\
					libft_dupli/libft_dupli.a	\
					libft_dupli2/libft_dupli2.a

RUN_ARGS		:=	$(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

RULE_SENT		:= 	$(firstword $(MAKECMDGOALS))

.DEFAULT_GOAL	:=  all

#_________________________________VARIABLES____________________________________#

libraries		=	$(shell make -q -s -C $(1) || echo 'FORCE')

#________________________________LIBS_RULES____________________________________#

.SECONDEXPANSION:

ifneq ($(LIBS), )
ifneq ($(RULE_SENT), re)
$(LIBS)			:	$$(strip $$(call libraries,$ $$(@D)))
		@make -C $(@D)
endif
endif

#__________________________________RULES_______________________________________#


.PHONY			:	all clean fclean re relibs FORCE run


all				:	$(NAME)
ifeq ($(DEBUG), yes)
				@echo $(red)$(blink)" DEBUG"$(reset) $(yellow)"MODE $(NAME)"\
				$(grey)"don't forget debug mode for libs"$(reset)
endif

$(NAME)			:	$(LIBS) $(OBJS)
				@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)
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


$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c $(HDRS)
ifneq ($(RULE_SENT), re)
				@echo $(green)" NEW" $?
endif
				@mkdir -p $(OBJ_PATH)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo $(green_dark)"  Compiling" $(grey)$< $(green_dark)\
				"->" $(grey)"$@"$(reset)


clean			:
ifeq ($(RULE_SENT), clean)
				@$(foreach varToGen, $(LIBS), make clean -C $(dir $(varToGen));)
endif
				@/bin/rm -f $(OBJS)
				@rmdir $(OBJ_PATH) 2>/dev/null || true
				@echo $(red_dark)" Removing objects from" $(grey)$(NAME)$(reset)


fclean			:	clean
ifeq ($(RULE_SENT), fclean)
				@$(foreach varToGen, $(LIBS), make fclean -C $(dir $(varToGen));)
endif
				@/bin/rm -f $(NAME)
	 			@echo $(red_dark)" Removing binary" $(grey)$(NAME)$(reset)


re				:	relibs fclean all


relibs			:
				@$(foreach varToGen, $(LIBS), make re -C $(dir $(varToGen));)


FORCE			:


ifeq ($(RULE_SENT), run)
ifndef VERBOSE
.SILENT			:
endif
endif


run				:	all
				./$(NAME) $(RUN_ARGS)
