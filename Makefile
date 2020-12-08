# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/01 17:44:02 by klsirop           #+#    #+#              #
#    Updated: 2020/12/08 18:46:20 by volyvar-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = 
LDFLAGS = -L ./libft/ -lft
HEAD = ./minishell.h
LIBFT = ./libft/libft.a


SRC = 	main.c read_input.c error.c free.c do_command.c ft_strsplit_sh.c \
		help.c env.c list.c cd.c manage_path.c promt.c process.c mysplit.c \
		exit.c echo.c remove_quotes.c set_unset_env.c secret.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C ./libft/

%.o: %.c $(HEAD)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(MAKE) -C ./libft/ $@
	@/bin/rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C ./libft/ $@
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
