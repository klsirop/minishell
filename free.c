/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:20 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/05 16:22:00 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_after_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_strdel(&arr[i]);
		i++;
	}
}

void	ft_free_after_split_path(char **arr)
{
	int i;
	int last;

	last = 0;
	i = 0;
	while (arr[i] && !last)
	{
		if (!ft_strcmp(arr[i], ""))
			last = 1;
		ft_strdel(&arr[i]);
		i++;
	}
}