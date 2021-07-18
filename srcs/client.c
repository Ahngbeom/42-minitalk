/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:45:23 by bahn              #+#    #+#             */
/*   Updated: 2021/07/18 15:37:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_client_data;

void    ft_connection() {
    exception_kill(kill(g_client_data.opponent_pid, SIGUSR1));
    pause();
}

void    ft_send_message() {
    static  int i = 0;
    static  int bit = 8;

    while (g_client_data.msg[i] != '\0')
    {
        while (--bit >= 0) {
            if ((g_client_data.msg[i] >> bit) & 1)
                exception_kill(kill(g_client_data.opponent_pid, SIGUSR1));
            else
                exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
            usleep(125);
        }
        bit = 8;
        i++;
    }
    if (g_client_data.msg[i] == '\0')
    {
        while (bit-- > 0)
        {
            exception_kill(kill(g_client_data.opponent_pid, SIGUSR2));
            usleep(125);
        }
        pause();
    }
}

int     main(int argc, char **argv) {
    if (argc != 3)
        exception_message("./client [SERVER PID] [SEND MESSAGE]");
    client_act.sa_flags = SA_SIGINFO;
    client_act.sa_sigaction = hdr_server_with_connection;
    sigemptyset(&client_act.sa_mask);
    sigaction(SIGUSR1, &client_act, NULL);
    sigaction(SIGUSR2, &client_act, NULL);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    g_client_data.opponent_pid = ft_atoi(argv[1]);
    g_client_data.msg = argv[2];
    ft_connection();
    return (0);
}