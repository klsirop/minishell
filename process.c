/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 16:38:32 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_exists(char **after_substitution, char **command,
						char ***arr_env, uint8_t *exit_stat)
{
	if (!access(*after_substitution, 1))
		execve(*after_substitution, command, *arr_env);
	else
	{
		*exit_stat = PERMISSION_DENIED;
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD
				" permission denied: " DROP "%s\n", *after_substitution);
	}
	ft_strdel(after_substitution);
	ft_free_after_split(*arr_env);
	free(*arr_env);
	*arr_env = NULL;
	exit(0);
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
	else
	{
		exit_stat = PERMISSION_DENIED;
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP BOLD
					" permission denied:" DROP " %s\n", *after_substitution);
	}
	return (exit_stat);
}

int		ft_file_not_exists(char **after_substitution, char **command,
							char ***arr_env, t_env **env)
{
	uint8_t exit_stat;
	char	*new_exe;
	int		ex;

	exit_stat = -1;
	new_exe = ft_check_path_access(*after_substitution, *env);
	if (new_exe)
	{
		ex = ft_exists_in_path(&new_exe, after_substitution, command, *arr_env);
		if (ex != -1)
			exit_stat = ex;
	}
	else
	{
		exit_stat = NOT_EXISTS;
		ft_fprintf(2, "\a" GREEN_FON "minishell:" DROP
			BOLD " command not found:" DROP " %s\n", *after_substitution);
		ft_strdel(&new_exe);
	}
	ft_strdel(after_substitution);
	ft_free_after_split(*arr_env);
	free(*arr_env);
	*arr_env = NULL;
	return (exit_stat);
}

void	ft_child(char **command, t_env **env,
				char **arr_env, uint8_t *exit_stat)
{
	char	*contant_no_quotes;
	char	*after_substitution;
	int		ex;

	contant_no_quotes = ft_remove_all_quotes(command[0]);
	after_substitution = ft_substitution(contant_no_quotes, *env);
	ft_strdel(&contant_no_quotes);
	if (!access(after_substitution, 0))
		ft_file_exists(&after_substitution, command, &arr_env, exit_stat);
	else
	{
		ex = ft_file_not_exists(&after_substitution, command, &arr_env, env);
		if (ex != -1)
			*exit_stat = ex;
		exit(0);
	}
}

int		ft_do_process(char **command, t_env **env, uint8_t *exit_stat)
{
	char	**arr_env;
	int		status;

	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	g_pid = fork();
	if (g_pid == -1)
		ft_error();
	else if (g_pid == 0)
	{
		ft_child(command, env, arr_env, exit_stat);
	}
	wait(&status);
	ft_free_after_split(arr_env);
	free(arr_env);
	return (0);
}
