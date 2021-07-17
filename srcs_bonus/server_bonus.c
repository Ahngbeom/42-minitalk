/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:42:29 by bahn              #+#    #+#             */
/*   Updated: 2021/07/17 22:26:23 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data g_server_data;

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
        exception_message("./server [NO ARGUMENTS]");
    server_act.sa_sigaction = hdr_client_with_connection;
    sigemptyset(&server_act.sa_mask);
    server_act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &server_act, NULL);
    sigaction(SIGUSR2, &server_act, NULL);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    while(1)
        pause();
}