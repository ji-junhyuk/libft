CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

S_SRC 			=	server.c print.c
C_SRC			=	client.c print.c
SERVER_SRCS		=	$(addprefix ./server_srcs/, $(S_SRC))
CLIENT_SRCS		=	$(addprefix ./client_srcs/, $(C_SRC))

S_OBJS			=	$(SERVER_SRCS:c=o)
C_OBJS 			=	$(CLIENT_SRCS:c=o) 

R_SERVER		=	server
R_CLIENT		=	client

all: $(R_SERVER) $(R_CLIENT)

$(R_SERVER): $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) -o $(R_SERVER)

$(R_CLIENT): $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(R_CLIENT)

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
