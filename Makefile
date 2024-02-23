NAME = philo

SRCS = philo.c utils.c argcontrols.c life_cycle.c routine.c

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "PHILO COMPAILED."

clean:
	@rm -rf $(OBJS)
	@echo "OBJS FILES CLEANED"

fclean: clean
	@rm -rf $(NAME)
	@echo "PHILO FILE CLEANED"

re: fclean all

.PHONY: all clean fclean re