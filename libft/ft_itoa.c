/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:49:43 by bahn              #+#    #+#             */
/*   Updated: 2021/01/04 14:42:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_nbrlen(long long nbr)
{
	int			i;
	size_t		length;
	long long	num;

	i = 1;
	length = 0;
	if (nbr < 0)
		num = nbr * -1;
	else
		num = nbr;
	while (num / i >= 10)
	{
		i *= 10;
		length++;
	}
	return (++length);
}

static	void	ft_putnbr(char *ptr, long long nb, size_t len)
{
	size_t	i;
	size_t	divisor;

	i = 0;
	divisor = 1;
	while (++i < len)
		divisor *= 10;
	while (len-- > 0)
	{
		*ptr++ = '0' + (nb / divisor);
		nb %= divisor;
		divisor /= 10;
	}
	*ptr = '\0';
}

char	*ft_itoa(int n)
{
	char		*nbr;
	size_t		len;
	long long	num;

	num = (long long)n;
	len = ft_nbrlen(num);
	if (n < 0)
	{
		nbr = (char *)malloc(sizeof(char) * (len + 2));
		if (nbr == NULL)
			return (NULL);
		*nbr = '-';
		ft_putnbr(nbr + sizeof(char), num * -1, len);
	}
	else
	{
		nbr = (char *)malloc(sizeof(char) * (len + 1));
		if (nbr == NULL)
			return (NULL);
		ft_putnbr(nbr, num, len);
	}
	return (nbr);
}
