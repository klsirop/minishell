/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:47:03 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/30 21:44:42 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_iamgay(char **command) {
	if (command[1] != NULL) {
		ft_printf("minishell: iamgay: too many arguments\n");
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
		ft_printf("minishell: iambi: too many arguments\n");
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

int ft_do_command(char *command, t_env **myenv) {
	char **command_parts;
	int ret;

	command_parts = NULL;
	if (!(command_parts = ft_strsplit_sh(command, ' ', '\t')))
		ft_error();
	
	// ft_printf("\n");
	
	if (!command_parts || !command_parts[0])
		return 0;
	else if (!ft_strcmp(command_parts[0], "echo"))
		ft_do_echo(command_parts, *myenv);
	else if (!ft_strcmp(command_parts[0], "env"))
		ft_print_env(*myenv);
	else if (!ft_strcmp(command_parts[0], "setenv"))
		ft_do_setenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "exit")) {
		if (command_parts[1] == NULL)
			return (-1);
		else
			ft_printf("minishell: exit: too many arguments\n");
		// exit(0);
	}
	else if (!ft_strcmp(command_parts[0], "clear"))
		ft_do_clear();
	else if (!ft_strcmp(command_parts[0], "unsetenv"))
		ft_do_unsetenv(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "help"))
		ft_do_help();
	else if (!ft_strcmp(command_parts[0], "cd"))
		ft_do_cd(command_parts, myenv);
	else if (!ft_strcmp(command_parts[0], "iamgay"))
		ft_iamgay(command_parts);
	else if (!ft_strcmp(command_parts[0], "iambi"))
		ft_iambi(command_parts);
	else {
		ret = ft_do_process(command_parts, myenv);
	}

	ft_free_after_split(command_parts);
	ft_strdel(command_parts);
	return (0);////
}