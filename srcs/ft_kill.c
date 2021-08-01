/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 22:35:34 by bahn              #+#    #+#             */
/*   Updated: 2021/08/01 23:14:33 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(pid_t pid, int signo)
{
	if (kill(pid, signo) != 0)
	{
		exception("INVALID PID or KILL ERROR");
		exit(1);
	}
	else
		usleep(125);
}
