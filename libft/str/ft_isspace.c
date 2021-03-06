/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 10:36:10 by jmaynard          #+#    #+#             */
/*   Updated: 2018/12/14 10:39:13 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\f')
		return (1);
	else if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}
