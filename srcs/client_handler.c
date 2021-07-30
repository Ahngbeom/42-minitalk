/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:42:41 by bahn              #+#    #+#             */
/*   Updated: 2021/07/30 21:18:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	hdr_server_with_connection(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_putstr_lf("SERVER with Connection : SUCCESS");
		g_client_act.sa_sigaction = hdr_send_message;
		sigaction(SIGUSR1, &g_client_act, NULL);
		sigaction(SIGUSR2, &g_client_act, NULL);
		ft_send_message();
	}
	else if (signo == SIGUSR2)
		exception_message("CONNECTION FAILED");
	else
		exception_message("INVALID SIGNAL");
}

void	hdr_send_message(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGUSR2)
	{
		ft_putstr_lf("Send Message to SERVER : SUCCESS");
		exit(0);
	}
	else
		exception_message("SEND MESSAGE FAILED");
}
