/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:58:10 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/06 20:00:38 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_help(char **command) {
	if (command[1] == NULL) {
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP "\n");
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
		ft_fprintf(2, GREEN_FON "minishell:" DROP BOLD " help:" DROP "too many arguments\n");
		return ;
	}
	if (!ft_strcmp(command[1], "echo"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP "\n" BOLD "\techo " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "env"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\tenv" DROP "\n");
	else if (!ft_strcmp(command[1], "setenv"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\tsetenv " DROP "name value\n");
	else if (!ft_strcmp(command[1], "unsetenv"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\tunsetenv " DROP "name\n");
	else if (!ft_strcmp(command[1], "clear"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\tclear" DROP "\n");
	else if (!ft_strcmp(command[1], "help"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\thelp " DROP "[command_name]\n");
	else if (!ft_strcmp(command[1], "cd"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\tcd " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "exit"))
		ft_printf(ITALIC BOLD BLUE_FON "usage:" DROP  "\n" BOLD "\texit" DROP "\n");
	else {
		ft_printf(ITALIC "minishell: " DROP BOLD "help: " DROP "unknown argument\n");
	}
}
