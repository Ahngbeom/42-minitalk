/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:45:23 by bahn              #+#    #+#             */
/*   Updated: 2021/07/15 23:28:02 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data g_client_data;

void    ft_connection() {
    kill(g_client_data.opponent_pid, SIGUSR1);
    pause();
}

void    ft_send_message() {
    static  int i = 0;
    static  int bit = 8;

    while (g_client_data.msg[i] != '\0')
    {
        // ft_putstr_fd("SEND CHARACTER : ", 1);
        while (--bit >= 0) {
            // ft_putnbr_fd((g_client_data.msg[i] >> bit) & 1, 1);
            if ((g_client_data.msg[i] >> bit) & 1)
                kill(g_client_data.opponent_pid, SIGUSR1);
            else
                kill(g_client_data.opponent_pid, SIGUSR2);
            usleep(1000);
        }
        bit = 8;
        i++;
    }
    if (g_client_data.msg[i] == '\0')
    {
        while (bit-- > 0)
        {
            kill(g_client_data.opponent_pid, SIGUSR2);
            usleep(1000);
        }
        exit(0);
    }
}

int     main(int argc, char **argv) {
    if (argc != 3) {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }

    client_act.sa_sigaction = hdr_server_with_connection;
    sigemptyset(& client_act.sa_mask);
    client_act.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, & client_act, NULL);
    sigaction(SIGUSR2, & client_act, NULL);

    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);

    g_client_data.opponent_pid = ft_atoi(argv[1]);
    g_client_data.msg = argv[2];

    ft_connection();

    return (0);
}