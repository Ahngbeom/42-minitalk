NAME		= MINITALK

SERVER 		= server
CLIENT		= client

CC 			= gcc
CFLAGS		= -Wall -Werror -Wextra
INCFLAGS 	= -I./includes -I./libft

LIBFT_PATH	= ./libft/
LIBFT_FILES = ft_putstr_fd.c ft_putnbr_fd.c ft_atoi.c
LIBFT_SRCS	= $(addprefix $(LIBFT_PATH), $(LIBFT_FILES))
LIBFT_OBJS	= $(LIBFT_SRCS:.c=.o)

SERVER_PATH	= ./srcs/
SERVER_FILES = server.c
SERVER_SRCS	= $(addprefix $(SERVER_PATH), $(SERVER_FILES))
SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

CLIENT_PATH	= ./srcs/
CLIENT_FILES = client.c
CLIENT_SRCS	= $(addprefix $(CLIENT_PATH), $(CLIENT_FILES))
CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(SERVER)	: $(LIBFT_OBJS) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^

$(CLIENT)	: $(LIBFT_OBJS) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $^

$(NAME) 	: $(SERVER) $(CLIENT)

all : $(NAME)

re			: fclean all

clean		:
		$(RM) $(LIBFT_OBJS) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean		: clean
		$(RM) $(SERVER) $(CLIENT)

.PHONY		: all re clean fclean