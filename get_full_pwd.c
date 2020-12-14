/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:19:09 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:41:21 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_home_path(t_env *env, char **piece_path, char **full_pwd)
{
	t_env	*tmp_env;
	char	*home;
	char	*tmp;

	tmp_env = ft_find_in_list(env, "HOME");
	if (!tmp_env || !(tmp_env->content) || !ft_strcmp(tmp_env->content, ""))
	{
		ft_free_after_split(piece_path);
		free(piece_path);
		return (1);
	}
	if (!(home = ft_strdup(tmp_env->content)))
		ft_malloc_error();
	if (!(tmp = ft_strdup(home)))
		ft_malloc_error();
	ft_strswap(full_pwd, &tmp);
	ft_strdel(&home);
	return (0);
}

int		ft_get_part_pwd(char **full_pwd, t_env *env,
						char *piece, char **piece_path)
{
	char	*tmp;

	if (!ft_strcmp(piece, ".."))
		ft_path_step_back(full_pwd);
	else if (!ft_strcmp(piece, "~"))
	{
		if (ft_home_path(env, piece_path, full_pwd))
			return (1);
	}
	else
	{
		tmp = ft_concat_path(*full_pwd, piece);
		ft_strswap(full_pwd, &tmp);
	}
	return (0);
}

char	*ft_get_full_new_pwd(char *old_pwd, char *new_pwd, t_env *env)
{
	char	**piece_path;
	char	*full_pwd;
	int		i;

	piece_path = ft_strsplit(new_pwd, '/');
	i = 0;
	if (new_pwd[0] != '/')
		full_pwd = ft_strdup(old_pwd);
	else
		full_pwd = ft_strdup("/");
	while (piece_path[i])
	{
		if (!ft_strcmp(piece_path[i], "."))
		{
			i++;
			continue;
		}
		if (ft_get_part_pwd(&full_pwd, env, piece_path[i], piece_path))
			return (full_pwd);
		i++;
	}
	ft_free_after_split(piece_path);
	free(piece_path);
	return (full_pwd);
}
