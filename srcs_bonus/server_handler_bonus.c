/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:18:49 by bahn              #+#    #+#             */
/*   Updated: 2021/08/01 23:13:20 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data	g_server_data;

void	hdr_connection_with_client(int signo, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signo == SIGUSR1 || signo == SIGUSR2)
	{
		ft_putnbr_fd(siginfo->si_pid, 1);
		ft_putstr_fd(" : ", 1);
		g_server_data.pid = siginfo->si_pid;
		g_server_data.msg = ft_strdup("");
		g_server_act.sa_sigaction = hdr_receive_message;
		sigaction(SIGUSR1, &g_server_act, NULL);
		sigaction(SIGUSR2, &g_server_act, NULL);
		ft_kill(g_server_data.pid, signo);
	}
	else
		exception("CONNECTION FAILED");
}

void	hdr_receive_message(int signo, siginfo_t *siginfo, void *context)
{
	static int	bit = 8;
	static char	ch = '\0';

	(void)context;
	if (signo == SIGUSR1)
		ch += 1 << --bit;
	else if (signo == SIGUSR2)
		--bit;
	if (bit == 0)
	{
		if (ch != '\0')
			g_server_data.msg = ft_charjoin(g_server_data.msg, ch);
		else
		{
			ft_putstr_lf(g_server_data.msg);
			free(g_server_data.msg);
			g_server_act.sa_sigaction = hdr_connection_with_client;
			sigaction(SIGUSR1, &g_server_act, NULL);
			sigaction(SIGUSR2, &g_server_act, NULL);
			ft_kill(siginfo->si_pid, SIGUSR2);
		}
		bit = 8;
		ch = '\0';
	}
}
