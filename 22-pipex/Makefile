CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g

SRC 		=	main.c error.c free.c init.c parse_cmd.c parse_path.c split.c string_utils.c

SRCS		=	$(addprefix ./srcs/, $(SRC))

B_SRC		=	main_bonus.c error_bonus.c free_bonus.c init_bonus.c parse_cmd_bonus.c parse_path_bonus.c split_bonus.c string_utils_bonus.c string_utils2_bonus.c get_next_line_bonus.c

B_SRCS		=	$(addprefix ./srcs_bonus/, $(B_SRC))

OBJS 		=	$(SRCS:c=o) 
B_OBJS		=	$(B_SRCS:c=o)

NAME		=	pipex
BONUS_NAME	=	pipex_bonus

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
	rm -rf $(OBJS) $(B_OBJS) bonus_check all_check

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: 
	make fclean
	make all

.PHONY: all bonus clean fclean re 
