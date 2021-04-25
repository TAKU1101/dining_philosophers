NAME	= philo_one

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

SRCS	= ${shell find ./srcs -type f -name "*.c"}

INCLUDE	= -I ./includes/

OBJS	= $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
