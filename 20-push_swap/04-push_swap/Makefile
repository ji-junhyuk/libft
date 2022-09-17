CC			= cc

CFLAGS		= -Wall -Wextra -Werror

HEADER 		= ./includes/push_swap.h
B_HEADER	= 

SRC 		= main.c 																	\
			  free.c init.c malloc.c operator_1.c operator_2.c operator_3.c				\
			  print.c push_a_to_b.c push_b_to_a.c rank_score.c rotate.c					\
			  sort_three_stack_a_1.c sort_three_stack_a_2.c sort_three_stack_b_1.c		\
			  sort_three_stack_b_2.c sort_two_stack.c split.c							\
			  use_one_pivot_a_to_b.c use_one_pivot_b_to_a.c check_valid_input.c			\

SRCS		= $(addprefix ./srcs/, $(SRC))

B_SRC		= test.c
B_SRCS		= $(addprefix ./bonus_srcs/, $(B_SRC))

OBJS 		= $(SRCS:c=o) 
B_OBJS		= $(B_SRCS:c=o)

NAME		= push_swap
BONUS_NAME	= checker

all: $(NAME)

$(NAME): all_check

all_check: $(OBJS)
	touch $@
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: bonus_check

bonus_check: $(B_OBJS)
	touch $@
	$(CC) $(CFLAGS) $(B_OBJS) -o $(BONUS_NAME)

clean:
	rm -rf $(OBJS) $(BOBJS) bonus_check all_check

fclean: clean
	rm -f $(NAME)

re: 
	make fclean
	make all

.PHONY: all bonus clean fclean re 
