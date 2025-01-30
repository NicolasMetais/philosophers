SRCS = 	src/main.c \
		src/parsing.c \
		src/ft_atol.c \
		src/linked_setup/linked_setup.c \
		src/linked_setup/linked_list_fork.c \
		src/linked_setup/linked_list_philo.c \
		src/philo.c \
		src/life_cycle.c \
		src/diet.c \
		src/free.c \
		src/mutex.c \
		src/mutex_fork.c \


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -g3 #-fsanitize=address -static-libsan -pthread

NAME = philo


all: $(NAME)

#-fsanitize=address -lasan
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re