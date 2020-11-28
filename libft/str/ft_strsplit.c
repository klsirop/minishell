/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:27:45 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/21 13:24:25 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

char			**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	char	*word;
	int		i;

	i = 0;
	if (!s || !c ||
		!(ptr = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *))))
		return (NULL);
	word = (char *)s;
	while (*s)
	{
		if (*s == c)
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
