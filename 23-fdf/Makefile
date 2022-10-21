CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	./srcs/
B_SRC_DIR		=	./srcs_bonus/
OBJ_DIR			=	./objs/
B_OBJ_DIR		=	./objs_bonus/

SRC				=	main.c split.c get_next_line.c get_next_line_utils.c error.c
SRCS			=	$(addprefix ./srcs/, $(SRC))

B_SRC			=	main_bonus.c
B_SRCS			=	$(addprefix ./srcs_bonus/, $(B_SRC))

OBJS			=	$(SRC:c=o) 
OBJ				=	$(addprefix $(OBJ_DIR),$(OBJS))
B_OBJS			=	$(B_SRC:c=o)
B_OBJ			=	$(addprefix $(B_OBJ_DIR),$(B_OBJS))

LIBMLX			=	./MLX
LIBS			=	-L./MLX -lmlx -framework OpenGL -framework AppKit

NAME			=	fdf
BONUS_NAME		=	fdf

INCLUDES		=	-I./includes -I./MLX/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(B_OBJ_DIR)%.o : $(B_SRC_DIR)%.c
		mkdir -p $(B_OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

debug : 
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	=	-Wall -Wextra -Werror -g3 # -fsanitize=address -save-temps=obj
endif

# $(NAME): mlx
$(NAME) : all_check
#	make before_all_check

mlx: 
	$(MAKE) -C $(LIBMLX)

before_all_check : all_check

all_check: $(OBJ)
#	cd MLX && cp libmlx.dylib ../ 
#	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(NAME) $^
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $^
	touch $@

bonus: bonus_check

bonus_check: $(B_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(BONUS_NAME) $^
	touch $@

clean:
	$(MAKE) -C $(LIBMLX) clean
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR) bonus_check all_check libmlx.dylib

fclean: clean
	rm -rf fdf

re: 
	make fclean
	make all

.PHONY: all bonus fclean clean re mlx
