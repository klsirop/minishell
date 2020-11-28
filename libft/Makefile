# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/29 17:00:58 by jmaynard          #+#    #+#              #
#    Updated: 2019/09/06 10:47:04 by jmaynard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
INC = ./includes
SRC_MEM =	ft_bzero.c ft_memcmp.c ft_memcpy.c \
			ft_memchr.c ft_memccpy.c ft_memmove.c \
			ft_memset.c ft_memalloc.c ft_memdel.c \

SRC_LST =	ft_lstnew.c ft_lstdelone.c \
			ft_lstdel.c ft_lstadd.c ft_lstiter.c \
			ft_lstmap.c ft_lstn.c ft_lst_pushback.c \
			ft_lstlen.c ft_lst_merge.c \
			
SRC_GNL =		get_next_line.c 

SRC_STR =	ft_strlen.c ft_strdup.c ft_strcpy.c \
			ft_strncpy.c ft_strcat.c ft_strncat.c \
			ft_strlcat.c ft_strchr.c ft_strrchr.c \
			ft_strstr.c ft_strnstr.c ft_strcmp.c \
			ft_strncmp.c ft_atoi.c ft_isalpha.c \
			ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_toupper.c ft_tolower.c \
			ft_strnew.c ft_strdel.c ft_strclr.c \
			ft_striter.c ft_striteri.c ft_strmap.c \
			ft_strmapi.c ft_strequ.c ft_strnequ.c \
			ft_strsub.c ft_strjoin.c ft_strtrim.c \
			ft_itoa.c ft_putchar.c \
			ft_putstr.c ft_putnbr.c ft_putendl.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
			ft_putendl_fd.c ft_strsplit.c ft_isspace.c ft_atoi_large.c

SRC_PRTF =	c_conservation.c di_cons.c do_consver.c \
			ft_itoa_base.c ft_printf.c ft_read_arg.c \
			o_conservation.c s_conservation.c p_conservation.c \
			x_conservation.c x_up_conservation.c di_func.c \
			ft_size.c ft_size_u.c u_cons.c ft_size_1.c \
			ft_size_2.c ft_size_3.c ft_size_u_1.c ft_size_u_2.c \
			ft_size_u_3.c di_func_1.c di_func_3.c di_cons_2.c float.c \
			bnt.c multik.c f_cons.c f_wid.c f_cons_str.c di_ost.c \
			f_ost.c f_cons_str_h.c float_h.c ft_float_hh.c \
			float_hhh.c multik_h.c sl_conservation.c cl_cons.c \
			nan.c last_func.c ft_last_func_2.c do_len.c do_flags.c \
			do_wid.c do_type.c

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

LST = $(addprefix lst/,$(SRC_LST))
MEM = $(addprefix mem/,$(SRC_MEM))
STR = $(addprefix str/,$(SRC_STR))
GNL = $(addprefix gnl/,$(SRC_GNL))
PRTF = $(addprefix ft_printf/,$(SRC_PRTF))

OBJ_LST:= $(LST:.c=.o)
OBJ_STR:= $(STR:.c=.o)
OBJ_MEM:= $(MEM:.c=.o)
OBJ_GNL:= $(GNL:.c=.o)
OBJ_PRTF:= $(PRTF:.c=.o)

O_LST:= $(SRC_LST:.c=.o)
O_STR:= $(SRC_STR:.c=.o)
O_MEM:= $(SRC_MEM:.c=.o)
O_GNL:= $(SRC_GNL:.c=.o)
O_PRTF:= $(SRC_PRTF:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INC) -c $<

$(NAME): $(OBJ_LST) $(OBJ_MEM) $(OBJ_STR) $(OBJ_GNL) $(OBJ_PRTF)
	@ar -rcs $(NAME) $(O_LST) $(O_MEM) $(O_STR) $(O_GNL) $(O_PRTF)
	@ranlib $(NAME)

clean:
	@rm -f $(O_LST) $(O_MEM) $(O_STR) $(O_GNL) $(O_PRTF)

fclean: clean
	@rm -f $(NAME)

re: fclean all
