/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 23:06:11 by bahn              #+#    #+#             */
/*   Updated: 2021/07/17 22:24:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>

struct sigaction server_act;
struct sigaction client_act;

typedef struct s_data {
    pid_t    opponent_pid;
    char    *msg;
}   t_data;

extern t_data g_server_data;
extern t_data g_client_data;

// Server Handler
void    hdr_client_with_connection(int signo, siginfo_t *siginfo, void *context);
void    hdr_receive_message(int signo, siginfo_t *siginfo, void *context);

// Server Function
char	*ft_charjoin(char *str, char ch);

// Client Handler
void    hdr_server_with_connection(int signo, siginfo_t *siginfo, void *context);
void    hdr_send_message(int signo, siginfo_t *siginfo, void *context);

// Client Function
void    ft_server_with_connection(pid_t pid);
void    ft_send_message();

// Exception Handler
void    exception_message(char *exception);
int    exception_kill(int rtn);

#endif