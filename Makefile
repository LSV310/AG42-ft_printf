CC = cc

CFLAGS = -Werror -Wextra -Wall

LIBFT = libft/libft.a
LIBFT_OBJ =

SRCS = ft_printf.c main.c
OBJ = $(SRCS:.c=.o)

NAME = libftprintf.a

all: $(NAME)

$(LIBFT):
	make -sC libft bonus

$(NAME): $(LIBFT) $(OBJ)
	ar rcs $(NAME) $(OBJ)

test: $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -sC libft clean
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	make -sC libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
