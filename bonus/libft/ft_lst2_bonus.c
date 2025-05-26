/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:50:04 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/08 13:04:28 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == 0)
		return ;
	if (del != 0)
		(del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*prev;

	if (*lst == 0)
		return ;
	iter = *lst;
	while (iter != 0)
	{
		prev = iter;
		iter = iter->next;
		ft_lstdelone(prev, del);
	}
	*lst = 0;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iter;

	if (lst == 0)
		return ;
	iter = lst;
	while (iter != 0)
	{
		(f)(iter->content);
		iter = iter->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;

	if (!lst)
		return (0);
	elem = ft_calloc(1, sizeof(t_list));
	if (!elem)
		return (0);
	elem->content = (f)(lst->content);
	if (lst->next)
	{
		elem->next = ft_lstmap(lst->next, f, del);
		if (elem->next == 0)
		{
			(del)(elem->content);
			free(elem);
			return (0);
		}
	}
	else
		elem->next = 0;
	return (elem);
}
