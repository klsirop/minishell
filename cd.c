/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:59:35 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:36:15 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_or_create_var(t_env **env, char *var_name, char *content)
{
	t_env *tmp;

	tmp = ft_find_in_list(*env, var_name);
	if (tmp)
	{
		if (tmp->content)
			ft_strdel(&(tmp->content));
		if (content)
			if (!(tmp->content = ft_strdup(content)))
				ft_malloc_error();
	}
	else
	{
		ft_list_add(env, var_name, content);
	}
}

void	ft_strswap(char **src, char **tmp)
{
	ft_strdel(src);
	if (!(*src = ft_strdup(*tmp)))
		ft_malloc_error();
	ft_strdel(tmp);
}

void	ft_change_oldpwd_and_pwd(t_env **env, char *new_pwd)
{
	t_env	*pwd;
	char	*full_new_pwd;

	pwd = ft_find_in_list(*env, "PWD");
	if (pwd && pwd->content)
		ft_change_or_create_var(env, "OLDPWD", pwd->content);
	full_new_pwd = ft_get_full_new_pwd(pwd->content, new_pwd, *env);
	ft_change_or_create_var(env, "PWD", full_new_pwd);
	ft_strdel(&full_new_pwd);
}

int		ft_go_to_home_dir(t_env **env)
{
	t_env *home;

	home = ft_find_in_list(*env, "HOME");
	if (home == NULL || home->content == NULL || !ft_strcmp(home->content, ""))
		return (1);
	return (ft_cd_go_to(env, home->content));
}
