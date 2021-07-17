/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 20:06:53 by bahn              #+#    #+#             */
/*   Updated: 2021/07/17 20:59:00 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    exception_message(char *exception)
{
    ft_putstr_fd("ERROR : ", 1);
    ft_putstr_fd(exception, 1);
    ft_putchar_fd('\n', 1);
    exit(1);
}

int     exception_kill(int rtn)
{
    if (rtn == 0)
        return (0);
    else
    {
        exception_message("INVALID PID or KILL ERROR");
        exit(1);
    }
}