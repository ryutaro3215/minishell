NAME = a.out
SRCS = tokenize.c parse.c exec.c exec_utils.c free.c minishell.c #test_parser.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG
endif

vpath % tokenize parse exec free include

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: all
