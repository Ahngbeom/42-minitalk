/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:18:49 by bahn              #+#    #+#             */
/*   Updated: 2021/07/17 20:49:56 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data g_server_data;

void hdr_client_with_connection(int signo, siginfo_t *siginfo, void *context)
{
    (void)context;
    if (signo == SIGUSR1)
    {
        ft_putstr_fd("Client-", 1);
        ft_putnbr_fd(siginfo->si_pid, 1);
        ft_putstr_fd(" with Connection : SUCCESS\n", 1);
        g_server_data.opponent_pid = siginfo->si_pid;
        g_server_data.msg = ft_strdup("");
        server_act.sa_sigaction = hdr_receive_message;
        sigaction(SIGUSR1, &server_act, NULL);
        sigaction(SIGUSR2, &server_act, NULL);
        exception_kill(kill(siginfo->si_pid, siginfo->si_signo));
    }
    else if (signo == SIGUSR2)
        exception_message("CONNECTION FAILED");
    else
        exception_message("INVALID SIGNAL");
}

void hdr_receive_message(int signo, siginfo_t *siginfo, void *context)
{
    static int bit = 8;
    static char ch = 0;

    (void)context;   
    if (signo == SIGUSR1)
        ch += 1 << --bit;
    else if (signo == SIGUSR2)
        --bit;
    else
        exception_message("INVALID SIGNAL");
    if (bit == 0)
    {
        if (ch != 0)
            g_server_data.msg = ft_charjoin(g_server_data.msg, ch);
        else
        {
            ft_putstr_fd(g_server_data.msg, 1);
            ft_putchar_fd('\n', 1);
            free(g_server_data.msg);
            server_act.sa_sigaction = hdr_client_with_connection;
            sigaction(SIGUSR1, &server_act, NULL);
            sigaction(SIGUSR2, &server_act, NULL);
            exception_kill(kill(siginfo->si_pid, SIGUSR2));
        }
        bit = 8;
        ch = 0;
    }
}