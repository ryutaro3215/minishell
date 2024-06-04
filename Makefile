NAME = minishell
SRCS = signal.c env.c tokenize.c parse.c here_document.c exec.c exec_utils.c redirect.c builtin.c free.c minishell.c #test_parser.c  
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = object
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
RLFLAGS = -lreadline -L $(shell brew --prefix readline)/lib
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG
endif

vpath % signal env tokenize parse exec free include object

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: all
