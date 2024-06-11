NAME = minishell
SRCS = init.c init_utils.c\
	signal.c\
	environ.c environ_utils.c\
	eval.c\
	parse_cmd.c tokenize.c parse.c parse_utils.c\
	create_new_struct.c copy_struct.c get_info.c here_document.c\
	expand.c expand_dollar.c expand_quote.c expand_wildcard.c\
	expand_redirect_wildcard.c expand_dollar_utils.c\
	expand_quote_utils.c expand_wildcard_utils.c expand_utils.c\
	exec.c exec_simple.c exec_connection.c exec_exit.c\
	exec_null.c exec_utils.c\
	redirect.c do_fork_pipe.c\
	builtin_utils.c echo.c cd.c pwd.c export.c unset.c\
	env.c exit.c\
	free.c error.c xmalloc.c\
	minishell.c\
	ft_strlen.c ft_isalpha.c ft_strlcat.c ft_strchr.c\
	ft_atoi.c ft_strcmp.c ft_strncmp.c ft_strdup.c\
	ft_strndup.c ft_strjoin.c ft_itoa.c ft_substr.c\
	ft_printf.c if_something1.c if_something2.c\
	ft_put_something1.c ft_put_something2.c\
	ft_err_printf.c err_if_something1.c\
	err_if_something2.c ft_err_put_something1.c\
	ft_err_put_something2.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_DIR = object
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include
RLFLAGS = -lreadline -L $(shell brew --prefix readline)/lib

vpath % init signal environ eval parse expand\
		exec builtin free error xmalloc include object libft

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


BONUS_NAME = minishell_bonus
BONUS_SRCS = init_bonus.c init_utils_bonus.c\
	signal_bonus.c\
	environ_bonus.c environ_utils_bonus.c\
	eval_bonus.c\
	parse_cmd_bonus.c tokenize_bonus.c parse_bonus.c\
	parse_utils_bonus.c create_new_struct_bonus.c\
	copy_struct_bonus.c get_info_bonus.c\
	here_document_bonus.c expand_bonus.c\
	expand_dollar_bonus.c expand_quote_bonus.c\
	expand_wildcard_bonus.c expand_redirect_wildcard_bonus.c\
	expand_dollar_utils_bonus.c\
	expand_quote_utils_bonus.c\
	expand_wildcard_utils_bonus.c\
	expand_utils_bonus.c exec_bonus.c\
	exec_simple_bonus.c exec_connection_bonus.c\
	exec_exit_bonus.c exec_null_bonus.c\
	exec_utils_bonus.c redirect_bonus.c do_fork_pipe_bonus.c\
	builtin_utils_bonus.c echo_bonus.c cd_bonus.c\
	pwd_bonus.c export_bonus.c unset_bonus.c\
	env_bonus.c exit_bonus.c\
	free_bonus.c error_bonus.c xmalloc_bonus.c\
	minishell_bonus.c\
	ft_strlen_bonus.c ft_isalpha_bonus.c\
	ft_strlcat_bonus.c ft_strchr_bonus.c\
	ft_atoi_bonus.c ft_strcmp_bonus.c\
	ft_strncmp_bonus.c ft_strdup_bonus.c\
	ft_strndup_bonus.c ft_strjoin_bonus.c\
	ft_itoa_bonus.c ft_substr_bonus.c\
	ft_printf_bonus.c if_something1_bonus.c\
	if_something2_bonus.c ft_put_something1_bonus.c\
	ft_put_something2_bonus.c ft_err_printf_bonus.c\
	err_if_something1_bonus.c err_if_something2_bonus.c\
	ft_err_put_something1_bonus.c ft_err_put_something2_bonus.c

BONUS_OBJS = $(BONUS_SRCS:%.c=$(BONUS_OBJS_DIR)/%.o)
BONUS_DIR = bonus
BONUS_OBJS_DIR = $(BONUS_DIR)/object_bonus

vpath % bonus bonus/init_bonus bonus/signal_bonus\
		bonus/environ_bonus bonus/eval_bonus\
		bonus/parse_bonus bonus/expand_bonus\
		bonus/exec_bonus bonus/builtin_bonus\
		bonus/free_bonus bonus/error_bonus\
		bonus/xmalloc_bonus bonus/include_bonus\
		bonus/object_bonus bonus/libft_bonus

$(BONUS_OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

clean_bonus:
	rm -rf $(BONUS_OBJS)

fclean_bonus: clean_bonus
	rm -rf $(BONUS_NAME)

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus
