/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:47:03 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/29 20:21:48 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_do_command(char *command, t_env **myenv) {
	char **command_parts;

	if (!(command_parts = ft_strsplit_sh(command, ' ', '\t')))
		ft_error();
	//
	// ft_printf("\n");
	// int i = 0;
	// while (command_parts[i] != NULL) {
	// 	ft_printf("%s\n", command_parts[i]);
	// 	i++;
	// }
	//
	if (!command_parts)
		return 0;
	else if (!ft_strcmp(command_parts[0], "echo"))
		ft_do_echo(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "env"))
		ft_print_env(*myenv);
	else if (!ft_strcmp(command_parts[0], "setenv"))
		ft_do_setenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "exit"))
		exit(0);
	else if (!ft_strcmp(command_parts[0], "clear"))
		ft_do_clear();
	else if (!ft_strcmp(command_parts[0], "unsetenv"))
		ft_do_unsetenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "help"))
		ft_do_help();
	else if (!ft_strcmp(command_parts[0], "cd"))
		ft_do_cd(command_parts, myenv);
	else
		ft_do_process(command_parts, myenv);

	ft_free_after_split(command_parts);
	ft_strdel(command_parts);
	return (0);////
}