NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = init_program.c  main.c  philo.c  philo_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o philo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: clean

re: fclean all