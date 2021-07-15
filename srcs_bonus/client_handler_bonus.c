/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 23:05:43 by bahn              #+#    #+#             */
/*   Updated: 2021/07/15 23:27:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void    hdr_server_with_connection(int signo, siginfo_t *siginfo, void *context)
{
    (void)siginfo;
    (void)context;
    if (signo == SIGUSR1)
    {
        ft_putstr_fd("Server with Connection : SUCCESS\n", 1);
        // ft_putstr_fd("Received SIGNAL from SERVER : ", 1);
        // ft_putnbr_fd(siginfo->si_signo, 1);

        client_act.sa_sigaction = hdr_send_message;
        sigaction(SIGUSR1, &client_act, NULL);
        sigaction(SIGUSR2, &client_act, NULL);
        ft_send_message();
    }
    else
    {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }
}

void    hdr_send_message(int signo, siginfo_t *siginfo, void *context)
{
    (void)siginfo;
    (void)context;
    
    if (signo == SIGUSR1)
    {
        ft_putstr_fd("Send Character to SERVER : SUCCESS\n", 1);
        ft_putchar_fd('\n', 1);
        ft_send_message();
    }
    else
        exit(0);
}