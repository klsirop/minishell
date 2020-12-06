/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/05 15:41:06 by volyvar-         ###   ########.fr       */
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
	ft_strdel(path_parts);
	return (NULL);
}

int	ft_do_process(char **command, t_env **env) {
	pid_t pid;
	pid_t wpid;
	char **arr_env;
	int status;
	char *new_exe;
	char *contant_no_quotes;
	char *after_substitution;

	// ft_printf("\t\t\t com: %s\n", command[0]);
	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	pid = fork();
	if (pid == -1) {
		ft_error();
	}
	else if (pid == 0) {
		contant_no_quotes = ft_remove_quotes(command[0]);
		after_substitution = ft_substitution(contant_no_quotes, *env);
		ft_strdel(&contant_no_quotes);
		
		// execve(command[0], command, arr_env);
		if (!access(after_substitution, 0)) { //exists
			if (!access(after_substitution, 1)) { //execute
				execve(after_substitution, command, arr_env);
				
			} else {
				ft_fprintf(2, BOLD ITALIC GREEN_FON BLACK_TEXT "minishell:" DROP BOLD " permission denied:" DROP" %s\n", after_substitution);
			}
			ft_strdel(&after_substitution);
			exit(0);
				// ft_error();
			// }
		} else {
			new_exe = ft_check_path_access(after_substitution, *env);
			if (new_exe) {
				if (!access(new_exe, 1)) {
					ft_strdel(&(after_substitution));
					after_substitution = ft_strdup(new_exe);
					ft_strdel(&new_exe);
					execve(after_substitution, command, arr_env);
				} else {
					ft_fprintf(2, BOLD ITALIC GREEN_FON BLACK_TEXT "minishell:" DROP BOLD " permission denied:" DROP " %s\n", after_substitution);
				}
				ft_strdel(&after_substitution);
				exit(0);
			} else {
				ft_fprintf(2, BOLD ITALIC GREEN_FON BLACK_TEXT "minishell:" DROP BOLD " command not found:" DROP " %s\n", after_substitution);
				// ft_free_after_split(arr_env);
				// ft_strdel(arr_env);
				// ft_error();
				ft_strdel(&after_substitution);
				exit(0);
			}
			// check acces by each part of path and launch with concat part_path+command[0]
		}
		ft_strdel(&after_substitution);
	}
	else {
		// wpid = waitpid(pid, &status, WUNTRACED);

		// waitpid(pid, &status, 0);
		// if (status ==)
		//  wait(&pid);
		// status = 0;
		// while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
		// 	wpid = waitpid(pid, &status, WUNTRACED);
		// 	ft_printf("wpid=%d\n", wpid);
		// }
	}
	// if (status == 1)
	// 	return 1;
	wait(&pid);
	ft_free_after_split(arr_env);
	ft_strdel(arr_env);
	return (0);
}