/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 20:34:08 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_arr_env(char ***arr, t_env *env) {
	int len;
	int i;
	t_env *tmp;
	
	len = ft_find_list_len(env);
	(*arr) = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	tmp = env;
	while (i < len) {
		(*arr)[i] = ft_strconcat_delim(tmp->name, tmp->content, "=");
		tmp = tmp->next;
		i++;
	}
	(*arr)[i] = NULL;
}

char *ft_check_path_access(char *command, t_env *env) {
	t_env *path;
	char **path_parts;
	int i;
	char *new_exe;

	path = ft_find_in_list(env, "PATH");
	if (!path || !(path->content))
		return (NULL);
	path_parts = ft_strsplit(path->content, ':');
	i = 0;
	while (path_parts[i]) {
		new_exe = ft_concat_path(path_parts[i], command);
		if (!access(new_exe, 0)) {
			ft_free_after_split(path_parts);
			ft_strdel(path_parts);
			return new_exe;
		}
		ft_strdel(&new_exe);
		i++;
	}
	ft_free_after_split(path_parts);
	free(path_parts);
	return (NULL);
}

// free: arr_env, after_substitution
// exit_stat - what returns execve or else

// no exists exec - 127
int	ft_do_process(char **command, t_env **env, uint8_t *exit_stat) {
	pid_t pid;
	pid_t wpid;
	char **arr_env;
	int status;
	char *new_exe;
	char *contant_no_quotes;
	char *after_substitution;

	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	pid = fork();
	if (pid == -1) {
		ft_error();
	}
	else if (pid == 0) {
		contant_no_quotes = ft_remove_all_quotes(command[0]);
		after_substitution = ft_substitution(contant_no_quotes, *env);
		ft_strdel(&contant_no_quotes);
		
		if (!access(after_substitution, 0)) { //exists
			if (!access(after_substitution, 1)) { //execute
				execve(after_substitution, command, arr_env);
			} else {
				*exit_stat = PERMISSION_DENIED;
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " permission denied: " DROP "%s\n", after_substitution);
			}
			ft_strdel(&after_substitution);
			ft_free_after_split(arr_env);
			free(arr_env);
			arr_env = NULL;
			exit(0);
		} else {
			new_exe = ft_check_path_access(after_substitution, *env);////
			if (new_exe) {
				if (!access(new_exe, 1)) { //execute
					ft_strdel(&(after_substitution));
					after_substitution = ft_strdup(new_exe);
					ft_strdel(&new_exe);
					execve(after_substitution, command, arr_env);
				} else {
					*exit_stat = PERMISSION_DENIED;
					ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " permission denied:" DROP " %s\n", after_substitution);
				}
				ft_strdel(&after_substitution);
				ft_free_after_split(arr_env);
				free(arr_env);
				arr_env = NULL;
				exit(0);
			} else { //not exists
				*exit_stat = NOT_EXISTS;
				ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " command not found:" DROP " %s\n", after_substitution);
				ft_strdel(&after_substitution);
				ft_free_after_split(arr_env);
				free(arr_env);
				arr_env = NULL;
				ft_strdel(&new_exe);
				exit(0);
			}
		}
	}
	wait(&pid);
	ft_free_after_split(arr_env);
	free(arr_env);
	return (0);
}