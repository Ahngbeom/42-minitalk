/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:21:59 by bahn              #+#    #+#             */
/*   Updated: 2021/01/04 13:52:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	size_t	i;
	t_list	**lists;

	lists = (t_list **)malloc(sizeof(t_list *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		lists[i] = ft_lstnew(f(lst->content));
		if (lists[i] == NULL)
		{
			ft_lstclear(lists, del);
			return (NULL);
		}
		lst = lst->next;
		if (i > 0)
			lists[i - 1]->next = lists[i];
		i++;
	}
	lists[i] = NULL;
	return (*lists);
}
