NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -MMD


SRC_PATH = src/
INC_PATH = inc/
OBJ_PATH = obj/

SRCS =	main.c		\
		parsing.c	\
		thread.c	\
		routine.c	\
		utils.c


OBJ = $(SRCS:.c=.o)


OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

DEP = $(OBJS:.o=.d)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

test : CFLAGS= -Wall -Wextra -g3 -MMD


all : $(NAME)

$(NAME) :  $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@printf "\n"
		@echo "Compiling done"

test : $(NAME)

clean :
		rm -rf $(OBJ_PATH)

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re directories

-include $(DEP)
