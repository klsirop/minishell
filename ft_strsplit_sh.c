/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_sh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:10:36 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 21:28:30 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int		ft_count(const char *s, char c)
{
	int cnt;

	cnt = 0;
	if (*s != c)
	{
		s++;
		cnt++;
	}
	while (*s != '\0')
	{
		if (*s != c && *(s - 1) == c)
			cnt++;
		s++;
	}
	return (cnt);
}

static char		**ft_del(char ***ptr)
{
	while (**ptr)
	{
		free(**ptr);
		(**ptr)++;
	}
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char			**ft_strsplit_sh(char const *s, char c, char c1)
{
	char	**ptr;
	char	*word;
	int		i;

	i = 0;
	if (!s || !c || !c1 ||
		!(ptr = (char **)malloc((ft_count(s, c) +
			ft_count(s, c1) + 1) * sizeof(char *))))
		return (NULL);
	word = (char *)s;
	while (*s)
	{
		if (*s == c || *s == c1)
		{
			if (word != s)
				if (!(ptr[i++] = ft_strsub(word, 0, s - word)))
					return (ft_del(&ptr));
			word = (char *)s + 1;
		}
		s++;
	}
	if (word != s)
		ptr[i++] = ft_strsub(word, 0, s - word);
	ptr[i] = NULL;
	return (ptr);
}
