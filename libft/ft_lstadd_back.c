/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:54:08 by bahn              #+#    #+#             */
/*   Updated: 2021/01/05 21:50:29 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*org_last;

	if (lst)
	{
		if (*lst)
		{
			org_last = ft_lstlast(*lst);
			org_last->next = new;
		}
		else
			*lst = new;
	}
}
