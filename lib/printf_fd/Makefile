# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 23:39:57 by vlepille          #+#    #+#              #
#    Updated: 2023/05/22 17:32:22 by vlepille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf_fd.a

OBJ := printf_fd.o \
	ft_fun_conv_char.o \
	ft_fun_conv_decimal.o \
	ft_fun_conv_hex.o

CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : fclean
