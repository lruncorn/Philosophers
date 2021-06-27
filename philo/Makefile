NAME = philo

SRC =  philo.c   pre_philo.c  utils.c check.c

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re 
