/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:50:13 by bahn              #+#    #+#             */
/*   Updated: 2021/01/02 12:27:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if ((size_t)ft_strlen((char *)s) < start)
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[i] = '\0';
	}
	else
	{
		ptr = malloc(len + 1);
		if (ptr == NULL)
			return (NULL);
		while (i < len && s[start] != '\0')
			ptr[i++] = s[start++];
		ptr[i] = '\0';
	}
	return (ptr);
}
