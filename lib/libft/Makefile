# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboulest <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 17:06:08 by aboulest          #+#    #+#              #
#    Updated: 2022/11/21 15:37:42 by aboulest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c

MY_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c 

MY_OBJECTS = $(MY_SRC:.c=.o)

MY_OBJECTS_BONUS = $(MY_BONUS:.c=.o)

CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(MY_OBJECTS) $(MY_OBJECTS_BONUS)
	ar -crs $(NAME) $(MY_OBJECTS) $(MY_OBJECTS_BONUS)

clean:
	$(RM) $(MY_OBJECTS) $(MY_OBJECTS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : fclean
