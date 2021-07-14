/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:47:03 by bahn              #+#    #+#             */
/*   Updated: 2021/01/01 19:13:45 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	int		src_len;
	char	*cpy;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	cpy = malloc(sizeof(char) * src_len + 1);
	if (!cpy)
		return (NULL);
	while (i < src_len)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
