# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:44:55 by sklaokli          #+#    #+#              #
#    Updated: 2025/04/08 19:31:57 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Libraries
NAME		:=	minishell

## Paths to files
SRC_DIR		:=	sources
OBJ_DIR		:=	objects
INC_DIR		:=	include

## Source files
SRC			:=	$(addprefix $(SRC_DIR)/, $(FILES))
FILES		:=	sklaokli/main.c

## Include files
INC			:=	-I $(INC_DIR)

## Object files
OBJ			:=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

## Total number of files
COMPILED	:=	0
TOTAL_FILES	:=	$(words $(OBJ))

## Commands
RM			:=	rm -f
CC			:=	cc
LIBC		:=	ar rcs
WFLAG		:=	
RL_FLAG		:=	-lreadline -lhistory -lncurses

## Color Codes
CYAN		:=	\033[0;36m
GREEN		:=	\033[0;32m
RED			:=	\033[0;31m
BLUE		:=	\033[0;34m
YELLOW		:=	\033[0;33m
RESET		:=	\033[0m

## Targets
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@ mkdir -p $(dir $@)
				@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
				@ PERCENT=$$(($(COMPILED)*100/$(TOTAL_FILES))); \
				echo "$(BLUE)[$(COMPILED)/$(TOTAL_FILES)] Compiling $< ($$PERCENT%)$(RESET)\r"; \
				$(CC) $(WFLAG) -I $(INC_DIR) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) Makefile
			@ $(CC) $(RL_FLAG) $(WFLAG) $(OBJ) $(INC) -o $(NAME)
			@ echo "$(GREEN)Done! $(NAME) is now ready.$(RESET)"

clean:
			@ $(RM) -rf $(OBJ_DIR)
			@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean:
			@ $(RM) -rf $(OBJ_DIR) $(NAME)
			@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re