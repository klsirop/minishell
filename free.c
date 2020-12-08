/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:44:20 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 21:27:58 by volyvar-         ###   ########.fr       */
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

void	ft_free_env(t_env **env)
{
	t_env *tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->content));
		free(tmp);
	}
}
