/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:47:03 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 20:46:39 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_do_command(char *command, t_env **myenv, uint8_t *exit_stat) {
	char **command_parts;
	int ret;

	command_parts = NULL;
	if (!(command_parts = ft_strsplit_sh(command, ' ', '\t')))
		ft_error();
	
	if (!command_parts)
		return (0);
	if (!command_parts[0]) {
		free(command_parts);
		return (0);
	}
	else if (!ft_strcmp(command_parts[0], "echo"))
		ft_do_echo(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "env"))
		ft_print_env(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "setenv"))
		ft_do_setenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "exit")) {
		ret = ft_do_exit(command_parts, exit_stat);
		ft_free_after_split(command_parts);
		free(command_parts);
		return (ret);
	}
	else if (!ft_strcmp(command_parts[0], "clear"))
		ft_do_clear(command_parts);
	else if (!ft_strcmp(command_parts[0], "unsetenv"))
		ft_do_unsetenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "help"))
		ft_do_help(command_parts);
	else if (!ft_strcmp(command_parts[0], "cd")) {
		*exit_stat = ft_do_cd(command_parts, myenv);
		ft_free_after_split(command_parts);
		free(command_parts);
		return (0);
	}
	else if (!ft_strcmp(command_parts[0], "iamgay"))
		ft_iamgay(command_parts);
	else if (!ft_strcmp(command_parts[0], "iambi"))
		ft_iambi(command_parts);
	else {
		ft_do_process(command_parts, myenv, exit_stat);
		ft_free_after_split(command_parts);
		free(command_parts);
		return (0);
	}
	*exit_stat = 0;
	ft_free_after_split(command_parts);
	free(command_parts);
	return (0);
}