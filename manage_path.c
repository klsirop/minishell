/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:08:02 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:39:25 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_str_help(char **str, char **arr, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			(*str)[k] = arr[i][j];
			j++;
			k++;
		}
		i++;
		if (arr[i] != NULL)
		{
			(*str)[k] = c;
			k++;
		}
	}
	(*str)[k] = '\0';
}

char	*ft_create_str_from_split(char **arr, char c)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = 0;
	while (arr[i] != NULL)
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + i + 1))))
		ft_malloc_error();
	ft_create_str_help(&str, arr, c);
	return (str);
}

int		ft_arrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	ft_path_step_back(char **old_path)
{
	char **piece_path;
	char *new_path;

	if (!ft_strcmp(*old_path, "/"))
		return ;
	piece_path = ft_strsplit(*old_path, '/');
	if (ft_arrlen(piece_path) == 1)
	{
		ft_strdel(old_path);
		ft_free_after_split(piece_path);
		free(piece_path);
		if (!(*old_path = ft_strdup("/")))
			ft_malloc_error();
		return ;
	}
	ft_strdel(&(piece_path[ft_arrlen(piece_path) - 1]));
	new_path = ft_create_str_from_split(piece_path, '/');
	ft_strdel(old_path);
	*old_path = ft_strconcat("/", new_path);
	ft_strdel(&new_path);
	ft_free_after_split(piece_path);
	free(piece_path);
}
