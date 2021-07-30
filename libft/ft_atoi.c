/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:46:58 by bahn              #+#    #+#             */
/*   Updated: 2021/07/30 20:56:36 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_sp_check(char ch)
{
	if (ch != '\0')
	{
		if (ch == ' ' || ch == '\f' || \
				ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
		{
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

static	char	*ft_isspace(char *str)
{
	while (ft_sp_check(*str))
	{
		str++;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	long long	sign;
	long long	nbr;

	sign = 1;
	nbr = 0;
	str = ft_isspace(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		else if (*str == '+')
			sign *= 1;
		str++;
	}
	while ((*str != '\0') && (*str >= '0' && *str <= '9'))
	{
		nbr = (nbr * 10) + (*str - 48);
		if (nbr * sign > 2147483647)
			return (-1);
		else if (nbr * sign < -2147483648)
			return (0);
		str++;
	}
	return (nbr * sign);
}
