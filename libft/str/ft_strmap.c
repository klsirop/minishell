/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:34:09 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/13 21:22:55 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		len;
	char	*fresh;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	fresh = (char *)malloc((len + 1) * sizeof(char));
	if (!fresh)
		return (NULL);
	while (*s != '\0')
	{
		fresh[i] = f(*s);
		s++;
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
