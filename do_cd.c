/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:18:03 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:36:24 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_dir_status(struct stat	status, char *dest_dir)
{
	if (S_ISDIR(status.st_mode & S_IFMT))
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD " cd: " DROP
						"permission denied:" DROP " %s\n", dest_dir);
	else if (S_ISLNK(status.st_mode & S_IFMT))
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD " cd: " DROP
				"too many levels of symbolic links:" DROP " %s\n", dest_dir);
	else
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD " cd: " DROP
										"not a directory: %s\n", dest_dir);
}

int		ft_cd_go_to(t_env **env, char *dest_dir)
{
	char		*new_path;
	struct stat	status;
	t_env		*tmp;

	tmp = ft_find_in_list(*env, "PWD");
	if (!tmp || !(tmp->content) || !ft_strcmp(tmp->content, ""))
		return (1);
	new_path = ft_get_full_new_pwd(tmp->content, dest_dir, *env);
	if (chdir(new_path) == -1)
	{
		if (!lstat(new_path, &status))
			ft_check_dir_status(status, dest_dir);
		else
			ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD " cd: " DROP
							"no such file or directory: %s\n", dest_dir);
		ft_strdel(&new_path);
		return (1);
	}
	ft_change_oldpwd_and_pwd(env, dest_dir);
	ft_strdel(&new_path);
	return (0);
}

int		ft_do_cd_help(char **command_parts, t_env **env)
{
	t_env	*tmp;
	char	*content;
	char	*contant_no_quotes;
	char	*after_substitution;
	int		ret_code;

	ret_code = 0;
	if (!ft_strcmp(command_parts[1], "-"))
	{
		tmp = ft_find_in_list(*env, "OLDPWD");
		if (tmp && tmp->content)
		{
			if (!(content = ft_strdup(tmp->content)))
				ft_malloc_error();
			ret_code = ft_cd_go_to(env, content);
			ft_strdel(&content);
		}
		return (ret_code);
	}
	contant_no_quotes = ft_remove_all_quotes(command_parts[1]);
	after_substitution = ft_substitution(contant_no_quotes, *env);
	ret_code = ft_cd_go_to(env, after_substitution);
	ft_strdel(&contant_no_quotes);
	ft_strdel(&after_substitution);
	return (ret_code);
}

int		ft_do_cd(char **command_parts, t_env **env)
{
	if (command_parts[1] && command_parts[2])
	{
		ft_printf(GREEN_FON "minishell:" DROP BOLD
					" cd: " DROP "too many arguments\n");
		return (1);
	}
	if (command_parts[1] == NULL || !ft_strcmp(command_parts[1], "~"))
		return (ft_go_to_home_dir(env));
	if (command_parts[1] && command_parts[2] == NULL)
	{
		if (!ft_strcmp(command_parts[1], "."))
			return (0);
		return (ft_do_cd_help(command_parts, env));
	}
	return (0);
}
