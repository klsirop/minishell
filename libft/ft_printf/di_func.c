/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaynard <jmaynard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 12:46:41 by volyvar-          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:11 by jmaynard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_help_minus(int l, unsigned long long int new_num, char **str, int i)
{
	unsigned long long int	del;
	int						j;

	while (l)
	{
		del = 1;
		j = 0;
		while (j++ < l - 1)
			del = del * 10;
		(*str)[i++] = new_num / del + '0';
		new_num = new_num % del;
		l--;
	}
}

int		ft_plus_symb(char **str, char c, int *val)
{
	char *tmp;

	c++;
	if (!(tmp = ft_strjoin(" ", *str)))
		return (-1);
	free(*str);
	if (!(*str = ft_strdup(tmp)))
	{
		free(tmp);
		tmp = NULL;
		return (-1);
	}
	free(tmp);
	tmp = NULL;
	(*val)++;
	return (0);
}

int		ft_help_app_1(char **str, char c, int *val)
{
	char *tmp;

	if (c == '+')
		if (!(tmp = ft_strjoin("+", *str)))
			return (-1);
	if (c == ' ')
		if (!(tmp = ft_strjoin(" ", *str)))
			return (-1);
	free(*str);
	if (!((*str) = ft_strdup(tmp)))
		return (-1);
	free(tmp);
	tmp = NULL;
	(*val)++;
	return (0);
}

int		ft_help_app_2(char **str, char c, int l, int *i)
{
	while (l)
	{
		(*str)[l] = (*str)[l - 1];
		l--;
	}
	(*str)[*i] = c;
	return (0);
}

int		ft_append_symb(char **str, int *val, int l, char c)
{
	int i;

	i = 0;
	while (i < *val)
	{
		if ((i == 0) && ((*str)[i] != '\0'))
		{
			if (l == *val)
				return (ft_help_app_1(str, c, val));
			else if (l != *val)
				return (ft_help_app_2(str, c, l, &i));
			break ;
		}
		else if ((i != 0) && ((*str)[i] != '\0'))
		{
			(*str)[i - 1] = c;
			break ;
		}
		i++;
	}
	return (0);
}
