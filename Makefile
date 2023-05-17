# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 14:52:00 by aboulest          #+#    #+#              #
#    Updated: 2023/05/17 15:38:58 by vlepille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
TEST_NAME := tester

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Werror -Wextra -MMD -g3

SOURCES_DIR := src/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR) -I$(LIBRARIES_DIR)libft

LIBRARIES := -L/usr/local/opt/readline/lib -lreadline -L$(LIBRARIES_DIR)libft -lft

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

TEST_OBJ := tests.o \
	env_add.o \
	env_manage.o \
	vector.o \
	str_utils.o \

OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

TEST_OBJ := $(addprefix $(BINARIES_DIR),$(TEST_OBJ))

DEPS := ${OBJ:.o=.d}

RM := rm -f

LIBFT := lib/libft/libft.a

MAKE_LIBFT := make -C lib/libft

#############################################################################

$(NAME) : $(OBJ)
	$(MAKE_LIBFT)
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(TEST_NAME) : $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LIBRARIES) -o $(TEST_NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT) :
	$(MAKE_LIBFT)

all : $(NAME)

clean :
	make clean -C lib/libft
	$(RM) $(DEPS)
	$(RM) $(OBJ)

fclean : clean
	make fclean -C lib/libft
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
