# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 21:00:46 by pkhienko          #+#    #+#              #
#    Updated: 2025/05/15 01:10:51 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Library name
NAME        := libft.a

## Paths
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include

## Source files
SRC_FILES   := \
				src/ft_is/ft_isalnum.c \
				src/ft_is/ft_isalpha.c \
				src/ft_is/ft_isascii.c \
				src/ft_is/ft_isdigit.c \
				src/ft_is/ft_isprint.c \
				src/ft_is/ft_isspace.c \
				src/ft_lst/ft_lstadd_back.c \
				src/ft_lst/ft_lstadd_front.c \
				src/ft_lst/ft_lstclear.c \
				src/ft_lst/ft_lstdelone.c \
				src/ft_lst/ft_lstiter.c \
				src/ft_lst/ft_lstlast.c \
				src/ft_lst/ft_lstmap.c \
				src/ft_lst/ft_lstnew.c \
				src/ft_lst/ft_lstsize.c \
				src/ft_mem/ft_bzero.c \
				src/ft_mem/ft_calloc.c \
				src/ft_mem/ft_memchr.c \
				src/ft_mem/ft_memcmp.c \
				src/ft_mem/ft_memcpy.c \
				src/ft_mem/ft_memmove.c \
				src/ft_mem/ft_memset.c \
				src/ft_put/ft_putchar_fd.c \
				src/ft_put/ft_putendl_fd.c \
				src/ft_put/ft_putnbr_fd.c \
				src/ft_put/ft_putstr_fd.c \
				src/ft_str/ft_split.c \
				src/ft_str/ft_strchr.c \
				src/ft_str/ft_strcmp.c \
				src/ft_str/ft_strdup.c \
				src/ft_str/ft_striteri.c \
				src/ft_str/ft_strjoin.c \
				src/ft_str/ft_strlcat.c \
				src/ft_str/ft_strlcpy.c \
				src/ft_str/ft_strlen.c \
				src/ft_str/ft_strmapi.c \
				src/ft_str/ft_strncmp.c \
				src/ft_str/ft_strnstr.c \
				src/ft_str/ft_strrchr.c \
				src/ft_str/ft_strtrim.c \
				src/ft_str/ft_substr.c \
				src/ft_to/ft_atoi.c \
				src/ft_to/ft_itoa.c \
				src/ft_to/ft_tolower.c \
				src/ft_to/ft_toupper.c \
				src/get_next_line/get_next_line.c \
				src/get_next_line/get_next_line_utils.c \
				src/printf/ft_printf.c \
				src/printf/ft_print_hex.c \
				src/printf/ft_print_ptr.c \
				src/printf/ft_print_unsigned.c \
				src/printf/ft_print_utility.c \
				src/safealloc/safealloc.c

OBJ_FILES   := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

## Compiler & Flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -I $(INC_DIR)
AR          := ar rcs
RM          := rm -rf

## Color Codes
CYAN        := \033[1;36m
GREEN       := \033[1;32m
RED         := \033[1;31m
BLUE        := \033[1;34m
RESET       := \033[0m

## Progress Counters
COMPILED    := 0
TOTAL       := $(words $(OBJ_FILES))

## Compile object files with colored progress
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@PERCENT=$$(($(COMPILED)*100/$(TOTAL))); \
	 echo "$(BLUE)[$(COMPILED)/$(TOTAL)] Compiling $< ($$PERCENT%)$(RESET)"; \
	$(CC) $(CFLAGS) -c $< -o $@

## Main Targets
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $(NAME) $(OBJ_FILES)
	@echo "$(GREEN)[OK] $(NAME) built successfully.$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)All $(NAME) archives have been removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
