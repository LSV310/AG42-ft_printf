AR			= ar rcs
CC			= cc
CFLAGS		= -ggdb #-Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			=	ft_printf.c			\
				buffer.c			\
				calc_padding.c		\
				parse_flags.c		\
				write_converts.c	\
				write_flags.c
OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= libftprintf.a
TEST		= test

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@printf "                                         \r\e[1;35mft_printf archived\e[0m\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)
	@cp $(LIBFT) .
	@mv libft.a $(NAME)

$(TEST): $(NAME)
	@rm -f $(TEST)
	@$(CC) $(CFLAGS) main.c -o $@ $(NAME)
	@printf "\e[1;33mTest compiled\e[0m\n"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\e[1;35mCompiling %s\e[0m" $(notdir $<)
	@printf "                                            \r"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "\e[1;36mCleaning files\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -sC libft

bonus: $(NAME)

re: fclean all

.PHONY: all clean fclean re test bonus
