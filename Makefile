NAME = libarg_parser.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

CFILES = arg_parser.c \
		arg_parser_utils.c \
		arg_parser_checks.c

OFILES = $(CFILES:.c=.o)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

all: $(NAME) clean

.c.o :
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME) debug debug.o

re: fclean $(NAME)

debug: fclean $(OFILES)
	$(CC) $(CFLAGS) -c debug.c -o debug.o
	$(CC) $(CFLAGS) $(OFILES) debug.o -o debug

.PHONY:  all clean fclean re debug