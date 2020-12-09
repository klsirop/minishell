/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/09 14:01:55 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wchar.h>

void	ft_print_this_dir()
{
	t_env *pwd;

	pwd = ft_find_in_list(g_env, "PWD");
	if (pwd && pwd->content)
		ft_printf(BOLD PINK_TEXT "%s " DROP, pwd->content);
}

void	ft_print_promt()
{
	ft_print_this_dir();
	ft_printf("%lc ", g_promt);
	// ft_printf("$> ");
}

static void ft_promt(int s)
{
	// kill(g_pid, 9);
	// ft_printf("ctrlc\n");
	// ft_printf("func g_pid: %d\n", g_pid);
	// ft_print_promt();
	// ft_printf("s: %d\n", s);
	if (g_pid != 0) {
		ft_printf("\n");
		g_pid = 0;
	} else {
		ft_printf("\n");
		ft_print_promt();
	}
	s = 0;
}

static void ft_quit(int s)
{
	ft_printf("\nbye bye 😘\n");
	exit(0);
	s = 0;
}

int main(int argc, char **argv, char **env)
{
	// ft_printf(CLEAR);
	uint8_t exit_stat;
	char *input;
	char **semicolon_input;
	int i;
	int is_exit;

	g_promt = PROMT_SMILE;
	g_env = NULL;
	ft_set_origin_env(&g_env, env);
	exit_stat = 0;
	is_exit = 0;
	while (!is_exit) {
		semicolon_input = NULL;
		// ft_printf("start\n");
		if (signal(SIGINT, ft_promt)) {
			// ft_printf("g_pid: %d\n", g_pid);
		}
		if (signal(SIGQUIT, ft_quit)) {}
		// ft_printf("mid\n");
		ft_print_promt();
		input = ft_read_input();
		// ft_printf("after read\n");

		if (input && !(semicolon_input = ft_strsplit(input, ';'))) {
			
			ft_error();
		}
		i = 0;
		while (semicolon_input && semicolon_input[i] != NULL) {
			// ft_printf("while\n");
			is_exit = ft_do_command(semicolon_input[i], &g_env, &exit_stat);
			if (is_exit) {
				break ;
			}
			i++;
		}
		if (semicolon_input) {
			ft_free_after_split(semicolon_input);
			free(semicolon_input);
		}
		ft_strdel(&input);
	}
	ft_free_env(&g_env);
	// ft_printf(UNCLEAR);
	// ft_printf("exit_stat: %d \n", exit_stat);
	return (exit_stat);
}