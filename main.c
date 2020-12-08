/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/08 20:44:32 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wchar.h>

void	ft_print_this_dir() {
	t_env *pwd;

	pwd = ft_find_in_list(g_env, "PWD");
	if (pwd && pwd->content)
		ft_printf(BOLD PINK_TEXT "%s " DROP, pwd->content);
}

void	ft_print_promt() {

	ft_print_this_dir();
	ft_printf("%lc ", g_promt);
	// ft_printf("$> ");
}

static void ft_promt(int s) {
	ft_printf("\n");
	ft_print_promt();
	s = 0;
}

int main(int argc, char **argv, char **env) {
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
		ft_print_promt();
		if (signal(SIGINT, ft_promt)) {
		}
		input = ft_read_input();

		if (!(semicolon_input = ft_strsplit(input, ';')))
			ft_error();
		i = 0;
		while (semicolon_input && semicolon_input[i] != NULL) {
			is_exit = ft_do_command(semicolon_input[i], &g_env, &exit_stat);
			if (is_exit) {
				break ;
			}
			i++;
		}

		ft_free_after_split(semicolon_input);
		free(semicolon_input);
		ft_strdel(&input);
	}
	ft_free_env(&g_env);
	// ft_printf(UNCLEAR);
	// ft_printf("exit_stat: %d \n", exit_stat);
	return (exit_stat);
}