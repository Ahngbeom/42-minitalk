# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/16 19:22:48 by bahn              #+#    #+#              #
#    Updated: 2021/08/01 23:17:30 by bahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINITALK			= MINITALK

SERVER 				= server
CLIENT				= client

CC 					= gcc
CFLAGS				= -Wall -Werror -Wextra

INCFLAGS 			= -I./libft

LIBFT_PATH			= ./libft/
LIBFT_FILES 		= ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_atoi.c ft_strdup.c ft_strlen.c
LIBFT_SRCS			= $(addprefix $(LIBFT_PATH), $(LIBFT_FILES))
LIBFT_OBJS			= $(LIBFT_SRCS:.c=.o)

SRCS_PATH			= ./srcs
SERVER_FILES 		= server.c server_handler.c ft_charjoin.c ft_putstr_lf.c ft_kill.c
CLIENT_FILES 		= client.c client_handler.c ft_putstr_lf.c ft_kill.c
EXCEPTION_FILES		= exception.c
SERVER_SRCS			= $(addprefix $(addsuffix /, $(SRCS_PATH)), $(SERVER_FILES) $(EXCEPTION_FILES))
SERVER_SRCS_BONUS	= $(addprefix $(addsuffix _bonus/, $(SRCS_PATH)), $(patsubst %.c, %_bonus.c, $(SERVER_FILES) $(EXCEPTION_FILES)))
CLIENT_SRCS			= $(addprefix $(addsuffix /, $(SRCS_PATH)), $(CLIENT_FILES) $(EXCEPTION_FILES))
CLIENT_SRCS_BONUS	= $(addprefix $(addsuffix _bonus/, $(SRCS_PATH)), $(patsubst %.c, %_bonus.c, $(CLIENT_FILES) $(EXCEPTION_FILES)))
SERVER_OBJS			= $(SERVER_SRCS:.c=.o)
SERVER_OBJS_BONUS	= $(SERVER_SRCS_BONUS:.c=.o)
CLIENT_OBJS			= $(CLIENT_SRCS:.c=.o)
CLIENT_OBJS_BONUS	= $(CLIENT_SRCS_BONUS:.c=.o)

ifdef BONUS
	SERVER_OBJECTS 	= $(SERVER_OBJS_BONUS)
	CLIENT_OBJECTS 	= $(CLIENT_OBJS_BONUS)
else
	SERVER_OBJECTS	= $(SERVER_OBJS)
	CLIENT_OBJECTS	= $(CLIENT_OBJS)
endif

all: $(MINITALK)

.c.o:
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(SERVER): $(LIBFT_OBJS) $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -o $@

$(CLIENT): $(LIBFT_OBJS) $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -o $@

$(MINITALK): $(SERVER) $(CLIENT)

bonus:
	$(MAKE) BONUS=1 all

re: fclean all

clean:
	$(RM) $(LIBFT_OBJS) $(SERVER_OBJS) $(SERVER_OBJS_BONUS) $(CLIENT_OBJS) $(CLIENT_OBJS_BONUS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

.PHONY: all re clean fclean