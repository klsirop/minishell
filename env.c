/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:01:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/06 20:20:45 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_origin_env(t_env **myenv, char **env) {
	int i;
	char **parse_env;

	if (!env)
		return ;

	i = 0;
	while (env[i] != NULL) {
		if (!ft_strcmp(env[i], "PATH=")) {
			ft_strdel(&env[i]);
			env[i] = ft_strdup("/usr/bin:/bin");
		}
		if (!(parse_env = ft_strsplit(env[i], '=')))
			ft_error();
		if (!parse_env[0])
			ft_error();
		ft_list_add(myenv, parse_env[0], parse_env[1]);
		ft_free_after_split(parse_env);
		free(parse_env);
		i++;
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
** remove " at the begin of str
** remove " at the end of str
** if they exists
*/
char *ft_remove_quotes(char *str) {
	int new_len;
	char *new_str;
	int i;
	int new_i;

	new_len = ft_strlen(str) + 1;
	if (str[0] == '"')
		new_len--;
	if (str[ft_strlen(str) - 1] == '"')
		new_len--;
	if (!(new_str = (char *)malloc(sizeof(char) * new_len)))
		ft_malloc_error();
	i = 0;
	new_i = 0;
	while (str[i] != '\0'){
		if (!((i == 0 && str[i] == '"') || (i == ft_strlen(str) - 1 && str[i] == '"'))) {
			new_str[new_i] = str[i];
			new_i++;
		}
		i++;
	}
	new_str[new_i] = '\0';
	return new_str;
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

	if (!str || !env)
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
				tmp = ft_strdup(ft_find_in_list(env, "HOME")->content);
				new_str = ft_concat_path(tmp, parts[i] + 2);
				ft_strdel(&(parts[i]));
				ft_strdel(&tmp);
				parts[i] = ft_strdup(new_str);
				ft_strdel(&new_str);
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

int		ft_is_valid_var_name(char *name) {
	int i;
	int letter;

	i = 0;
	letter = 0;
	while (name[i]) {
		if (name[i] >= 'A' && name[i] <= 'Z')
			letter++;
		i++;
	}
	if (letter > 0)
		return (1);
	return (0);
}

void	ft_do_setenv(char **command_parts, t_env **env) {
	char *contant_no_quotes;
	char *after_substitution;
	t_env *is_exists;

	if (command_parts[1] == NULL) {
		ft_print_env(command_parts, *env);
		return ;
	}
	if (!ft_is_valid_var_name(command_parts[1])) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " setenv: " DROP "not an identifier: %s\n", command_parts[1]);
		return ;
	}
	if (command_parts[2] == NULL || command_parts[3] != NULL) {
		ft_fprintf(2, BOLD ITALIC BLUE_FON "usage:" DROP "\n" BOLD "\tsetenv " DROP "name value\n");
		return ;
	}
	contant_no_quotes = ft_remove_quotes(command_parts[2]);
	after_substitution = ft_substitution(contant_no_quotes, *env);
	ft_change_or_create_var(env, command_parts[1], after_substitution);
	ft_strdel(&after_substitution);
	ft_strdel(&contant_no_quotes);
}

void	ft_do_unsetenv(char **command_parts, t_env **env) {
	int i;

	if (command_parts[1] == NULL) {
		ft_fprintf(2, BOLD ITALIC BLUE_FON "usage:" DROP "\n" BOLD "\tunsetenv " DROP "name\n");
		return ;
	}
	i = 1;
	while (command_parts[i]) {
		ft_list_delete_element_name(env, command_parts[i]);
		i++;
	}
}
