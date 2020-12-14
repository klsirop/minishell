/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 18:48:51 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_do_fork(char **after_substitution, char **command,
						char ***arr_env, char **new_exe)
{
	int status;

	g_pid = fork();
	if (g_pid == -1)
		ft_error();
	else if (g_pid == 0)
	{
		if (!access(*after_substitution, 0))
			ft_file_exists(after_substitution, command, arr_env);
		else
			ft_exists_in_path(new_exe, after_substitution, command, *arr_env);
		ft_strdel(new_exe);
		exit(0);
	}
	wait(&status);
}

uint8_t		ft_perm(char **after_substitution, char ***arr_env,
					char **new_exe, uint8_t *exit_stat)
{
	*exit_stat = PERMISSION_DENIED;
	ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD
		" permission denied: " DROP "%s\n", *after_substitution);
	ft_strdel(after_substitution);
	ft_free_after_split(*arr_env);
	ft_strdel(new_exe);
	return (*exit_stat);
}

uint8_t		ft_file_not_exists(char **after_substitution, char **command,
							char ***arr_env, t_env **env)
{
	uint8_t exit_stat;
	char	*new_exe;

	exit_stat = -1;
	new_exe = ft_check_path_access(*after_substitution, *env);
	if (new_exe || (!access(*after_substitution, 0)))
	{
		if (((!access(*after_substitution, 0)) &&
			access(*after_substitution, 1)) || (new_exe && access(new_exe, 1)))
			return (ft_perm(after_substitution, arr_env, &new_exe, &exit_stat));
		ft_do_fork(after_substitution, command, arr_env, &new_exe);
	}
	else
	{
		exit_stat = NOT_EXISTS;
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP
			BOLD " command not found:" DROP " %s\n", *after_substitution);
	}
	ft_strdel(&new_exe);
	ft_strdel(after_substitution);
	ft_free_after_split(*arr_env);
	return (exit_stat);
}

void		ft_child(char **command, t_env **env,
				char **arr_env, uint8_t *exit_stat)
{
	char	*contant_no_quotes;
	char	*after_substitution;
	int		ex;

	contant_no_quotes = ft_remove_all_quotes(command[0]);
	after_substitution = ft_substitution(contant_no_quotes, *env);
	ft_strdel(&contant_no_quotes);
	ex = ft_file_not_exists(&after_substitution, command, &arr_env, env);
	if (ex != -1)
		*exit_stat = ex;
}

int			ft_do_process(char **command, t_env **env, uint8_t *exit_stat)
{
	char	**arr_env;

	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	ft_child(command, env, arr_env, exit_stat);
	ft_free_after_split(arr_env);
	if (arr_env)
		free(arr_env);
	return (0);
}
