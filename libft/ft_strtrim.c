/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:01:24 by bahn              #+#    #+#             */
/*   Updated: 2021/01/02 17:10:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*s1_first;
	char	*s1_last;

	if (!s1)
		return (NULL);
	s1_first = (char *)s1;
	s1_last = (char *)s1 + ft_strlen((char *)s1) - 1;
	while (ft_strchr((char *)set, *s1_first) && s1_first < s1_last)
		s1_first++;
	while (ft_strchr((char *)set, *s1_last) && s1_last > s1)
		s1_last--;
	if (s1_first > s1_last)
	{
		if (!(result = (char *)malloc(1)))
			return (0);
		*result = '\0';
	}
	else
	{
		if (!(result = (char *)malloc(s1_last - s1_first + 2)))
			return (0);
		ft_strlcpy(result, s1_first, s1_last - s1_first + 2);
	}
	return (result);
}
