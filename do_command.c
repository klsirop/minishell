/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:47:03 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/06 20:02:54 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_iamgay(char **command) {
	if (command[1] != NULL) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " iamgay: " DROP "too many arguments\n");
		return ;
	}
	if (g_promt == PROMT_GAY) {
		ft_printf("i know\n");
		return ;
	}
	ft_printf("me too 😏\n");
	g_promt = PROMT_GAY;
}

void	ft_iambi(char **command) {
	char *answer;

	if (command[1] != NULL) {
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " iambi: " DROP "too many arguments\n");
		return ;
	}
	if (g_promt == PROMT_SMILE) {
		ft_printf("i know\n");
		return ;
	}
	ft_printf("are you sure? [y/n]\n");
	if (get_next_line(0, &answer) == -1) {
		ft_error();
	}
	if (!ft_strcmp(answer, "y")) {
		g_promt = PROMT_SMILE;
		return ;
	}
	if (!ft_strcmp(answer, "n")) {
		return ;
	}
}

int ft_do_command(char *command, t_env **myenv, uint8_t *exit_stat) {
	char **command_parts;
	int ret;

	command_parts = NULL;
	if (!(command_parts = ft_strsplit_sh(command, ' ', '\t')))
		ft_error();
	
	if (!command_parts)
		return (0);
	else if (!ft_strcmp(command_parts[0], "echo"))
		ft_do_echo(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "env"))
		ft_print_env(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "setenv"))
		ft_do_setenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "exit")) {
		return (ft_do_exit(command_parts, exit_stat));
	}
	else if (!ft_strcmp(command_parts[0], "clear"))
		ft_do_clear(command_parts);
	else if (!ft_strcmp(command_parts[0], "unsetenv"))
		ft_do_unsetenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "help"))
		ft_do_help(command_parts);
	else if (!ft_strcmp(command_parts[0], "cd")) {
		*exit_stat = ft_do_cd(command_parts, myenv);
		return (0);
	}
	else if (!ft_strcmp(command_parts[0], "iamgay"))
		ft_iamgay(command_parts);
	else if (!ft_strcmp(command_parts[0], "iambi"))
		ft_iambi(command_parts);
	else {
		ret = ft_do_process(command_parts, myenv);
	}
	*exit_stat = 0;
	ft_free_after_split(command_parts);
	ft_strdel(command_parts);
	return (0);
}