# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:44:55 by sklaokli          #+#    #+#              #
#    Updated: 2025/05/15 01:10:20 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
LIBFT		:=	libft/libft.a 

SRC_DIR		:=	sources
OBJ_DIR		:=	objects
INC_DIR		:=	include

FILES		:=	\
				shell/main.c \
				shell/prompt.c \
				env/env.c \
				env/utils.c \
				init/init.c \
				init/built_cmd.c \
				init/built_util.c \
				init/built_util2.c \
				lexer/tokenizer.c \
				lexer/syntax.c \
				lexer/expand.c \
				lexer/subtoken.c \
				lexer/utils.c \
				lexer/parser.c \
				lexer/check.c \
				builtins/cd.c \
				builtins/env.c \
				builtins/pwd.c \
				builtins/exit.c \
				builtins/echo.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/export_util.c \
				executor/execution.c \
				executor/execution_util.c \
				executor/execution_util2.c \
				executor/heredoc.c \
				io_file/io_file.c \
				io_file/io_util.c \
				error/error.c \
				error/exit_error.c \
				signal/signal.c \
				utils/utils.c


SRC			:=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ			:=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

INC			:=	-I $(INC_DIR) -I libft/include

CC			:=	cc
RM			:=	rm -rf
WFLAGS		:=	-Wall -Wextra -Werror
RLFLAGS		:=	-lreadline -lhistory
VFLAGS		:=	--track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all

CYAN		:=	\033[1;36m
GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
BLUE		:=	\033[1;34m
YELLOW		:=	\033[1;33m
RESET		:=	\033[0m

TOTAL_FILES	:=	$(words $(OBJ))
COMPILED	:=	0

SUPPRESS := "\
{\n\
\treadline_leak\n\
\tMemcheck:Leak\n\
\t...\n\
\tfun:readline\n\
}\n\
{\n\
\tadd_history_leak\n\
\tMemcheck:Leak\n\
\t...\n\
\tfun:add_history\n\
}\
"

all: 			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
				@ $(CC) $(WFLAGS) $(OBJ) $(LIBFT) $(RLFLAGS) -o $(NAME)
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
				@ $(RM) $(OBJ_DIR) readline.supp
				@ $(MAKE) -sC libft clean
				@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean:			clean
				@ $(RM) $(NAME) readline.supp
				@ $(MAKE) -sC libft fclean
				@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re:				fclean all

valgrind:		$(NAME)
				@ echo $(SUPPRESS) > readline.supp
				@ valgrind --suppressions=readline.supp $(VFLAGS) ./$(NAME)

.PHONY:			all clean fclean re valgrind