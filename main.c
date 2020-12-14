/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/14 17:15:28 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wchar.h>

void		ft_init_var(int argc, char **argv)
{
	argc = (int)argc;
	(void)argv;
	g_promt = PROMT_SMILE;
	g_env = NULL;
	ft_printf(CLEAR);
}

int			ft_do_all_commands(char *input, uint8_t *exit_stat, int *is_exit)
{
	char		**semicolon_input;
	int			i;

	semicolon_input = NULL;
	if (!(semicolon_input = ft_strsplit(input, ';')))
		ft_error();
	i = 0;
	while (semicolon_input && semicolon_input[i] != NULL)
	{
		*is_exit = ft_do_command(semicolon_input[i], &g_env, exit_stat);
		if (*is_exit)
		{
			ft_free_after_split(semicolon_input);
			free(semicolon_input);
			return (1);
		}
		i++;
	}
	ft_free_semicolon(&semicolon_input);
	return (0);
}

int			main(int argc, char **argv, char **env)
{
	uint8_t		exit_stat;
	char		*input;
	int			is_exit;

	ft_init_var(argc, argv);
	ft_set_origin_env(&g_env, env);
	exit_stat = 0;
	is_exit = 0;
	while (!is_exit)
	{
		ft_signal();
		ft_print_promt();
		input = ft_read_input();
		if (ft_do_all_commands(input, &exit_stat, &is_exit) == 1)
		{
			ft_strdel(&input);
			break ;
		}
		ft_strdel(&input);
	}
	ft_free_env(&g_env);
	ft_printf(UNCLEAR);
	return (exit_stat);
}
