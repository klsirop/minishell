/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:37:00 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/20 20:16:03 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhite(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	ft_last(const char *s)
{
	int max;
	int i;

	i = 0;
	max = 0;
	while (s[i] != '\0')
	{
		if (!(ft_iswhite(s[i])))
			max = i;
		i++;
	}
	return (max);
}

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	n = ft_last(s);
	while (s[i] != '\0' && ft_iswhite(s[i]))
		i++;
	if (n == 0)
		n = i - 1;
	if (!(tmp = (char *)malloc(sizeof(char) * (n - i + 1))))
		return (NULL);
	while (s[i] != '\0' && i <= n)
	{
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
