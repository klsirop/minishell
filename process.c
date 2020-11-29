/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 19:16:13 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/29 20:49:20 by volyvar-         ###   ########.fr       */
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
#include <errno.h>
void	ft_do_process(char **command, t_env **env) {
	pid_t pid;
	pid_t wpid;
	char **arr_env;
	int status;

	// ft_printf("\t\t\t com: %s\n", command[0]);
	arr_env = NULL;
	ft_create_arr_env(&arr_env, *env);
	pid = fork();
	if (pid == -1) {
		ft_error();
	}
	else if (pid == 0) {
		// execve(command[0], command, arr_env);
		if (!access(command[0], 1)) {
			if (execve(command[0], command, arr_env) == -1) {
				ft_error();
			}
		} else {
			// check acces by each part of path and launch with concat part_path+command[0]
			ft_printf("no access\n");
		}
	}
	// } else {
	// 	status = 0;
	// 	while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
	// 		wpid = waitpid(pid, &status, WUNTRACED);
	// 	}
	// }
	wait(&pid);
	ft_free_after_split(arr_env);
	ft_strdel(arr_env);
}