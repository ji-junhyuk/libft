NAME = philosopher

OBJS = $(SRCS:.o=.c) 

SRCS = main.c

CFLAGS = -g3 #-fsanitize=thread #-Wall -Wextra -Werror -pthread -fsanitize=thread -g3

all	: .all_check

%.o : %.c
	@printf "\033[Kcompile 🦑 $(notdir $<)🔥\r"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

philo :
	@echo '★┏┓'
	@echo '┏┻┫'
	@echo '┃━┫'
	@echo '┃━┫'
	@echo '┗━┛'

.all_check :
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $^
	@make philo

debugs	:
	make DEBUG=2

debug	:
	make DEBUG=1

ifeq ($(DEBUG), 1)
    CFLAGS	+=	-g3
endif

ifeq ($(DEBUG), 2)
    CFLAGS	+=	-g3 -fsanitize=address
endif

clean	:
	@rm -rf $(OBJS)
	@rm -f .all_check

fclean	:
	@rm -f .all_check
	@rm -f $(NAME)
