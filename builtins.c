/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:58:10 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/01 20:58:52 by volyvar-         ###   ########.fr       */
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

void	ft_do_clear(char **command) {
	if (command[1] != NULL) {
		ft_fprintf(2, BOLD ITALIC GREEN_FON BLACK_TEXT "minishell:" DROP BOLD " clear: " DROP "too many arguments\n");
		return ;
	}
	ft_putstr(CLEAR);//////////////////////////////
}

void	ft_do_help(char **command) {
	if (command[1] == NULL) {
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP "\n");
		ft_printf("\t" BOLD "echo " DROP "[argc]\n");
		ft_printf("\t" BOLD "env" DROP "\n");
		ft_printf("\t" BOLD "setenv " DROP "name var\n");
		ft_printf("\t" BOLD "unsetenv " DROP "name\n");
		ft_printf("\t" BOLD "clear" DROP "\n");
		ft_printf("\t" BOLD "help " DROP "[command_name]\n");
		ft_printf("\t" BOLD "cd " DROP "[argc]\n");
		ft_printf("\t" BOLD "exit" DROP "\n");
		return ;
	}
	if (command[1] != NULL && command[2] != NULL) {
		ft_fprintf(2, BOLD ITALIC GREEN_FON BLACK_TEXT "minishell:" DROP BOLD " help:" DROP "too many arguments\n");
		return ;
	}
	if (!ft_strcmp(command[1], "echo"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP "\n" BOLD "\techo " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "env"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\tenv" DROP "\n");
	else if (!ft_strcmp(command[1], "setenv"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\tsetenv " DROP "name value\n");
	else if (!ft_strcmp(command[1], "unsetenv"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\tunsetenv " DROP "name\n");
	else if (!ft_strcmp(command[1], "clear"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\tclear" DROP "\n");
	else if (!ft_strcmp(command[1], "help"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\thelp " DROP "[command_name]\n");
	else if (!ft_strcmp(command[1], "cd"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\tcd " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "exit"))
		ft_printf(ITALIC BOLD LIGHT_BLUE_FON BLACK_TEXT "usage:" DROP  "\n" BOLD "\texit" DROP "\n");
	else {
		ft_printf(ITALIC "minishell: " DROP BOLD "help: " DROP "unknown argument\n");
	}
}
