NAME = philo

SRC = main check_input create_thread routine monitor_thread return_resource syscall_thread1 syscall_thread2 utils

SRCS = $(addsuffix .c, $(SRC))

OBJS = $(SRCS:.c=.o) 

CFLAGS = -Wall -Wextra -Werror -pthread -g3

%.o : %.c
	@printf "\033[Kcompile 🦑 $<🔥\r"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all	: .all_check

philosophy :
	@echo '🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥'
	@echo '  ||||       ||||'
	@echo '  \__/       \__/'
	@echo '   ||         ||'
	@echo '   ||         ||'
	@echo '   ||         ||'
	@echo '🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥'

.all_check : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@touch $@
	@make philosophy

debug	:
	make DEBUG=1

debugs	:
	make DEBUG=2

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3 -fsanitize=thread
endif

ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address
endif

clean	:
	@rm -rf $(OBJS)
	@rm -f .all_check

fclean	:
	@make clean
	@rm -f $(NAME)

re	:
	@make fclean
	@make all

.PHONY : all bonus clean fclean re debug debugs
