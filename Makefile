NAME = a.out
SRCS = test_parser.c tokenize.c parse.c free.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG
endif

vpath % tokenize parse free

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: all
