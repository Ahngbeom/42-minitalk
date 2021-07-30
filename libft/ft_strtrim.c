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

static	void	remove_front_trim(char const *set, char **start, char *limit)
{
	while (ft_strchr((char *)set, **start) && *start < limit)
		*start++;
	return (start);
}

static	char	*remove_back_trim(char const *set, char *start, char *limit)
{
	while (ft_strchr((char *)set, *start) && start > limit)
		start--;
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*s1_first;
	char	*s1_last;

	if (!s1)
		return (NULL);
	s1_last = (char *)s1 + ft_strlen((char *)s1) - 1;
	s1_first = remove_front_trim(set, (char *)s1, s1_last);
	s1_last = remove_back_trim(set, s1_last, (char *)s1);
	if (s1_first > s1_last)
	{
		result = (char *)malloc(1);
		if (result == NULL)
			return (NULL);
		*result = '\0';
	}
	else
	{
		result = (char *)malloc(s1_last - s1_first + 2);
		if (result == NULL)
			return (NULL);
		ft_strlcpy(result, s1_first, s1_last - s1_first + 2);
	}
	return (result);
}
