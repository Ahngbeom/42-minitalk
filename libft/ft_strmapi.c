/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:37:17 by bahn              #+#    #+#             */
/*   Updated: 2021/01/01 20:18:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fstr;

	if (!s || !f)
		return (NULL);
	i = 0;
	fstr = (char *)malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!fstr)
		return (NULL);
	while (s[i] != '\0')
	{
		fstr[i] = f(i, s[i]);
		i++;
	}
	fstr[i] = '\0';
	return (fstr);
}
