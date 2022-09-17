CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

HEADER 			=	includes/printf.h

SRC 			=	print_address.c print_char.c print_decimal.c						\
					print_hex.c print_percent.c print_string.c							\
					print_undecimal.c printf.c utils.c									\
					check_flag.c parse.c

SRCS			= 	$(addprefix srcs/, $(SRC))
OBJS			=	$(SRCS:c=o)

BONUS_HEADER	=	includes_bonus/printf_bonus.h

B_SRC 			=	print_address_bonus.c print_char_bonus.c print_decimal_bonus.c		\
					print_hex_bonus.c print_percent_bonus.c print_string_bonus.c		\
					print_undecimal_bonus.c printf_bonus.c utils_bonus.c				\
					check_flag_bonus.c parse_bonus.c

B_SRCS			=	$(addprefix srcs_bonus/, $(B_SRC))
B_OBJS			=	$(B_SRCS:c=o) 

NAME			=	libftprintf.a

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif


ifdef BONUS_FLAG
	ALLOBJ = $(B_OBJS)
else
	ALLOBJ = $(OBJS)
endif

all: $(NAME)

$(NAME): $(ALLOBJ)
	rm -rf $@
	ar rcs $@ $(ALLOBJ)

bonus : 
	make BONUS_FLAG=1

clean:
	rm -rf $(OBJS)
	rm -rf $(B_OBJS) 

fclean: clean
	rm -rf $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re bonus
