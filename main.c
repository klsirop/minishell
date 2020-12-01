/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/12/01 14:21:24 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wchar.h>

// #define FON 48;5;18
// #define TEXT
// #define CURS


void	ft_print_this_dir() {
	t_env *pwd;

	pwd = ft_find_in_list(g_env, "PWD");
	ft_printf("\033[32;1m\e[38;5;161m%s\x1B[0m ", pwd->content);
}

void	ft_print_promt() {
	static int promt;

	// ft_print_this_dir();
	promt = PROMT_GAY;
	// ft_printf("%lc ", g_promt);
	ft_printf("$> ");
}

static void ft_promt(int s) {
	ft_printf("\n");
	ft_print_promt();
	s = 0;
}

int main(int argc, char **argv, char **env) {
	// ft_printf(CLEAR);
	int is_exit;
	char *input;
	char **semicolon_input;
	int i;
	// t_env *myenv;

	g_promt = PROMT_SMILE;

	g_env = NULL;
	ft_set_origin_env(&g_env, env);
	is_exit = 0;
	while (!is_exit) {
		ft_print_promt();
		if (signal(SIGINT, ft_promt)) {
			// ft_printf("signal\n");
		}
			// is_exit = 1;
		input = ft_read_input();
			
		if (input && !(semicolon_input = ft_strsplit(input, ';')))
			ft_error();
		i = 0;
		while (input && semicolon_input[i] != NULL) {
			if (ft_do_command(semicolon_input[i], &g_env) == -1) {
				is_exit = 1;
				break ;
			}
			i++;
		}


		// ft_free_after_split(semicolon_input);
		// ft_strdel(semicolon_input);
		// ft_strdel(&input);
	}
	//ft_free_env;
	// ft_printf(UNCLEAR);
	return (0);
}