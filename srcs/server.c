/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:42:29 by bahn              #+#    #+#             */
/*   Updated: 2021/08/01 23:13:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		exception("./server [NO ARGUMENTS REQUIRED]");
	g_server_act.sa_flags = SA_SIGINFO;
	g_server_act.sa_sigaction = hdr_connection_with_client;
	sigemptyset(&g_server_act.sa_mask);
	sigaction(SIGUSR1, &g_server_act, NULL);
	sigaction(SIGUSR2, &g_server_act, NULL);
	ft_putstr_fd("[SERVER PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_lf("]");
	while (1)
		pause();
}
