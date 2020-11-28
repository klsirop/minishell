/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:58:10 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/28 23:14:06 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_find_var(char *str, t_env *env) {
	t_env *tmp;
	char *var;

	var = NULL;
	tmp = env;
	while (tmp) {
		if (!(ft_strcmp(tmp->name, (str + 1)))) {
			var = ft_strdup(tmp->content);
			return var;
		}
		tmp = tmp->next;
	}
	if (var == NULL)
		var = ft_strdup("");
	return (var);
}

void	ft_do_echo(char **command_parts, t_env *env) {
	int i;
	char *var;
	int is_first;
	int was_print;
	char *no_quotes;
	
	// ft_printf("\n");
	is_first = 1;
	i = 1;
	was_print = 0;
	while (command_parts[i] != NULL) {
		if (!is_first && was_print)
			ft_printf(" ");
		else
			is_first = 0;

		no_quotes = ft_remove_quotes(command_parts[i]);
		// check VAR
		if (no_quotes[0] == '$' && no_quotes[1] != '\0') {
			var = ft_find_var(no_quotes, env);
			if (!ft_strcmp(var, ""))
				was_print = 0;
			else
				was_print = 1;
			ft_printf("%s", var);
			ft_strdel(&var);
		} else {
			ft_printf("%s", no_quotes);
			was_print = 1;
		}
		ft_strdel(&no_quotes);
		i++;
	}
	ft_printf("\n");
}

void	ft_do_clear() {
	ft_putstr("\033[?1049h\033[H");
}

void	ft_do_help() {
	ft_printf("usage:\n");
	ft_printf("	echo [argc]\n");
	ft_printf("	env\n");
	ft_printf("	setenv [name] [var]\n");
	ft_printf("	unsetenv [name]\n");
	ft_printf("	clear\n");
	ft_printf("	help\n");
	ft_printf("	cd [argc]\n");
	ft_printf("	exit\n");
}
