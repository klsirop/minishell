/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:23:39 by jmaynard          #+#    #+#             */
/*   Updated: 2019/01/14 13:46:38 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_pushback(t_list **lst, t_list *new)
{
	if (!lst || !*lst || !new)
		return ;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	new->next = (*lst)->next;
	(*lst)->next = new;
}
