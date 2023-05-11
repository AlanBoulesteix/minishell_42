NAME := exec

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Wextra -MMD -g3

OBJ := main.o \

DEPS := ${OBJ:.o=.d}

RM := rm -f

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

test : test.o
	$(CC) test.o -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
