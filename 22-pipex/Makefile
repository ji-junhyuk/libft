CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	./srcs/
B_SRC_DIR		=	./srcs_bonus/
OBJ_DIR			=	./objs/
B_OBJ_DIR		=	./objs_bonus/

SRC				=	main.c error.c error2.c free.c init.c parse_path.c split.c string_utils.c
SRCS			=	$(addprefix ./srcs/, $(SRC))

B_SRC			=	main_bonus.c init_bonus.c parse_path_bonus.c heredoc_bonus.c error_bonus.c error2_bonus.c free_bonus.c get_next_line_bonus.c pipex_bonus.c split_bonus.c string_utils_bonus.c string_utils2_bonus.c
B_SRCS			=	$(addprefix ./srcs_bonus/, $(B_SRC))

OBJS			=	$(SRC:c=o) 
OBJ				=	$(addprefix $(OBJ_DIR),$(OBJS))
B_OBJS			=	$(B_SRC:c=o)
B_OBJ			=	$(addprefix $(B_OBJ_DIR),$(B_OBJS))

NAME			=	pipex
BONUS_NAME		=	pipex

INCLUDES		=	-I./includes

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(B_OBJ_DIR)%.o : $(B_SRC_DIR)%.c
		mkdir -p $(B_OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): all_check

all_check: $(OBJ)
	touch $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $^

bonus: bonus_check

bonus_check: $(B_OBJ)
	touch $@
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BONUS_NAME) $^

clean:
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR) bonus_check all_check

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: 
	make fclean
	make all

.PHONY: all bonus fclean clean re
