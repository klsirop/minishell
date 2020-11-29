/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/29 19:57:05 by volyvar-         ###   ########.fr       */
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

void	ft_do_process(char **command, t_env **env) {
	pid_t pid;
	pid_t wpid;
	char **arr_env;
	int status;

	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	pid = fork();
	if (pid == -1) {
		ft_error();
	}
	else if (pid == 0) {
		execve(command[0], command, arr_env);
		// if (execve(command[0], command, arr_env) == -1) {
		// 	ft_printf("ok\n");
		// 	ft_error();
		// }
	} else {
		if (!access(command[0], 1)) {
			status = 0;
			while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
				wpid = waitpid(pid, &status, WUNTRACED);
			}
		} else {
			
		}
	}
}