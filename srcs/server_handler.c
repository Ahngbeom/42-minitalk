/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:18:49 by bahn              #+#    #+#             */
/*   Updated: 2021/07/15 00:00:38 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void client_with_connection(int signo, siginfo_t *siginfo, void *context)
{
    (void)context;
    if (signo == SIGUSR1)
    {
        ft_putstr_fd("Client with Connection : SUCCESS\n", 1);
        ft_putstr_fd("CLIENT PID : ", 1);
        ft_putnbr_fd(siginfo->si_pid, 1);
        ft_putchar_fd('\n', 1);
        ft_putstr_fd("CLIENT SIGNAL : ", 1);
        ft_putnbr_fd(signo, 1);
        ft_putchar_fd('\n', 1);

        act.sa_sigaction = receive_message;

        kill(siginfo->si_pid, siginfo->si_signo);
        usleep(1000);
    }
    else
    {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }
}

void receive_message(int signo, siginfo_t *siginfo, void *context)
{
    static int bit = 8;
    static char ch = 0;

    (void)context;   
    if (signo == SIGUSR1)
    {
        ch += 1 << --bit;
        // kill(siginfo->si_pid, siginfo->si_signo);
    }
    else if (signo == SIGUSR2)
    {
        --bit;
        // kill(siginfo->si_pid, siginfo->si_signo);
    }
    ft_putnbr_fd((ch >> bit) & 1, 1);
    
    if (bit == 0)
    {
        kill(siginfo->si_pid, siginfo->si_signo);
        bit = 8;
        ch = 0;
    }
}