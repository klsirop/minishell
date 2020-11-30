/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: volyvar- <volyvar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:54:28 by volyvar-          #+#    #+#             */
/*   Updated: 2020/11/30 15:21:19 by volyvar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wchar.h>

void	ft_print_promt() {
	// ft_printf("$> ");
	// char [5] a = "ð\u009f\u0092\u009a";
	// ft_printf("%c", "ð\u009f\u0092\u009a");
	ft_printf("😏 ");
	// char *promt;

	// promt = ft_chrtoa_ostssrk(U+1F60F);
	// promt = ft_chrtoa_ostssrk((unsigned int)('\u1F60F'));
	// ft_printf("%s\n", promt);
	// ft_printf("U+1F60F");
	// printf("%lc", '\u1F60F');
}

static void ft_promt(int s) {
	// ft_printf("\n$> ");
	ft_printf("\n");
	ft_print_promt();
	s = 0;
}

int main(int argc, char **argv, char **env) {
	// ft_printf("\033[?1049h\033[H");
	int is_exit;
	char *input;
	char **semicolon_input;
	int i;
	t_env *myenv;

	myenv = NULL;
	ft_set_origin_env(&myenv, env);
	is_exit = 0;
	while (!is_exit) {
		ft_print_promt();
		// ft_printf("start\n");
		signal(SIGINT, ft_promt);
			// is_exit = 1;
		input = ft_read_input();
			
		if (input && !(semicolon_input = ft_strsplit(input, ';')))
			ft_error();
		i = 0;
		while (input && semicolon_input[i] != NULL) {
			// ft_printf("do: %s\n", semicolon_input[i]);
			if (ft_do_command(semicolon_input[i], &myenv) == -1) {
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
	// ft_printf("\033[?1049l");
	return (0);
}