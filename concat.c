/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:41:44 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/13 18:42:24 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strconcat(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	int		j;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		ft_malloc_error();
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strconcat_delim(char *s1, char *s2, char *delim)
{
	char *tmp;
	char *full;

	tmp = ft_strconcat(s1, delim);
	full = ft_strconcat(tmp, s2);
	ft_strdel(&tmp);
	return (full);
}

char	*ft_concat_path(char *s1, char *s2)
{
	char *path;

	if (!s1 || !s2)
		return (NULL);
	if (s1[ft_strlen(s1) - 1] == '/')
		path = ft_strconcat(s1, s2);
	else
		path = ft_strconcat_delim(s1, s2, "/");
	return (path);
}
