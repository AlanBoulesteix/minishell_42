V0_NAME := execv0
V1_NAME := execv1
V2_NAME := execv2

CC := cc

# @TODO rm -g3
FLAGS := -Wall -Wextra -MMD -g3

V0_OBJ := v0.o
V1_OBJ := v1.o
V2_OBJ := v2.o

DEPS := ${OBJ:.o=.d}

RM := rm -f

all : $(V0_NAME) $(V1_NAME) $(V2_NAME)

$(V0_NAME) : $(V0_OBJ)
	$(CC) $(V0_OBJ) -o $@

$(V1_NAME) : $(V1_OBJ)
	$(CC) $(V1_OBJ) -o $(V1_NAME)

$(V2_NAME) : $(V2_OBJ)
	$(CC) $(V2_OBJ) -o $(V2_NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(V1_NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
