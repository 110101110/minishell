# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chchen <chchen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/23 18:16:22 by qizhang           #+#    #+#              #
#    Updated: 2025/09/16 15:52:26 by chchen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/minishell.c \
		src/exec/signals_00.c \
		src/exec/signals_01.c \
		src/exec/builtin.c\
		src/exec/check_cmd.c\
		src/exec/exec.c\
		src/exec/get_path.c\
		src/exec/process.c\
		src/parse/create_token.c\
		src/parse/quote.c \
		src/parse/token_types.c \
		src/parse/expand.c \
		src/parse/expand_utils.c\
		src/parse/remove_quote.c\
		src/parse/check_syntax.c\
		src/parse/count_tokens.c\
		src/parse/create_cmd.c\
		src/parse/heredoc_00.c\
		src/parse/heredoc_01.c\
		src/parse/init_cmd.c\
		src/parse/redirection.c\
		src/utils/free_00.c \
		src/utils/free_01.c \
		src/utils/utils_00.c \
		src/utils/utils_01.c \
		src/builtin/builtin_utils.c\
		src/builtin/cd.c\
		src/builtin/echo.c\
		src/builtin/env.c\
		src/builtin/exit.c\
		src/builtin/export.c\
		src/builtin/pwd.c\
		src/builtin/unset.c\
		src/builtin/ft_atol.c\

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -Iincludes -I$(LIBFT_DIR)

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline -lncurses

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
