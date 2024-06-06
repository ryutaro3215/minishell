NAME = minishell
SRCS = init.c signal.c env.c tokenize.c parse.c create_new_struct.c copy_struct.c get_info.c here_document.c expand.c expand_utils.c exec.c exec_utils.c redirect.c builtin.c free.c minishell.c ft_strjoin.c ft_itoa.c ft_substr.c #test_parser.c  
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = object
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
RLFLAGS = -lreadline -L $(shell brew --prefix readline)/lib
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG
endif

vpath % init signal env tokenize parse expand exec free include object libft

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
