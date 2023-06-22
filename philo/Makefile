NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -I inc

RM = rm -f

SRCS = \
	src/main.c \
	src/init.c\
	src/action.c \
	src/time.c \
	src/print_message.c \
	src/simulation.c \
	src/ft_pthread.c \
	src/bool_handlers.c \
	src/is_number.c \
	src/ft_strlen.c \
	src/ft_atol.c \
	src/ft_isdigit.c \

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS)  $(INCLUDE)-c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) -L. $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
