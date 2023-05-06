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

OBJ := main.o \
	context.o \
	str_utils.o \
	exec.o \
	builtin_env.o \
	builtin_echo.o \
	builtin_cd.o \
	builtin_pwd.o \
	builtin_export.o \
	builtin_unset.o \
	builtin_exit.o \
	vector.o \
	env_add.o \
	env_manage.o \
	builtin_export_add.o \

TEST_OBJ := tests.o \
	env_add.o \
	env_manage.o \
	vector.o \
	str_utils.o \

OBJ := $(addprefix $(BINARIES_DIR),$(OBJ))

TEST_OBJ := $(addprefix $(BINARIES_DIR),$(TEST_OBJ))

DEPS := ${OBJ:.o=.d}

RM := rm -f

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LIBRARIES) -o $(NAME)

$(TEST_NAME) : $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LIBRARIES) -o $(TEST_NAME)

$(BINARIES_DIR) :
	mkdir $(BINARIES_DIR)

$(BINARIES_DIR)%.o : $(SOURCES_DIR)%.c | $(BINARIES_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
