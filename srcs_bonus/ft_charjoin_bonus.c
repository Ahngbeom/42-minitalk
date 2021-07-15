/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bbu0704@gmail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:37:06 by bahn              #+#    #+#             */
/*   Updated: 2021/07/15 23:27:55 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

char	*ft_charjoin(char *str, char ch)
{
	size_t	str_len;
	char	*ptr;
    int     i;

	if (!str)
		return (NULL);
	str_len = ft_strlen((char *)str);
	if (!(ptr = malloc(str_len + sizeof(char) + 1)))
		return (NULL);
    i = 0;
	while (str[i] != '\0')
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i++] = ch;
    ptr[i] = '\0';
	free(str);
	return (ptr);
}
