# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 14:52:00 by aboulest          #+#    #+#              #
#    Updated: 2023/05/27 18:54:42 by vlepille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Werror -Wextra -MMD -g3

SOURCES_DIR := src/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR) -I$(LIBRARIES_DIR)libft -I$(LIBRARIES_DIR)printf_fd

LIBRARIES := -L/usr/local/opt/readline/lib -lreadline -L$(LIBRARIES_DIR)libft -lft -L$(LIBRARIES_DIR)printf_fd -lprintf_fd

#@todo ? tree_to_tab / operation /

OBJ := main.o \
	context.o \
	utils_str.o \
	builtin_env.o \
	builtin_echo.o \
	builtin_cd.o \
	builtin_pwd.o \
	builtin_export.o \
	builtin_unset.o \
	builtin_exit.o \
	utils_vector.o \
	env_add.o \
	env_manage.o \
	builtin_export_add.o \
	utils_garbage.o \
	tree.o \
	tree_to_tab.o \
	operations.o \
	check.o \
	check_token.o \
	utils_error.o \
	execution.o \
	builtin_exec.o \
	signals.o \

OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

DEPS := ${OBJ:.o=.d}

RM := rm -f

LIBFT := lib/libft/libft.a

MAKE_LIBFT := make -C lib/libft

#############################################################################

$(NAME) : $(OBJ)
	$(MAKE_LIBFT)
	make -C lib/printf_fd
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT) :
	$(MAKE_LIBFT)

all : $(NAME)

clean :
	make clean -C lib/libft
	make clean -C lib/printf_fd
	$(RM) $(DEPS)
	$(RM) $(OBJ)

fclean : clean
	make fclean -C lib/libft
	make fclean -C lib/printf_fd
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
