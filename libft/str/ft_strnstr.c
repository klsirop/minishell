/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:47:02 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/14 17:53:46 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(const char *str, const char *to_find, size_t len)
{
	size_t i;

	i = 0;
	while (to_find[i] != '\0')
	{
		if (str[i] != to_find[i] || len == 0)
			return (0);
		i++;
		len--;
	}
	return (1);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		flaq;
	int		index;

	i = 0;
	flaq = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (flaq == 0 && haystack[i] != '\0' && len > 0)
	{
		if (haystack[i] == needle[0])
		{
			index = i;
			flaq = ft_find(&haystack[i], &needle[0], len);
		}
		len--;
		i++;
	}
	if (flaq > 0)
		return ((char *)&haystack[index]);
	else
		return (NULL);
}
