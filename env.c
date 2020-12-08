/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:01:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 17:49:47 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_origin_env(t_env **myenv, char **env) {
	int i;
	char **parse_env;
	t_env *path;

	if (!env)
		return ;

	i = 0;
	while (env[i] != NULL) {
		if (!(parse_env = ft_strsplit(env[i], '=')))
			ft_error();
		if (!parse_env[0])
			ft_error();
		ft_list_add(myenv, parse_env[0], parse_env[1]);
		ft_free_after_split(parse_env);
		free(parse_env);
		i++;
	}
	path = ft_find_in_list(*myenv, "PATH");
	if (path == NULL) {
		ft_list_add(myenv, "PATH", "/usr/bin:/bin");
	}
}

void	ft_print_env(char **command, t_env *myenv) {
	t_env *tmp;

	if (command[1] != NULL) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " env: " DROP "too many arguments\n");
		return ;
	}

	tmp = myenv;
	while (tmp) {
		ft_printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

/*
** take a VAL from VAR=VAL
** VAL can be /volyvar-:$PATH:$PWDddd
** this func substitute variables and VAL will be:
** /volyvar-:/bin:
** PS.	$PWDddd - is unvalid. replace by ""
**	  	VAL shouldn't have any : 
*/
char *ft_substitution(char *str, t_env *env) {
	char *new_str;
	char **parts;
	int i;
	char *tmp;
	t_env *env_tmp;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, ':') && str[0] != '$' && str[0] != '~') {
		new_str = ft_strdup(str);
		return (new_str);
	}
	if (str[0] == '$' && !ft_strchr(str, ':')) {
		new_str = ft_find_var(str, env);
		return (new_str);
	}
	// if (ft_strchr(str, ':')) {
		parts = ft_strsplit(str, ':');
		i = 0;
		while (parts[i] != NULL) {
			if (parts[i][0] == '$') {
				tmp = ft_find_var(parts[i], env);
				ft_strdel(&(parts[i]));
				parts[i] = ft_strdup(tmp);
				ft_strdel(&tmp);
			} 
			else if (parts[i][0] == '~') {
				env_tmp = ft_find_in_list(env, "HOME");
				if (env_tmp) {
					tmp = ft_strdup(env_tmp->content);
					new_str = ft_concat_path(tmp, parts[i] + 2);
					ft_strdel(&(parts[i]));
					ft_strdel(&tmp);
					parts[i] = ft_strdup(new_str);
					ft_strdel(&new_str);
				}
			}
			i++;
		}
		new_str = ft_create_str_from_split(parts, ':');
		ft_free_after_split(parts);
		free(parts);
		return new_str;
	// }
	// new_str = ft_strdup(str);
	// return (new_str);
}
