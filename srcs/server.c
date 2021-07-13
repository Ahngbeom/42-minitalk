/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 23:55:31 by root              #+#    #+#             */
/*   Updated: 2021/07/14 00:38:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void sigact_handler()
{
    ft_putstr_fd("SERVER Signal !\n", 1);
}

int main()
{
    struct sigaction act;

    act.sa_handler = sigact_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);
    ft_putnbr_fd(getpid(), 1);

    while(1)
    {
        pause();
    }
}