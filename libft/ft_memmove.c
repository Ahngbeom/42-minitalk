/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:24:18 by bahn              #+#    #+#             */
/*   Updated: 2021/01/06 16:43:31 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dptr;
	unsigned char	*sptr;

	dptr = (unsigned char*)dest;
	sptr = (unsigned char*)src;
	if (!dest && !src)
		return (NULL);
	if (dptr <= sptr)
	{
		i = 0;
		while (i++ < n)
			*dptr++ = *sptr++;
	}
	else
	{
		i = n;
		while (i-- > 0)
			*(dptr + i) = *(sptr + i);
	}
	return (dest);
}
