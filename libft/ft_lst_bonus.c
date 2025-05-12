/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:06:47 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/13 18:14:05 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = ft_calloc(1, sizeof(t_list));
	if (newlst == 0)
		return (0);
	newlst->content = content;
	newlst->next = 0;
	return (newlst);
}

void	ft_lstadd_front(t_list **lst, t_list *newlst)
{
	if (newlst == 0)
		return ;
	newlst->next = *lst;
	*lst = newlst;
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*iter;

	if (lst == 0)
		return (0);
	i = 1;
	iter = lst;
	while (iter->next != 0)
	{
		iter = iter->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*iter;

	if (lst == 0)
		return (0);
	iter = lst;
	while (iter->next != 0)
		iter = iter->next;
	return (iter);
}

void	ft_lstadd_back(t_list **lst, t_list *newlst)
{
	t_list	*last;

	if (newlst == 0)
		return ;
	if (*lst == 0)
	{
		*lst = newlst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = newlst;
}
