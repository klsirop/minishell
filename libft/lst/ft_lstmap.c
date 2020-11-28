/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:23:28 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/19 15:22:57 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdelete(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	free(lst);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*head;

	if (!f || !lst)
		return (NULL);
	head = ft_lstnew(f(lst)->content, f(lst)->content_size);
	tmp = head;
	lst = lst->next;
	if (!head)
		return (NULL);
	while (lst)
	{
		tmp->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (!tmp->next)
		{
			ft_lstdelete(head);
			return (NULL);
		}
		lst = lst->next;
		tmp = tmp->next;
	}
	return (head);
}
