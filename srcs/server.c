/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 23:55:31 by root              #+#    #+#             */
/*   Updated: 2021/07/15 00:00:53 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main()
{
    act.sa_sigaction = client_with_connection;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    while(1)
    {
        pause();
    }
}