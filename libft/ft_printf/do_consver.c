/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_consver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:32:22 by jmaynard          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:22 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_free_param(t_flags *param)
{
	if (param->flags != NULL)
		ft_strdel(&param->flags);
	if (param->size != NULL)
		ft_strdel(&param->size);
}

void	ft_init(t_flags *param)
{
	param->flags = NULL;
	param->wid = -1;
	param->pres = -1;
	param->size = NULL;
	param->type = -1;
}

int		ft_check(char c)
{
	char *fl;
	char *len;

	fl = ft_strdup("#0- +");
	len = ft_strdup("hlzjL");
	if (ft_strchr(fl, c))
	{
		ft_strdel(&fl);
		ft_strdel(&len);
		return (-1);
	}
	ft_strdel(&fl);
	ft_strdel(&len);
	return (1);
}

int		ft_do(int *val, t_flags *param, char *fmt, va_list *arg)
{
	int ch;

	if (param->type == 10 || param->type == -1)
	{
		ch = ft_check(*fmt);
		if (ch != 1)
			return (ch);
		*val += ft_percent(param, *fmt);
		ft_free_param(param);
		return (1);
	}
	*val += g_func[param->type](param, arg);
	return (1);
}

char	*ft_consver(char *fmt, va_list *arg, int *val)
{
	t_flags		param;
	int			done;

	fmt++;
	ft_init(&param);
	if (!(fmt = ft_flags(fmt, &param)))
		return (NULL);
	if (!(fmt = ft_valid_wid(fmt, &param, arg)))
		return (NULL);
	if (*fmt == '.')
		fmt = ft_valid_pres(fmt, &param, arg);
	if (!(fmt = ft_valid_len("hlLjz", fmt, &param)))
		return (NULL);
	ft_type(fmt, &param);
	while ((done = ft_do(val, &param, fmt, arg)) == -1)
	{
		if (!(fmt = ft_flags(fmt, &param)))
			return (NULL);
		ft_type(fmt, &param);
	}
	if (done)
		fmt++;
	ft_free_param(&param);
	return (fmt);
}
