CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

B_S_SRC 			=	server_bonus.c print_bonus.c
B_C_SRC				=	client_bonus.c print_bonus.c
B_SERVER_SRCS		=	$(addprefix ./server_bonus_srcs/, $(S_SRC))
B_CLIENT_SRCS		=	$(addprefix ./client_bonus_srcs/, $(C_SRC))

B_S_OBJS			=	$(B_SERVER_SRCS:c=o)
B_C_OBJS 			=	$(B_CLIENT_SRCS:c=o) 

B_R_SERVER			=	server_bonus
B_R_CLIENT			=	client_bonus

all: $(B_R_SERVER) $(B_R_CLIENT)


bonus: bonus_check

bonus_check: $(B_R_SERVER) $(B_R_CLIENT)
	touch $@

$(B_R_SERVER): $(B_S_OBJS)
	$(CC) $(CFLAGS) $(B_S_OBJS) -o $(B_R_SERVER)

$(B_R_CLIENT): $(B_C_OBJS)
	$(CC) $(CFLAGS) $(B_C_OBJS) -o $(B_R_CLIENT)

#all_check: $(OBJS)
#	touch $@
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
#
#bonus: bonus_check
#
#bonus_check: $(B_OBJS)
#	touch $@
#	$(CC) $(CFLAGS) $(B_OBJS) -o $(BONUS_NAME)

clean:
	rm -rf $(S_OBJS) $(C_OBJS)

fclean: clean
	rm -f $(R_SERVER) $(R_CLIENT)

re: 
	make fclean
	make all

.PHONY: all bonus clean fclean re 
