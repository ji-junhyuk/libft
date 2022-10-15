CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	./srcs/
B_SRC_DIR		=	./srcs_bonus/
OBJ_DIR			=	./objs/
B_OBJ_DIR		=	./objs_bonus/

SRC				=	main.c
SRCS			=	$(addprefix ./srcs/, $(SRC))

B_SRC			=	main_bonus.c
B_SRCS			=	$(addprefix ./srcs_bonus/, $(B_SRC))

OBJS			=	$(SRC:c=o) 
OBJ				=	$(addprefix $(OBJ_DIR),$(OBJS))
B_OBJS			=	$(B_SRC:c=o)
B_OBJ			=	$(addprefix $(B_OBJ_DIR),$(B_OBJS))

LIBMLX			=	./MLX42
LIBS			=	$(LIBMLX)/libmlx42.a -ldl -lglfw -pthread -lm -L "/opt/homebrew/Cellar/glfw/3.3.8/lib/"

# $(LIBMLX)/libmlx42.a -ldl -lglfw -pthread -lm -L "/Users/junji/.brew/opt/glfw/lib/"

NAME			=	fdf
BONUS_NAME		=	fdf

INCLUDES		=	-I./includes -I./MLX42/include/MLX42

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3 -fsanitize=address
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(B_OBJ_DIR)%.o : $(B_SRC_DIR)%.c
		mkdir -p $(B_OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

debug:
	make DEBUG=1

$(NAME): 
	$(MAKE) -C $(LIBMLX)
	make all_check

all_check: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(NAME) $^
	touch $@

bonus: bonus_check

bonus_check: $(B_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $(BONUS_NAME) $^
	touch $@

clean:
	$(MAKE) -C $(LIBMLX) clean
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR) bonus_check all_check 

fclean: clean
	rm -rf fdf

re: 
	make fclean
	make all

.PHONY: all bonus fclean clean re
