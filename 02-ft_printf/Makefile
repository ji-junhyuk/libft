CC			= cc

CFLAGS		= -Wall -Wextra -Werror

HEADER 		= 

SRCS 		= ft_printf.c

OBJS 		= $(SRCS:c=o) 

NAME		= libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re
