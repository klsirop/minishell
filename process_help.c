/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:01:37 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 18:29:38 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_arr_env(char ***arr, t_env *env)
{
	int		len;
	int		i;
	t_env	*tmp;

	len = ft_find_list_len(env);
	if (!((*arr) = (char **)malloc(sizeof(char *) * (len + 1))))
		ft_malloc_error();
	i = 0;
	tmp = env;
	while (i < len)
	{
		(*arr)[i] = ft_strconcat_delim(tmp->name, tmp->content, "=");
		tmp = tmp->next;
		i++;
	}
	(*arr)[i] = NULL;
}

char	*ft_check_path_access(char *command, t_env *env)
{
	t_env	*path;
	char	**path_parts;
	int		i;
	char	*new_exe;

	path = ft_find_in_list(env, "PATH");
	if (!path || !(path->content))
		return (NULL);
	path_parts = ft_strsplit(path->content, ':');
	i = 0;
	while (path_parts[i])
	{
		new_exe = ft_concat_path(path_parts[i], command);
		if (!access(new_exe, 0))
		{
			ft_free_after_split(path_parts);
			free(path_parts);
			return (new_exe);
		}
		ft_strdel(&new_exe);
		i++;
	}
	ft_free_after_split(path_parts);
	free(path_parts);
	return (NULL);
}

void	ft_file_exists(char **after_substitution, char **command,
						char ***arr_env)
{
	if (!access(*after_substitution, 1))
		execve(*after_substitution, command, *arr_env);
	ft_strdel(after_substitution);
	ft_free_after_split(*arr_env);
}

int		ft_exists_in_path(char **new_exe, char **after_substitution,
							char **command, char **arr_env)
{
	uint8_t exit_stat;

	exit_stat = -1;
	if (!access(*new_exe, 1))
	{
		ft_strdel(after_substitution);
		if (!(*after_substitution = ft_strdup(*new_exe)))
			ft_malloc_error();
		ft_strdel(new_exe);
		execve(*after_substitution, command, arr_env);
	}
	return (exit_stat);
}
