# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:44:55 by sklaokli          #+#    #+#              #
#    Updated: 2025/04/19 22:34:04 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
LIBFT		:=	libft/libft.a 

SRC_DIR		:=	sources
OBJ_DIR		:=	objects
INC_DIR		:=	include

FILES		:=	\
				shell/main.c \
				shell/utils.c \
				env/env.c \
				env/token.c \
				builtins/cd.c \
				builtins/env.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/export_util.c \
				memory/free_arg.c

SRC			:=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ			:=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

INC			:=	-I $(INC_DIR) -I libft/include

CC			:=	cc
RM			:=	rm -rf
WFLAGS		:=
RL_FLAG		:=	-lreadline -lhistory -lncurses

CYAN		:=	\033[0;36m
GREEN		:=	\033[0;32m
RED			:=	\033[0;31m
BLUE		:=	\033[0;34m
YELLOW		:=	\033[0;33m
RESET		:=	\033[0m

TOTAL_FILES	:=	$(words $(OBJ))
COMPILED	:=	0

all: 			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
				@ $(CC) $(WFLAGS) $(OBJ) $(LIBFT) $(RL_FLAG) -o $(NAME)
				@ echo "$(GREEN)[OK] $(NAME) built succesfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@ mkdir -p $(dir $@)
				@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
				@ PERCENT=$$(($(COMPILED)*100/$(TOTAL_FILES))); \
				echo "$(BLUE)[$(COMPILED)/$(TOTAL_FILES)] Compiling $< ($$PERCENT%)$(RESET)\r"
				@ $(CC) $(WFLAGS) $(INC) -c $< -o $@

$(LIBFT):
				@ $(MAKE) -sC libft

clean:
				@ $(RM) $(OBJ_DIR)
				@ $(MAKE) -sC libft clean
				@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean:			clean
				@ $(RM) $(NAME)
				@ $(MAKE) -sC libft fclean
				@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re:				fclean all

.PHONY:			all clean fclean re