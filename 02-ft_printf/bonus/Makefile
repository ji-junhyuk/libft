CC			= cc

CFLAGS		= -Wall -Wextra -Werror

HEADER 		= printf_bonus.h

SRCS 		= print_address_bonus.c print_char_bonus.c print_decimal_bonus.c	\
			  print_hex_bonus.c print_percent_bonus.c print_string_bonus.c		\
			  print_undecimal_bonus.c printf_bonus.c utils_bonus.c				\
			  check_flag_bonus.c parse_bonus.c

OBJS 		= $(SRCS:c=o) 

NAME		= libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

bonus : all

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re bonus
