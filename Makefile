NAME = minishell
SRCS = init.c init_utils.c signal.c environ.c environ_utils.c eval.c parse_cmd.c tokenize.c parse.c parse_utils.c create_new_struct.c copy_struct.c get_info.c here_document.c expand.c expand_dollar.c expand_quote.c expand_wildcard.c expand_dollar_utils.c expand_quote_utils.c expand_wildcard_utils.c expand_utils.c exec.c exec_simple.c exec_connection.c exec_exit.c exec_null.c exec_utils.c redirect.c builtin_utils.c echo.c cd.c pwd.c export.c unset.c env.c exit.c free.c minishell.c ft_strjoin.c ft_itoa.c ft_substr.c #test_parser.c  
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = object
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
RLFLAGS = -lreadline -L $(shell brew --prefix readline)/lib
ifeq ($(MAKECMDGOALS), debug)
CFLAGS += -D DEBUG
endif

vpath % init signal environ eval parse expand exec builtin free include object libft

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
