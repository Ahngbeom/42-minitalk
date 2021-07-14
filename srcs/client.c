/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 00:05:29 by bahn              #+#    #+#             */
/*   Updated: 2021/07/14 23:59:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct sigaction act;

void server_with_connection(int signo, siginfo_t *siginfo, void *context);
void    send_message();

void server_with_connection(int signo, siginfo_t *siginfo, void *context)
{
    (void)context;
    if (signo == SIGUSR1)
    {
        ft_putstr_fd("Server with Connection : SUCCESS\n", 1);
        ft_putstr_fd("Received SIGNAL from SERVER : ", 1);
        ft_putnbr_fd(siginfo->si_signo, 1);
        ft_putchar_fd('\n', 1);

        act.sa_sigaction = send_message;
    }
    else
    {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }
}

void    send_message()
{
    int     bit;
    char    ch;

    ft_putstr_fd("SEND MESSAGE : ", 1);
    ft_putstr_fd("a", 1);
    ft_putstr_fd(" (", 1);
    bit = 8;
    ch = 'a';
	while (--bit >= 0)
	{
		// if ((ch >> bit) & 1)
		// 	ft_putnbr_fd(1, 1);
		// else
		// 	ft_putnbr_fd(0, 1);
		ft_putnbr_fd((ch >> bit) & 1, 1);
		usleep(1000);
	}
    ft_putstr_fd(")\n", 1);
}

int main(int argc, char **argv)
{
    pid_t   server_pid;

    if (argc != 3)
    {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }

    act.sa_sigaction = server_with_connection;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    server_pid = ft_atoi(argv[1]);
    
    kill(server_pid, SIGUSR1);
    usleep(1000);
    send_message();

    while (1)
    {
        pause();
    }

    return (0);
}