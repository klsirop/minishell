/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:05:39 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/12 14:12:36 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len;

	i = -1;
	len = ft_strlen(dst);
	if (len > size)
		return (size + ft_strlen(src));
	while (*dst != '\0')
		dst++;
	while (++i + len < size - 1 && src[i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
	i = ft_strlen(src) + len;
	return (i);
}
