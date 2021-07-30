/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:18:48 by bahn              #+#    #+#             */
/*   Updated: 2021/01/06 16:42:47 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dptr;
	unsigned char	*sptr;

	if (!dest && !src)
		return (NULL);
	dptr = (unsigned char *)dest;
	sptr = (unsigned char *)src;
	while (n--)
	{
		*dptr++ = *sptr++;
	}
	return (dest);
}
