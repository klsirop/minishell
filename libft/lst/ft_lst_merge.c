/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 19:15:49 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/21 12:50:24 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_list_last(const t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return ((t_list *)lst);
}

t_list			*ft_lst_merge(t_list **lst1, const t_list **lst2)
{
	t_list *tmp1;

	if (!lst1 || !lst2)
		return (NULL);
	tmp1 = ft_list_last((t_list *)lst1);
	tmp1->next = (t_list *)(*lst2);
	return ((t_list *)lst1);
}
