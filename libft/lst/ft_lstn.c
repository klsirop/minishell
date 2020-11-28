/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 19:07:05 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/20 20:33:23 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstn(const t_list *lst, int n)
{
	int i;

	i = 0;
	if (!lst)
		return (NULL);
	while (i < n && lst)
	{
		i++;
		lst = lst->next;
	}
	return ((t_list *)lst);
}
