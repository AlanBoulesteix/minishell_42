# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboulest <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 14:52:00 by aboulest          #+#    #+#              #
#    Updated: 2023/05/01 13:22:04 by aboulest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Werror -Wextra -MMD -g3

SOURCES_DIR := src/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
#LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR)

LIBRARIES := -L/usr/local/opt/readline/lib -lreadline -Llibft -lft

OBJ := main.o \
	context.o \
	str_utils.o \
	garbage.o\
	tree.o\
	tree_to_tab.o\
	# init_token.o\ todo ?

OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

DEPS := ${OBJ:.o=.d}

RM := rm -f

LIBFT := libft/libft.a

MAKE_LIBFT := make -C libft

#############################################################################

$(NAME) : $(OBJ)
	$(MAKE_LIBFT)
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT) :
	$(MAKE_LIBFT)

all : $(NAME)

clean :
	make clean -C libft
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
