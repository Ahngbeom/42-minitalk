/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:45:23 by bahn              #+#    #+#             */
/*   Updated: 2021/07/30 21:25:11 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data	g_client_data;

void	ft_connection(void)
{
	exception_kill(kill(g_client_data.opponent_pid, SIGUSR1));
	pause();
}

void	ft_send_message(void)
{
	static int	i = 0;
	static int	bit = 8;
	static int	kill_count = 0;

	while (g_client_data.msg[i] != '\0')
	{
		while (--bit >= 0)
		{
			if ((g_client_data.msg[i] >> bit) & 1)
				exception_kill(kill(g_client_data.opponent_pid, SIGUSR1));
			else
				exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
			kill_count++;
		}
		bit = 8;
		i++;
	}
	if (g_client_data.msg[i] == '\0')
	{
		while (bit-- > 0)
			exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
		pause();
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		exception_message("./client [SERVER PID] [SEND MESSAGE]");
	g_client_act.sa_flags = SA_SIGINFO;
	g_client_act.sa_sigaction = hdr_server_with_connection;
	sigemptyset(&g_client_act.sa_mask);
	sigaction(SIGUSR1, &g_client_act, NULL);
	sigaction(SIGUSR2, &g_client_act, NULL);
	ft_putstr_fd("[CLIENT PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_lf("]");
	g_client_data.opponent_pid = ft_atoi(argv[1]);
	g_client_data.msg = argv[2];
	ft_connection();
	return (0);
}
