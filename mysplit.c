/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:34:58 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/30 21:35:55 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static	int				ft_find_words(char const *s, char c)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (((char)s[i] == c) && (s[i] != '\0'))
			i++;
		if (((char)s[i] != c) && (s[i] != '\0'))
		{
			while (((char)s[i] != c) && (s[i] != '\0'))
				i++;
			words++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (words);
}

static	int				ft_find_len(const char *s, int word, char c)
{
	int		i;
	int		w;
	int		j;

	w = 0;
	i = 0;
	while (w < word)
	{
		while ((char)s[i] == c)
			i++;
		if ((char)s[i] != c)
		{
			if (w == word - 1)
				j = i;
			while (((char)s[i] != c) && (s[i] != '\0'))
				i++;
			w++;
		}
	}
	return (i - j + 1);
}

static	char			*ft_find_slovo(char const *s, int word, char c)
{
	int		i;
	int		w;
	int		j;
	char	*slovo;

	slovo = (char *)malloc(sizeof(char) * ft_find_len(s, word, c));
	if (slovo)
	{
		w = 1;
		i = 0;
		while ((s[i] != '\0') && (w <= word))
		{
			while (((char)s[i] == c) && (s[i] != '\0'))
				i++;
			while (((char)s[i] != c) && (s[i] != '\0') && (w < word))
				i++;
			w++;
		}
		j = 0;
		while (j < ft_find_len(s, word, c) - 1)
			slovo[j++] = s[i++];
		slovo[j] = '\0';
	}
	return (slovo);
}

static void				ft_clean(char **arr, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(*(arr + i));
		i++;
	}
}

char					**ft_strsplit_my(char const *s, char c)
{
	char	**arr;
	int		i;

	if (s)
		arr = (char **)malloc(sizeof(char *) * (ft_find_words(s, c) + 1));
	if (s && arr)
	{
		i = 0;
		while (i < ft_find_words(s, c))
		{
			arr[i] = (char *)malloc(sizeof(char) * ft_find_len(s, i + 1, c));
			if (arr[i])
				arr[i] = ft_find_slovo(s, i + 1, c);
			else
			{
				ft_clean(arr, i);
				arr = NULL;
				break ;
			}
			i++;
		}
		arr[i] = NULL;
	}
	return (arr);
}