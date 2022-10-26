CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror 

SRC_DIR			=	./srcs/
B_SRC_DIR		=	./srcs_bonus/
OBJ_DIR			=	./objs/
B_OBJ_DIR		=	./objs_bonus/

SRC				=	main.c error.c get_next_line.c parse.c parse_utils.c split.c utils.c utils2.c draw.c rotate.c bresenham.c hook.c hook2.c
SRCS			=	$(addprefix ./srcs/, $(SRC))

B_SRC				=	main_bonus.c error_bonus.c get_next_line_bonus.c parse_bonus.c parse_utils_bonus.c split_bonus.c utils_bonus.c utils2_bonus.c draw_bonus.c rotate_bonus.c bresenham_bonus.c hook_bonus.c hook2_bonus.c
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

debugs : 
	make DEBUG=2

debug :
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3 -save-temps=obj
endif
ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address -save-temps=obj
endif

$(NAME): mlx
	make before_all_check

mlx: 
	$(MAKE) -C $(LIBMLX)

before_all_check : all_check

all_check: $(OBJ)
	cd MLX && cp libmlx.dylib ../ 
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o $(NAME)
	touch $@

bonus: mlx
	make before_bonus_check

before_bonus_check : bonus_check

bonus_check: $(B_OBJ)
	cd MLX && cp libmlx.dylib ../ 
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
