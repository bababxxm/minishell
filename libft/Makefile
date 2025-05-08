# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 21:00:46 by pkhienko          #+#    #+#              #
#    Updated: 2025/05/07 23:06:52 by pkhienko42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Library name
NAME		:=	libft.a

## Paths
SRC_DIR		:=	src
OBJ_DIR		:=	obj
INC_DIR		:=	include

## Get all .c files from src/**/*
SRC_FILES	:=	$(shell find $(SRC_DIR) -type f -name "*.c")
OBJ_FILES	:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

## Compiler & Flags
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -I $(INC_DIR)
AR			:=	ar rcs
RM			:=	rm -rf

## Color Codes
CYAN		:=	\033[0;36m
GREEN		:=	\033[0;32m
RED			:=	\033[0;31m
BLUE		:=	\033[0;34m
RESET		:=	\033[0m

## Counters
COMPILED	:=	0
TOTAL		:=	$(words $(OBJ_FILES))

## Compile object files with colored progress bar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@ mkdir -p $(dir $@)
				@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
				@ PERCENT=$$(($(COMPILED)*100/$(TOTAL))); \
				echo "$(BLUE)[$(COMPILED)/$(TOTAL)] Compiling $< ($$PERCENT%)$(RESET)\r"; \
				$(CC) $(CFLAGS) -c $< -o $@

## Main Targets
all: 			$(NAME)

$(NAME): 		$(OBJ_FILES)
				@ $(AR) $(NAME) $(OBJ_FILES)
				@ echo "$(GREEN)[OK] $(NAME) built succesfully.$(RESET)"

clean:
				@ $(RM) $(OBJ_DIR)
				@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean: 		clean
				@ $(RM) $(NAME)
				@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re: 			fclean all

.PHONY: 		all clean fclean re
