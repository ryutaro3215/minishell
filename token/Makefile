NAME = token
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCDIR = .
SRCS = $(shell find $(SRCDIR) -name "*.c" -type f | xargs)
OBJS = $(SRCS:.c=.o)
LIBDIR = .
LIBNAME = readline
INCLUDE = -I ./includes
LIBRARY = -L $(LIBDIR) -l $(LIBNAME)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIBRARY) $(OBJS) -o $(NAME)
	@echo "Done."

%.o: %.c
	@echo "Compiling Object $@..."
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "Do make clean..."
	@rm -f $(OBJS)

fclean: clean
	@echo "Do make fclean..."
	@rm -f $ $(NAME)

re: fclean all

.PHONY: all clean fclean re
