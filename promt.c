/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:40:45 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 19:43:47 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_this_dir(void)
{
	t_env *pwd;

	pwd = ft_find_in_list(g_env, "PWD");
	if (pwd && pwd->content)
		ft_printf(BOLD_PINK "%s " DROP, pwd->content);
}

void		ft_print_promt(void)
{
	ft_print_this_dir();
	ft_printf("%lc ", g_promt);
}

static void	ft_ctrlc(int s)
{
	if (g_pid != 0)
	{
		ft_printf("\n");
		g_pid = 0;
	}
	else
	{
		ft_printf("\n");
		ft_print_promt();
	}
	s = 0;
}

static void	ft_quit(int s)
{
	s = 0;
	ft_printf(UNCLEAR);
	exit(0);
}

void		ft_signal(void)
{
	if (signal(SIGINT, ft_ctrlc))
	{
	}
	if (signal(SIGQUIT, ft_quit))
	{
	}
}
