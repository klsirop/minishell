/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:49:08 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 18:13:27 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	contant_no_quotes = ft_remove_all_quotes(command_parts[2]);
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
