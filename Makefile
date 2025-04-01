AR			= ar rcs
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -ggdb

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			= ft_printf.c ft_printf_utils.c
OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= libftprintf.a


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(LIBFT):
	make -sC $(LIBFT_DIR)
	@cp $(LIBFT) .
	@mv libft.a $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -sC libft

re: fclean all

.PHONY: all clean fclean re
