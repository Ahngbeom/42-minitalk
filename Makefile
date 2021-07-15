NAME			= MINITALK
BONUS				= MINITALK_BONUS

SERVER 				= server
BONUS_SERVER 		= server

CLIENT				= client
BONUS_CLIENT		= client

CC 					= gcc
CFLAGS				= -Wall -Werror -Wextra

INCFLAGS 			= -I./libft

LIBFT_PATH			= ./libft/
LIBFT_FILES 		= ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_atoi.c ft_strdup.c ft_strlen.c
LIBFT_SRCS			= $(addprefix $(LIBFT_PATH), $(LIBFT_FILES))
LIBFT_OBJS			= $(LIBFT_SRCS:.c=.o)

SRCS_PATH			= ./srcs/
SERVER_FILES 		= server.c server_handler.c ft_charjoin.c
SERVER_SRCS			= $(addprefix $(SRCS_PATH), $(SERVER_FILES))
SERVER_OBJS			= $(SERVER_SRCS:.c=.o)
CLIENT_FILES 		= client.c client_handler.c
CLIENT_SRCS			= $(addprefix $(SRCS_PATH), $(CLIENT_FILES))
CLIENT_OBJS			= $(CLIENT_SRCS:.c=.o)

BONUS_SRCS_PATH		= ./srcs_bonus/
BONUS_SERVER_FILES	= server_bonus.c server_handler_bonus.c ft_charjoin_bonus.c
BONUS_SERVER_SRCS	= $(addprefix $(BONUS_SRCS_PATH), $(BONUS_SERVER_FILES))
BONUS_SERVER_OBJS	= $(BONUS_SERVER_SRCS:.c=.o)
BONUS_CLIENT_FILES	= client_bonus.c client_handler_bonus.c
BONUS_CLIENT_SRCS	= $(addprefix $(BONUS_SRCS_PATH), $(BONUS_CLIENT_FILES))
BONUS_CLIENT_OBJS	= $(BONUS_CLIENT_SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(SERVER)	: $(LIBFT_OBJS) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^
$(BONUS_SERVER)	: $(LIBFT_OBJS) $(BONUS_SERVER_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^

$(CLIENT)	: $(LIBFT_OBJS) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^
$(BONUS_CLIENT)	: $(LIBFT_OBJS) $(BONUS_CLIENT_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^

$(NAME) 	: $(SERVER) $(CLIENT)
$(BONUS)		: $(BONUS_SERVER) $(BONUS_CLIENT)

all : $(NAME)

bonus : $(BONUS)

re			: fclean all

clean		:
		$(RM) $(LIBFT_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS) $(BONUS_SERVER_OBJS) $(BONUS_CLIENT_OBJS)

fclean		: clean
		$(RM) $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)

.PHONY		: all re clean fclean