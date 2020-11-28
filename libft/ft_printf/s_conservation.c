/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_conservation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:19:31 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:22:44 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_crop(char *str, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = (char *)malloc((size_t)(len + 1))))
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int		ft_strwid(char **str, t_flags *param, int len)
{
	char	*tmp;
	char	*s;

	if (len < param->wid)
	{
		if (!(tmp = ft_strnew((size_t)(param->wid - len + 1))))
			return (0);
		if (param->flags != NULL && ft_strchr(param->flags, '0')
			&& !ft_strchr(param->flags, '-'))
			ft_memset(tmp, '0', (size_t)(param->wid - len));
		else
			ft_memset(tmp, ' ', (size_t)(param->wid - len));
		if (param->flags != NULL && ft_strchr(param->flags, '-'))
			s = ft_append(*str, tmp);
		else
			s = ft_prepend(*str, tmp);
		if (s == NULL)
			return (0);
		ft_strdel(&tmp);
		ft_strdel(str);
		if (!(*str = ft_strdup(s)))
			return (0);
		ft_strdel(&s);
	}
	return (1);
}

int		ft_spres(t_flags *param, char **str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*str);
	if (param->pres > -1 && param->pres < len)
	{
		if (!(tmp = ft_crop(*str, param->pres)))
			return (0);
		ft_strdel(str);
		if (!(*str = ft_strdup(tmp)))
			return (0);
		ft_strdel(&tmp);
	}
	return (1);
}

int		s_con(t_flags *param, va_list *arg)
{
	char	*str;
	int		len;
	char	*get;

	if (param->size != NULL && !ft_strcmp(param->size, "l"))
		return (s_big(param, arg));
	get = va_arg(*arg, char *);
	if (get == NULL)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(get);
	if (!str)
		return (0);
	if (!ft_spres(param, &str))
		return (del(&str));
	if (!ft_strwid(&str, param, ft_strlen(str)))
		return (del(&str));
	ft_putstr(str);
	len = ft_strlen(str);
	ft_strdel(&str);
	return (len);
}
