/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 00:05:29 by bahn              #+#    #+#             */
/*   Updated: 2021/07/14 01:42:00 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void sigact_handler()
{
    ft_putstr_fd("CLIENT Signal !\n", 1);
}

int main(int argc, char **argv)
{
    struct sigaction act;
    pid_t   server_pid;

    if (argc != 3)
    {
        ft_putstr_fd("ERROR !\n", 1);
        exit(1);
    }

    act.sa_handler = sigact_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
    sigaction(SIGUSR1, &act, NULL);

    server_pid = ft_atoi(argv[1]);
    kill(server_pid, SIGUSR1);

    return (0);
}