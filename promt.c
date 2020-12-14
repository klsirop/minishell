/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:40:45 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 14:41:54 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_this_dir(void)
{
	t_env *pwd;

	pwd = ft_find_in_list(g_env, "PWD");
	if (pwd && pwd->content)
		ft_printf(BOLD_PINK "%s " DROP, pwd->content);
}

void	ft_print_promt(void)
{
	ft_print_this_dir();
	ft_printf("%lc ", g_promt);
}
