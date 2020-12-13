/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:18:15 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/13 18:06:03 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_help_arg(char **command)
{
	if (!ft_strcmp(command[1], "echo"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD "\techo " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "env"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD "\tenv" DROP "\n");
	else if (!ft_strcmp(command[1], "setenv"))
		ft_printf(BLUE_FON"usage:"DROP"\n"BOLD"\tsetenv "DROP"name value\n");
	else if (!ft_strcmp(command[1], "unsetenv"))
		ft_printf(BLUE_FON"usage:"DROP"\n"BOLD"\tunsetenv "DROP"names\n");
	else if (!ft_strcmp(command[1], "clear"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD "\tclear" DROP "\n");
	else if (!ft_strcmp(command[1], "help"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD
					"\thelp " DROP "[command_name]\n");
	else if (!ft_strcmp(command[1], "cd"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD "\tcd " DROP "[args]\n");
	else if (!ft_strcmp(command[1], "exit"))
		ft_printf(BLUE_FON "usage:" DROP "\n" BOLD
						"\texit" DROP " [exit_code]\n");
	else
		ft_printf(GREEN_FON "minishell:" DROP BOLD " help: "
						DROP "unknown argument\n");
}

void	ft_do_help(char **command)
{
	if (command[1] == NULL)
	{
		ft_printf(BLUE_FON "usage:" DROP "\n");
		ft_printf("\t" BOLD "echo " DROP "[argc]\n");
		ft_printf("\t" BOLD "env" DROP "\n");
		ft_printf("\t" BOLD "setenv " DROP "name var\n");
		ft_printf("\t" BOLD "unsetenv " DROP "names\n");
		ft_printf("\t" BOLD "clear" DROP "\n");
		ft_printf("\t" BOLD "help " DROP "[command_name]\n");
		ft_printf("\t" BOLD "cd " DROP "[argc]\n");
		ft_printf("\t" BOLD "exit" DROP " [exit_code]\n");
		return ;
	}
	if (command[1] != NULL && command[2] != NULL)
	{
		ft_fprintf(2, "\a" GREEN_FON "minishell:"
					DROP BOLD " help:" DROP " too many arguments\n");
		return ;
	}
	ft_do_help_arg(command);
}
