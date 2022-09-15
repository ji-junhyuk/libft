CC			= cc

CFLAGS		= -Wall -Wextra -Werror

HEADER 		= push_swap.h

SRCS 		= main.c 																	\
			  free.c init.c malloc.c operator_1.c operator_2.c operator_3.c				\
			  print.c push_a_to_b.c push_b_to_a.c rank_score.c rotate.c			\
			  sort_three_stack_a_1.c sort_three_stack_a_2.c sort_three_stack_b_1.c		\
			  sort_three_stack_b_2.c sort_two_stack.c split.c							\
			  use_one_pivot_a_to_b.c use_one_pivot_b_to_a.c check_valid_input.c

BONUS		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

OBJS 		= $(SRCS:c=o) 

OBJS_BONUS	= $(BONUS:c=o)

ifdef BONUSFLAG
	ALLOBJ 	= $(OBJS) $(OBJS_BONUS)
else
	ALLOBJ 	= $(OBJS)
endif

NAME		= push_swap

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(ALLOBJ)
	$(CC) $(CFLAGS) $(ALLOBJ) -o $@ -I $(HEADER)

bonus:
	make BONUSFLAG=1

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: 
	make fclean
	make all

.PHONY: all bonus clean fclean re
