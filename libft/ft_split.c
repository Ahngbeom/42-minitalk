/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:22:04 by bahn              #+#    #+#             */
/*   Updated: 2021/01/05 22:25:26 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_free_malloc(char **pptr)
{
	size_t	i;

	i = 0;
	while (pptr[i])
		free(pptr[i++]);
	free(pptr);
	return (pptr);
}

static	size_t	ft_countstrs(char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			cnt++;
			while (*(++s) != c)
			{
				if (*s == '\0')
					break ;
			}
		}
		else
			s++;
	}
	return (cnt);
}

static	char	*ft_findstr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
			return (s);
	}
	return (0);
}

static	size_t	ft_strclen(char *s, char c)
{
	size_t	length;
	char	*ptr;

	length = 0;
	ptr = s;
	while (*ptr != '\0' && *ptr != c)
	{
		length++;
		ptr++;
	}
	return (length);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*sptr;
	size_t	cnt_strs;
	size_t	i;

	if (!s)
		return (NULL);
	sptr = (char *)s;
	cnt_strs = ft_countstrs(sptr, c);
	result = (char **)malloc(sizeof(char *) * (cnt_strs + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i < cnt_strs)
	{
		result[i] = (char *)malloc(ft_strclen(ft_findstr(sptr, c), c) + 1);
		if (result[i] == NULL)
			return (ft_free_malloc(result));
		ft_strlcpy(result[i], ft_findstr(sptr, c), \
				ft_strclen(ft_findstr(sptr, c), c) + 1);
		sptr = ft_findstr(ft_findstr(sptr, c) + \
				ft_strclen(ft_findstr(sptr, c), c), c);
	}
	result[i] = NULL;
	return (result);
}
