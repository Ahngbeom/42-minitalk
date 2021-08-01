/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:42:41 by bahn              #+#    #+#             */
/*   Updated: 2021/08/01 23:07:50 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	hdr_connection_with_server(int signo, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signo == SIGUSR1)
	{
		ft_putstr_lf("Connection with SERVER : SUCCESS");
		g_client_act.sa_sigaction = hdr_send_message;
		sigaction(SIGUSR1, &g_client_act, NULL);
		sigaction(SIGUSR2, &g_client_act, NULL);
		ft_send_message();
	}
	else if (signo == SIGUSR2)
		exception("CONNECTION FAILED");
	else
		exception("INVALID SIGNAL");
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
		exception("SEND MESSAGE FAILED");
}
