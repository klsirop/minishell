/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:52:26 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/29 18:54:29 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_chrtoa_ostssrk(unsigned int chr)
{
	char str[5];
	ft_bzero(str, 5);
	if (chr < 128)
		str[0] = chr;
	else if (chr < 2048)
	{
		str[0] = (unsigned char)(chr >> 6) + 0xc0;
		str[1] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}
	else if (chr < 65536 && (chr < 55296 || chr > 57343))
	{
		str[0] = (unsigned char)(chr >> 12) + 0xe0;
		str[1] = (unsigned char)((chr >> 6) & 0x0000003f) + 0x80;
		str[2] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}
	else if (chr > 65535)
	{
		str[0] = (unsigned char)((chr >> 18) & 0x00000007) + 0xf0;
		str[1] = (unsigned char)((chr >> 12) & 0x0000003f) + 0x80;
		str[2] = (unsigned char)((chr >> 6) & 0x0000003f) + 0x80;
		str[3] = (unsigned char)(chr & 0x0000003f) + 0x80;
	}
	return (ft_strdup(str));
}