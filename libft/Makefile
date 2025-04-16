NAME			= libft.a

SOURCES			= $(shell find src -type f -name "*.c")

OBJECTS			= $(patsubst src/%.c, obj/%.o, $(SOURCES))

HEADERS 		= -I include

CC				= cc

FLAGS			= -Wall -Werror -Wextra

AR				= ar -rsc

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJECTS)
				@$(AR) $(NAME) $(OBJECTS)

obj/%.o:src/%.c
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

clean:
				@$(RM) $(OBJECTS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re