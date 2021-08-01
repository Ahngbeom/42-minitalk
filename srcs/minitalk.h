/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 23:06:18 by bahn              #+#    #+#             */
/*   Updated: 2021/08/01 23:08:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>

struct sigaction	g_server_act;
struct sigaction	g_client_act;

typedef struct s_data
{
	pid_t			pid;
	char			*msg;
}			t_data;

// Server Handler
void	hdr_connection_with_client(int signo, \
		siginfo_t *siginfo, void *context);
void	hdr_receive_message(int signo, siginfo_t *siginfo, void *context);

// Server Function
char	*ft_charjoin(char *str, char ch);

// Client Handler
void	hdr_connection_with_server(int signo, \
		siginfo_t *siginfo, void *context);
void	hdr_send_message(int signo, siginfo_t *siginfo, void *context);

// Client Function
void	ft_connection_with_server(int signo);
void	ft_send_message(void);

//	My KILL Function
void	ft_kill(pid_t pid, int signo);

// Printing Exception Info
void	exception(char *exception);

// Printing Message with LineFeed
void	ft_putstr_lf(char *str);

#endif
