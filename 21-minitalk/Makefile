CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

S_SRC 				=	server.c print.c
C_SRC				=	client.c print.c
SERVER_SRCS			=	$(addprefix ./server_srcs/, $(S_SRC))
CLIENT_SRCS			=	$(addprefix ./client_srcs/, $(C_SRC))

S_OBJS				=	$(SERVER_SRCS:c=o)
C_OBJS 				=	$(CLIENT_SRCS:c=o) 

R_SERVER			=	server
R_CLIENT			=	client

B_S_SRC 			=	server_bonus.c print_bonus.c
B_C_SRC				=	client_bonus.c print_bonus.c
B_SERVER_SRCS		=	$(addprefix ./server_srcs_bonus/, $(B_S_SRC))
B_CLIENT_SRCS		=	$(addprefix ./client_srcs_bonus/, $(B_C_SRC))

B_S_OBJS			=	$(B_SERVER_SRCS:c=o)
B_C_OBJS 			=	$(B_CLIENT_SRCS:c=o) 

B_R_SERVER			=	server_bonus
B_R_CLIENT			=	client_bonus

all: all_check

all_check: $(R_SERVER) $(R_CLIENT)
	touch $@

$(R_SERVER): $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) -o $(R_SERVER)

$(R_CLIENT): $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(R_CLIENT)

bonus: bonus_check

bonus_check: $(B_R_SERVER) $(B_R_CLIENT)
	touch $@

$(B_R_SERVER): $(B_S_OBJS)
	$(CC) $(CFLAGS) $(B_S_OBJS) -o $(B_R_SERVER)

$(B_R_CLIENT): $(B_C_OBJS)
	$(CC) $(CFLAGS) $(B_C_OBJS) -o $(B_R_CLIENT)

clean:
	rm -rf $(S_OBJS) $(C_OBJS) $(B_S_OBJS) $(B_C_OBJS) all_check bonus_check

fclean: clean
	rm -f $(R_SERVER) $(R_CLIENT) $(B_R_SERVER) $(B_R_CLIENT)

re: 
	make fclean
	make all

.PHONY: all bonus clean fclean re 
