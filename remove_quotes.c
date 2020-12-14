/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:40:47 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:42:29 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_help_find_len(char *str, char c)
{
	int i;
	int new_len;
	int len;

	len = ft_strlen(str);
	new_len = len + 1;
	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			new_len--;
		i++;
	}
	return (new_len);
}

char	*ft_remove_this_quotes(char *str, char c)
{
	int		new_len;
	char	*new_str;
	int		i;
	int		new_i;

	if (str[0] != c && str[ft_strlen(str) - 1] != c)
	{
		new_str = ft_strdup(str);
		return (new_str);
	}
	new_len = ft_help_find_len(str, c);
	new_str = (char *)malloc(sizeof(char) * new_len);
	i = 0;
	new_i = 0;
	while (new_i < new_len - 1)
	{
		if (str[i] != c)
		{
			new_str[new_i] = str[i];
			new_i++;
		}
		i++;
	}
	new_str[new_i] = '\0';
	return (new_str);
}

char	*ft_remove_all_quotes(char *str)
{
	char *new_str;
	char *no_quotes_str;

	if (!str)
		return (NULL);
	new_str = ft_remove_this_quotes(str, '"');
	no_quotes_str = ft_remove_this_quotes(new_str, '\'');
	ft_strdel(&new_str);
	return (no_quotes_str);
}

char	*ft_remove_quotes_echo(char *str)
{
	char *new_str;

	if (str[0] != '\'' && str[ft_strlen(str) - 1] != '\'' &&
		str[0] != '"' && str[ft_strlen(str) - 1] != '"')
	{
		if (!(new_str = ft_strdup(str)))
			ft_malloc_error();
		return (new_str);
	}
	if (str[0] == '\'' || str[ft_strlen(str) - 1] == '\'')
	{
		new_str = ft_remove_this_quotes(str, '\'');
	}
	else
	{
		new_str = ft_remove_this_quotes(str, '"');
	}
	return (new_str);
}
