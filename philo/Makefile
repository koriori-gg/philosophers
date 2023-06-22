NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

SRCS = \
	main.c \
	init.c\
	action.c \
	time.c \
	print_message.c \
	simulation.c \
	ft_pthread.c \
	bool_handlers.c \
	is_number.c \
	ft_strlen.c \
	ft_atol.c \
	ft_isdigit.c \

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
