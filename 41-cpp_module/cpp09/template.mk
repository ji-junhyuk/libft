CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJS)

fclean :
	make clean
	rm -f $(NAME)

re:
	make clean
	make all

.PHONY: all, clean, fclean, re
