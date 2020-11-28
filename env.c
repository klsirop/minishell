/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:01:33 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/28 22:48:50 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_origin_env(t_env **myenv, char **env) {
	int i;
	char **parse_env;

	i = 0;
	while (env[i] != NULL) {
		if (!(parse_env = ft_strsplit(env[i], '=')))
			ft_error();
		if (!parse_env[0] || !parse_env[1])
			ft_error();
		ft_list_add(myenv, parse_env[0], parse_env[1]);
		ft_free_after_split(parse_env);
		ft_strdel(parse_env);
		i++;
	}
}

void	ft_print_env(t_env *myenv) {
	t_env *tmp;

	// ft_printf("\n");
	tmp = myenv;
	while (tmp) {
		ft_printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

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

char *ft_create_str_from_split(char **arr) {
	int len;
	int i;
	char *str;
	int j;
	int k;

	len = 0;
	i = 0;
	while (arr[i] != NULL) {
		len += ft_strlen(arr[i]);
		i++;
	}
	str = (char *)malloc(sizeof(char) * (len + i + 1));
	i = 0;
	k = 0;
	while (arr[i] != NULL) {
		j = 0;
		while (arr[i][j] != '\0') {
			str[k] = arr[i][j];
			j++;
			k++;
		}
		i++;
		if (arr[i] != NULL) {
			str[k] = ':';
			k++;
		}
	}
	str[k] = '\0';
	return str;
}

char *ft_substitution(char *str, t_env *env) {
	char *new_str;
	char **parts;
	int i;
	char *tmp;

	if (!str || !env)
		return (NULL);
	if (!ft_strchr(str, ':') && str[0] != '$') {
		new_str = ft_strdup(str);
		return (new_str);
	}
	if (str[0] == '$' && !ft_strchr(str, ':')) {
		new_str = ft_find_var(str, env);
		return (new_str);
	}
	if (ft_strchr(str, ':')) {
		parts = ft_strsplit(str, ':');
		i = 0;
		while (parts[i] != NULL) {
			if (parts[i][0] == '$') {
				tmp = ft_find_var(parts[i], env);
				ft_strdel(&(parts[i]));
				parts[i] = ft_strdup(tmp);
				ft_strdel(&tmp);
			}
			i++;
		}
		new_str = ft_create_str_from_split(parts);
		ft_free_after_split(parts);
		ft_strdel(parts);
		return new_str;
	}
	new_str = ft_strdup(str);
	return (new_str);
}

void	ft_do_setenv(char **command_parts, t_env **env) {
	char *contant_no_quotes;
	char *after_substitution;
	t_env *is_exists;

	if (command_parts[1] == NULL || command_parts[2] == NULL || command_parts[3] != NULL) {
		ft_printf("usage: setenv [name] [value]\n");
		return ;
	}
	contant_no_quotes = ft_remove_quotes(command_parts[2]);
	after_substitution = ft_substitution(command_parts[2], *env);
	is_exists = ft_find_in_list(*env, command_parts[1]);
	if (is_exists == NULL)
		ft_list_add(env, command_parts[1], after_substitution);
	else {
		ft_strdel(&is_exists->content);
		is_exists->content = ft_strdup(after_substitution);
	}
	ft_strdel(&after_substitution);
	ft_strdel(&contant_no_quotes);
}

void	ft_do_unsetenv(char **command_parts, t_env **env) {
	if (command_parts[1] == NULL || command_parts[2] != NULL) {
		ft_printf("usage: unsetenv [name]\n");
		return ;
	}
	ft_list_delete_element_name(env, command_parts[1]);
}
