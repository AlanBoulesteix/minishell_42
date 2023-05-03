NAME := minishell
TEST_NAME := tester

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Werror -Wextra -MMD -g3

SOURCES_DIR := src/
BINARIES_DIR := build/
INCLUDES_DIR := includes/
#LIBRARIES_DIR := lib/

INCLUDES := -I$(INCLUDES_DIR)

LIBRARIES := -L/usr/local/opt/readline/lib -lreadline

OBJ := main.o \
	context.o \
	str_utils.o \
	vector.o \
	env.o \
	add_env.o \

TEST_OBJ := tests.o \
	env.o \
	vector.o \
	str_utils.o \
	add_env.o \

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
