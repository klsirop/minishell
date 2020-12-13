/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/13 18:26:52 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ctrlc(int s)
{
	if (g_pid != 0)
	{
		ft_printf("\n");
		g_pid = 0;
	}
	else
	{
		ft_printf("\n");
		ft_print_promt();
	}
	s = 0;
}

static void	ft_quit(int s)
{
	ft_printf("\nbye bye 😘\n");
	exit(0);
	s = 0;
}

void		ft_init_var(char **env, int argc, char **argv)
{
	if (argc != 1 || ft_strcmp(argv[0], "./minishell"))
		exit(1);
	g_promt = PROMT_SMILE;
	g_env = NULL;
	ft_set_origin_env(&g_env, env);
	ft_printf(CLEAR);
}

int			ft_do_all_commands(char *input, int *is_exit, uint8_t *exit_stat)
{
	char		**semicolon_input;
	int			i;

	semicolon_input = NULL;
	if (input && !(semicolon_input = ft_strsplit(input, ';')))
		ft_error();
	i = 0;
	while (semicolon_input && semicolon_input[i] != NULL)
	{
		*is_exit = ft_do_command(semicolon_input[i], &g_env, exit_stat);
		if (*is_exit)
			return (1);
		i++;
	}
	if (semicolon_input)
	{
		ft_free_after_split(semicolon_input);
		free(semicolon_input);
	}
	return (0);
}

int			main(int argc, char **argv, char **env)
{
	uint8_t		exit_stat;
	char		*input;
	int			is_exit;

	ft_init_var(env, argc, argv);
	exit_stat = 0;
	is_exit = 0;
	while (!is_exit)
	{
		if (signal(SIGINT, ft_ctrlc))
		{
		}
		if (signal(SIGQUIT, ft_quit))
		{
		}
		ft_print_promt();
		input = ft_read_input();
		if (ft_do_all_commands(input, &is_exit, &exit_stat))
			break ;
		ft_strdel(&input);
	}
	ft_free_env(&g_env);
	ft_printf(UNCLEAR);
	return (exit_stat);
}
