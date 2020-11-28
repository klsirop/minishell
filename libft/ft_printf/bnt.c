/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 10:26:33 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:19:48 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_sum_h(char *big, char *src, int *lb, int *des)
{
	char *tmp;

	while (*lb >= 0)
	{
		if (big[*lb] - '0' + *des < 9)
		{
			src[*lb] = big[*lb] + *des;
			*des = 0;
		}
		else
		{
			src[*lb] = (big[*lb] - '0' + *des) % 10 + '0';
			*des = (big[*lb] - '0' + *des) / 10;
		}
		(*lb)--;
	}
	if (*des != 0)
	{
		if (!(tmp = ft_strjoin("1", src)))
			return (NULL);
		ft_strdel(&src);
		return (tmp);
	}
	return (src);
}

int		ft_sum_hh(char *big, char *small, char *src, int *lb)
{
	int ls;
	int des;

	des = 0;
	ls = ft_strlen(small) - 1;
	while (ls >= 0)
	{
		if (big[*lb] - '0' + small[ls] - '0' + des <= 9)
		{
			src[*lb] = big[*lb] - '0' + small[ls] + des;
			des = 0;
		}
		else
		{
			src[*lb] = (big[*lb] - '0' + small[ls] - '0' + des) % 10 + '0';
			des = (big[*lb] - '0' + small[ls] - '0' + des) / 10;
		}
		(ls)--;
		(*lb)--;
	}
	return (des);
}

char	*ft_sum(char *big, char *small)
{
	char	*src;
	int		lb;
	int		des;

	lb = ft_strlen(big);
	if (!(src = (char *)malloc(sizeof(char) * (lb + 1))))
		return (NULL);
	src[lb--] = '\0';
	des = ft_sum_hh(big, small, src, &lb);
	return (ft_sum_h(big, src, &lb, &des));
}

int		ft_diff_h(char **str, char c)
{
	if (*str == NULL)
	{
		if (!(*str = (char *)malloc(sizeof(char) * 2)))
			return (0);
		(*str)[0] = '1';
		(*str)[1] = '\0';
		return (0);
	}
	if (c == 'f')
	{
		ft_strdel(str);
		return (0);
	}
	return (1);
}

int		ft_diff(char c, char **ta_samaya)
{
	static char	*str;
	char		*tmp;

	if (ft_diff_h(&str, c) == 0)
		return (0);
	if (!(tmp = ft_sum(str, str)))
		return (-1);
	ft_strdel(&str);
	if (!(str = ft_strdup(tmp)))
		return (-1);
	ft_strdel(&tmp);
	if (c == '1')
	{
		if (ft_diff_hh(ta_samaya, &str) == -1)
			return (-1);
	}
	return (0);
}
